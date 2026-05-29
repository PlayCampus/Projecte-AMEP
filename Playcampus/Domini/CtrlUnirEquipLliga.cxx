#include "pch.h"
#include "CtrlUnirEquipLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaEquipTemporada.hxx"
#include <stdexcept>

using namespace System;
using namespace Playcampus::Dades;

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
                throw gcnew Exception("Aquest capita no te un equip actiu. Primer enregistra't un.");
            }

            String^ idLligaEncontrado = ComprovarSiLligaExisteix(nomLliga);
            if (idLligaEncontrado == nullptr) {
                throw gcnew Exception("La lliga no existeix.");
            }

            PassarellaTemporada^ passTemporada = gcnew PassarellaTemporada(connectionString);
            String^ idTemporadaMesRecent = passTemporada->ObtenirIdTemporadaMesRecent(idLligaEncontrado);

            if (idTemporadaMesRecent == nullptr || String::IsNullOrWhiteSpace(idTemporadaMesRecent)) {
                throw gcnew Exception("La lliga no te cap temporada associada. Primer cal crear una temporada.");
            }

            // Comprobar que la temporada obtenida está "EnCurs"
            PassarellaTemporada^ dbTemporadaMesRecent = PassarellaTemporada::Llegeix(connectionString, idTemporadaMesRecent);
            if (dbTemporadaMesRecent == nullptr || dbTemporadaMesRecent->GetEstat() == "Finalitzat") {
                throw gcnew Exception("La temporada més recent està finalitzada o ha estat retirada. Cal obrir una nova temporada.");
            }

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }



            // Usar Llegeix  para ver si la vinculación ya existe
            PassarellaEquipTemporada^ vinculacioExistent = PassarellaEquipTemporada::Llegeix(connectionString, idEquipRecuperat, idTemporadaMesRecent);
            if (vinculacioExistent != nullptr) {
                throw gcnew Exception("Aquest equip ja està vinculat a la temporada més recent d'aquesta lliga.");
            }

            // Crear la asocación con el segundo constructor y guardarla con Insereix()
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
