#include "pch.h"
#include "CtrlCrearPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaPartit.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraEquipTemporada.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlCrearPartit::CtrlCrearPartit() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlCrearPartit::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            Playcampus::Dades::CercadoraLliga^ cercadoraLliga = gcnew Playcampus::Dades::CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirNomLligaAdministrador(correuAdmin);
        }

        void CtrlCrearPartit::CrearPartit(DateTime dataHora, String^ ubicacio, String^ nomEquipLocal, String^ nomEquipVisitant, String^ idJornada, String^ tipusUsuari) {

            if (String::IsNullOrEmpty(tipusUsuari) || tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear un partit.");
            }

            if (String::Equals(nomEquipLocal, nomEquipVisitant, StringComparison::Ordinal)) {
                throw gcnew ArgumentException("Un equip no pot jugar contra ell mateix.");
            }

            try {
                if (String::IsNullOrEmpty(idJornada)) {
                    throw gcnew Exception("La jornada no s'ha trobat o no és vàlida.");
                }

                Playcampus::Dades::CercadoraJornada^ cercadoraJornada = gcnew Playcampus::Dades::CercadoraJornada(connectionString);
                String^ idTemporada = cercadoraJornada->ObtenirIdTemporadaPerJornada(idJornada);

                if (String::IsNullOrEmpty(idTemporada)) {
                    throw gcnew Exception("No s'ha pogut determinar la temporada de la jornada seleccionada.");
                }

                String^ idEquipLocal = ObtenirIdEquip(nomEquipLocal, idTemporada);
                String^ idEquipVisitant = ObtenirIdEquip(nomEquipVisitant, idTemporada);

                if (String::IsNullOrEmpty(idEquipLocal)) {
                    throw gcnew Exception("L'equip local '" + nomEquipLocal + "' no existeix a la temporada seleccionada.");
                }
                if (String::IsNullOrEmpty(idEquipVisitant)) {
                    throw gcnew Exception("L'equip visitant '" + nomEquipVisitant + "' no existeix a la temporada seleccionada.");
                }

                String^ estat = "Pendent";

                Playcampus::Dades::PassarellaPartit^ partit = gcnew Playcampus::Dades::PassarellaPartit(
                    connectionString,
                    nullptr,
                    dataHora,
                    ubicacio,
                    estat,
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

        String^ CtrlCrearPartit::ObtenirIdEquip(String^ nomEquip, String^ idTemporada) {
            Playcampus::Dades::CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew Playcampus::Dades::CercadoraEquipTemporada(connectionString);
            return cercadoraEquipTemporada->ObtenirIdEquipPerNomITemporada(nomEquip, idTemporada);
        }

        List<Dictionary<String^, String^>^>^ CtrlCrearPartit::ObtenirTemporadesLliga(String^ nomLliga) {
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connectionString);
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
            Playcampus::Dades::CercadoraJornada^ cercJor = gcnew Playcampus::Dades::CercadoraJornada(connectionString);
            return cercJor->ObtenirDictJornadesPerTemporada(idTemporada);
        }

        List<String^>^ CtrlCrearPartit::ObtenirNomsEquipsPerTemporada(String^ idTemporada) {
            Playcampus::Dades::CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew Playcampus::Dades::CercadoraEquipTemporada(connectionString);
            return cercadoraEquipTemporada->ObtenirNomsEquipsPerTemporada(idTemporada);
        }
    }
}
