#include "pch.h"
#include "CtrlIniciSessio.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlIniciSessio::CtrlIniciSessio() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlIniciSessio::IniciarSessio(String^ correu, String^ contrasenya) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuari = cercadora->LlegeixPerCorreu(correu);

            bool correcte = false;
            if (usuari != nullptr && usuari->GetContrasenya() == contrasenya) {
                PassarellaTemporada::ActualitzarEstats(connectionString);
                PassarellaJornada::ActualitzarEstats(connectionString);
                correcte = true;
            }
            return correcte;
        }

        String^ CtrlIniciSessio::ObtenirTipusUsuari(String^ correu) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuari = cercadora->LlegeixPerCorreu(correu);
            return usuari != nullptr ? usuari->GetTipus() : "";
        }

        bool CtrlIniciSessio::CapitaTeEquip(String^ correu) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            return cercadora->CapitaTeEquip(correu);
        }

        bool CtrlIniciSessio::EquipEstaEnLliga(String^ correu) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            return cercadora->EquipEstaEnLliga(correu);
        }

        String^ CtrlIniciSessio::ObtenirIdEquipDeCapita(String^ correu) {
            CercadoraEquip^ cercadora = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadora->ObtenirIdEquipCapita(correu);
            return idEquip == nullptr ? "" : idEquip;
        }

        String^ CtrlIniciSessio::ObtenirIdUsuari(String^ correu) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            String^ idUsuari = cercadora->ObtenirIdUsuariStringPerCorreu(correu);
            return idUsuari == nullptr ? "" : idUsuari;
        }
    }
}
