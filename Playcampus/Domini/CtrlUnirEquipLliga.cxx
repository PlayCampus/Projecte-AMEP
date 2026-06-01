#include "pch.h"
#include "CtrlUnirEquipLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraEquipTemporada.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaEquipTemporada.hxx"
#include <stdexcept>

using namespace System;
using namespace Playcampus::Dades;

static String^ NormalitzarDisciplinaVinculacioLocal(String^ disciplina) {
    String^ resultat = nullptr;

    if (!String::IsNullOrWhiteSpace(disciplina)) {
        String^ disciplinaNeta = disciplina->Trim()->ToLower();

        if (disciplinaNeta == "futbol") {
            resultat = "Futbol";
        }
        else if (disciplinaNeta == "basquet" || disciplinaNeta == L"bàsquet") {
            resultat = "Basquet";
        }
        else if (disciplinaNeta == "voley" || disciplinaNeta == "volei" || disciplinaNeta == L"vòlei") {
            resultat = "Voley";
        }
    }

    return resultat;
}

namespace Playcampus {
    namespace Domini {

        CtrlUnirEquipLliga::CtrlUnirEquipLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlUnirEquipLliga::ComprovarSiLligaExisteix(String^ nomLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaPerNom(nomLliga);
        }

        bool CtrlUnirEquipLliga::ValidarContrasenyaLliga(String^ nomLliga, String^ pass) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            String^ currentPass = cercadoraLliga->ObtenirContrasenyaLliga(nomLliga);
            return currentPass != nullptr && currentPass == pass;
        }

        String^ CtrlUnirEquipLliga::VincularEquip(String^ correuCapita, String^ nomLliga) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquipRecuperat = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquipRecuperat)) {
                throw gcnew Exception(L"Aquest capit\u00E0 no t\u00E9 un equip actiu. Primer enregistra't un.");
            }

            String^ idLligaEncontrado = ComprovarSiLligaExisteix(nomLliga);
            if (idLligaEncontrado == nullptr) {
                throw gcnew Exception("La lliga no existeix.");
            }

            PassarellaTemporada^ passTemporada = gcnew PassarellaTemporada(connectionString);
            String^ idTemporadaMesRecent = passTemporada->ObtenirIdTemporadaMesRecent(idLligaEncontrado);

            if (idTemporadaMesRecent == nullptr || String::IsNullOrWhiteSpace(idTemporadaMesRecent)) {
                throw gcnew Exception(L"La lliga no t\u00E9 cap temporada associada. Primer cal crear una temporada.");
            }

            // Comprobar que la temporada obtenida est� "EnCurs"
            PassarellaTemporada^ dbTemporadaMesRecent = PassarellaTemporada::Llegeix(connectionString, idTemporadaMesRecent);
            if (dbTemporadaMesRecent == nullptr || dbTemporadaMesRecent->GetEstat() == "Finalitzat") {
                throw gcnew Exception(L"La temporada m\u00E9s recent est\u00E0 finalitzada o ha estat retirada. Cal obrir una nova temporada.");
            }

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }

            // RIT22: l'esport de l'equip ha de coincidir amb la disciplina de la lliga de la temporada.
            String^ disciplinaLliga = (gcnew CercadoraLliga(connectionString))->ObtenirDisciplinaLliga(idLligaEncontrado);
            String^ esportEquip = equipDB->GetEsport();
            String^ disciplinaNormalitzada = NormalitzarDisciplinaVinculacioLocal(disciplinaLliga);
            String^ esportNormalitzat = NormalitzarDisciplinaVinculacioLocal(esportEquip);

            if (String::IsNullOrWhiteSpace(disciplinaNormalitzada) || String::IsNullOrWhiteSpace(esportNormalitzat) || disciplinaNormalitzada != esportNormalitzat) {
                throw gcnew Exception("L'equip no es pot vincular a aquesta lliga perque l'esport de l'equip no coincideix amb la disciplina de la lliga.");
            }

            // Usar Llegeix para veure si la vinculacio ja existeix.
            PassarellaEquipTemporada^ vinculacioExistent = PassarellaEquipTemporada::Llegeix(connectionString, idEquipRecuperat, idTemporadaMesRecent);
            if (vinculacioExistent != nullptr) {
                throw gcnew Exception(L"Aquest equip ja esta vinculat a la temporada mes recent d'aquesta lliga.");
            }

            // RIT26: dins d'una mateixa temporada no poden existir dos equips amb el mateix nom.
            CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew CercadoraEquipTemporada(connectionString);
            if (cercadoraEquipTemporada->ExisteixNomEquipEnTemporada(equipDB->GetNom(), idTemporadaMesRecent, idEquipRecuperat)) {
                throw gcnew Exception("Ja existeix un equip amb aquest nom dins d'aquesta temporada.");
            }

            // Crear la associacio amb el segon constructor i guardar-la amb Insereix().
            PassarellaEquipTemporada^ equipTempDB = gcnew PassarellaEquipTemporada(connectionString, idEquipRecuperat, idTemporadaMesRecent);
            equipTempDB->Insereix();

      

       

            // Comprobar
            PassarellaEquipTemporada^ equipComprovat = PassarellaEquipTemporada::Llegeix(connectionString, idEquipRecuperat, idTemporadaMesRecent);
            if (equipComprovat == nullptr || String::IsNullOrEmpty(equipComprovat->GetIdTemporada()) || !equipComprovat->GetIdTemporada()->Equals(idTemporadaMesRecent, StringComparison::OrdinalIgnoreCase)) {
                throw gcnew Exception("La base de dades no ha confirmat la vinculacio de l'equip amb la temporada.");
            }

            return "L'equip " + equipDB->GetNom() + " ha sigut enregistrat amb exit a la lliga " + nomLliga + ".";
        }
    }
}
