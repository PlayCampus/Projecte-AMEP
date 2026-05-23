#include "pch.h"
#include "CtrlIniciSessio.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlIniciSessio::CtrlIniciSessio() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlIniciSessio::IniciarSessio(String^ correu, String^ contrasenya) {
            PassarellaUsuari^ pu = (gcnew CercadoraUsuari(connectionString))->LlegeixPerCorreu(correu);
            if (pu != nullptr) {
                if (pu->GetContrasenya() == contrasenya) {
                    PassarellaTemporada^ pt = gcnew PassarellaTemporada(connectionString);
                    pt->ActualitzarEstats(connectionString);
                    PassarellaJornada^ pj = gcnew PassarellaJornada(connectionString);
                    pj->ActualitzarEstats(connectionString);
                    return true;
                }
            }
            return false;
        }

        String^ CtrlIniciSessio::ObtenirTipusUsuari(String^ correu) {
            PassarellaUsuari^ pu = (gcnew CercadoraUsuari(connectionString))->LlegeixPerCorreu(correu);
            if (pu != nullptr) {
                return pu->GetTipus();
            }
            return "";
        }

        bool CtrlIniciSessio::CapitaTeEquip(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->CapitaTeEquip(correu);
        }

        bool CtrlIniciSessio::EquipEstaEnLliga(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->EquipEstaEnLliga(correu);
        }

        String^ CtrlIniciSessio::ObtenirIdEquipDeCapita(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ idEquip = cercadora->ObtenirIdEquipCapitaPerCorreu(correu);
            if (idEquip == nullptr) {
                idEquip = "";
            }
            return idEquip;
        }

        String^ CtrlIniciSessio::ObtenirIdUsuari(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ idUsuari = cercadora->ObtenirIdUsuariPerCorreuString(correu);
            if (idUsuari == nullptr) {
                idUsuari = "";
            }
            return idUsuari;
        }
    }
}
