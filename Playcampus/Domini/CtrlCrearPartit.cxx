#include "pch.h"
#include "CtrlCrearPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaPartit.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include <stdexcept>

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlCrearPartit::CtrlCrearPartit() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlCrearPartit::CrearPartit(DateTime dataHora, String^ ubicacio, String^ nomEquipLocal, String^ nomEquipVisitant, String^ idJornada, String^ tipusUsuari) {
            if (String::IsNullOrEmpty(tipusUsuari) || tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear un partit.");
            }

            if (nomEquipLocal->Equals(nomEquipVisitant, StringComparison::OrdinalIgnoreCase)) {
                throw gcnew ArgumentException("Un equip no pot jugar contra ell mateix.");
            }

            try {
                String^ idEquipLocal = ObtenirIdEquip(nomEquipLocal);
                String^ idEquipVisitant = ObtenirIdEquip(nomEquipVisitant);

                if (String::IsNullOrEmpty(idEquipLocal)) {
                    throw gcnew Exception("L'equip local '" + nomEquipLocal + "' no existeix.");
                }
                if (String::IsNullOrEmpty(idEquipVisitant)) {
                    throw gcnew Exception("L'equip visitant '" + nomEquipVisitant + "' no existeix.");
                }
                if (String::IsNullOrEmpty(idJornada)) {
                    throw gcnew Exception("La jornada no s'ha trobat o no és vàlida.");
                }

                PassarellaPartit^ partit = gcnew PassarellaPartit(
                    connectionString,
                    nullptr,
                    dataHora,
                    ubicacio,
                    "Pendent",
                    0, 0,
                    idJornada,
                    idEquipLocal,
                    idEquipVisitant
                );

                partit->InsereixPartit();
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Error al inserir el partit: " + ex->Message);
            }
        }

        String^ CtrlCrearPartit::ObtenirIdEquip(String^ nomEquip) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirIdEquipPerNom(nomEquip);
        }

        bool CtrlCrearPartit::ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin) {
            PassarellaUsuari^ usuari = (gcnew CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuAdmin);
            if (usuari == nullptr) return false;

            PassarellaLliga^ passLliga = gcnew PassarellaLliga(connectionString);
            return passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
        }

        List<Dictionary<String^, String^>^>^ CtrlCrearPartit::ObtenirTemporadesLliga(String^ nomLliga) {
            PassarellaTemporada^ passTemp = gcnew PassarellaTemporada(connectionString);
            List<Dictionary<String^, String^>^>^ totesLesTemporades = passTemp->ObtenirDictTemporadesPerLliga(nomLliga);

            List<Dictionary<String^, String^>^>^ temporadesActives = gcnew List<Dictionary<String^, String^>^>();
            for each (Dictionary<String^, String^> ^ dict in totesLesTemporades) {
                String^ estat = dict["estat"]->ToLower();
                if (estat != "retirada" && estat != "finalitzat") {
                    temporadesActives->Add(dict);
                }
            }
            return temporadesActives;
        }

        List<Dictionary<String^, String^>^>^ CtrlCrearPartit::ObtenirJornadesTemporada(String^ idTemporada) {
            CercadoraJornada^ cercJor = gcnew CercadoraJornada(connectionString);
            return cercJor->ObtenirDictJornadesPerTemporada(idTemporada);
        }

        List<String^>^ CtrlCrearPartit::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirNomsEquipsPerLliga(nomLliga);
        }
    }
}
