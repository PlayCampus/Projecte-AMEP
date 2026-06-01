#include "pch.h"
#include "CtrlEnregistrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaCapita.hxx"
#include <stdexcept>

using namespace System;
using namespace Playcampus::Dades;

static String^ NormalitzarDisciplinaEquipLocal(String^ esport) {
    String^ resultat = nullptr;

    if (!String::IsNullOrWhiteSpace(esport)) {
        String^ esportNet = esport->Trim()->ToLower();

        if (esportNet == "futbol") {
            resultat = "Futbol";
        }
        else if (esportNet == "basquet" || esportNet == L"bàsquet") {
            resultat = "Basquet";
        }
        else if (esportNet == "voley" || esportNet == "volei" || esportNet == L"vòlei") {
            resultat = "Voley";
        }
    }

    return resultat;
}

namespace Playcampus {
    namespace Domini {
        CtrlEnregistrarEquip::CtrlEnregistrarEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEnregistrarEquip::EnregistrarEquip(String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, String^ tipusUsuari, String^ correuUsuari) {
            if (tipusUsuari->ToLower() != "capita" && tipusUsuari->ToLower() != L"capit\u00E0") {
                throw gcnew UnauthorizedAccessException(L"Nom\u00E9s els capitans poden enregistrar un equip.");
            }

            // RIT19: el nom d'un equip no pot ser buit.
            if (String::IsNullOrWhiteSpace(nom)) {
                throw gcnew ArgumentException("El nom de l'equip no pot ser buit.");
            }

            // RIT20: la data de fundacio d'un equip ha de ser anterior o igual a la data actual.
            if (dataFundacio.Date > DateTime::Now.Date) {
                throw gcnew ArgumentException("La data de fundacio de l'equip no pot ser posterior a la data actual.");
            }

            // RIT21: l'esport d'un equip nomes pot ser Futbol, Voley o Basquet.
            String^ esportNormalitzat = NormalitzarDisciplinaEquipLocal(esport);
            if (String::IsNullOrWhiteSpace(esportNormalitzat)) {
                throw gcnew ArgumentException("L'esport de l'equip ha de ser Futbol, Voley o Basquet.");
            }
            esport = esportNormalitzat;
            nom = nom->Trim();

            String^ idCapita = nullptr;
            if (!String::IsNullOrEmpty(correuUsuari)) {
                PassarellaUsuari^ capUser = (gcnew CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuUsuari);
                if (capUser != nullptr && capUser->GetIdentificador() != nullptr) {
                    idCapita = capUser->GetIdentificador()->Trim();
                }
            }

            try {
                PassarellaEquip^ pe = gcnew PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport);
                pe->Insereix();

                if (idCapita != nullptr) {
                    String^ realIdEquip = pe->GetIdEquip();
                    if (String::IsNullOrEmpty(realIdEquip)) {
                        realIdEquip = idEquip;
                    }

                    PassarellaCapita^ passCapita = gcnew PassarellaCapita(connectionString);
                    passCapita->AssignarEquip(idCapita, realIdEquip);
                }
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Error al inserir l'equip: " + ex->Message);
            }
        }
    }
}
