#include "pch.h"
#include "CtrlIniciSessio.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlIniciSessio::CtrlIniciSessio() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlIniciSessio::IniciarSessio(String^ correu, String^ contrasenya) {
            Playcampus::Dades::PassarellaUsuari^ pu = Playcampus::Dades::PassarellaUsuari::LlegeixPerCorreu(connectionString, correu);
            if (pu != nullptr) {
                if (pu->GetContrasenya() == contrasenya) {
                    return true;
                }
            }
            return false;
        }

        String^ CtrlIniciSessio::ObtenirTipusUsuari(String^ correu) {
            Playcampus::Dades::PassarellaUsuari^ pu = Playcampus::Dades::PassarellaUsuari::LlegeixPerCorreu(connectionString, correu);
            if (pu != nullptr) {
                return pu->GetTipus();
            }
            return "";
        }
    }
}
