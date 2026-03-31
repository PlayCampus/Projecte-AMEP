#include "pch.h"
#include "CtrlEnregistrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlEnregistrarEquip::CtrlEnregistrarEquip() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEnregistrarEquip::EnregistrarEquip(String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, String^ tipusUsuari, String^ correuUsuari) {
            // Verificar que l'usuari és un capità
            if (tipusUsuari->ToLower() != "capita" && tipusUsuari->ToLower() != "capità") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden enregistrar un equip.");
            }

            String^ idCapita = nullptr;
            if (!String::IsNullOrEmpty(correuUsuari)) {
                Playcampus::Dades::PassarellaUsuari^ capUser = Playcampus::Dades::PassarellaUsuari::LlegeixPerCorreu(connectionString, correuUsuari);
                if (capUser != nullptr && capUser->GetIdentificador() != nullptr) {
                    idCapita = capUser->GetIdentificador()->Trim();
                }
            }

            // Guardar a la base de dades utilitzant la passarella
            try {
                Playcampus::Dades::PassarellaEquip^ pe = gcnew Playcampus::Dades::PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport);
                pe->Insereix();
                
                // Aquí, s'hauria d'actualitzar l'ID de l'equip al Capità a la base de dades si fos necessari, depenent dels requeriments addicionals
                // Aquest arxiu es pot estendre si s'ha de vincular directament el capità amb l'equip un cop es crea l'equip
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Error al inserir l'equip: " + ex->Message);
            }
        }
    }
}
