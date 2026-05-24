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

namespace Playcampus {
    namespace Domini {
        CtrlEnregistrarEquip::CtrlEnregistrarEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEnregistrarEquip::EnregistrarEquip(String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, String^ tipusUsuari, String^ correuUsuari) {
            if (tipusUsuari->ToLower() != "capita" && tipusUsuari->ToLower() != "capità") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden enregistrar un equip.");
            }

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
