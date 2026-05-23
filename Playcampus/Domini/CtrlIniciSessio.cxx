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
            CercadoraEquip^ cercadora = gcnew CercadoraEquip(connectionString);
            return cercadora->CapitaTeEquip(correu);
        }

        bool CtrlIniciSessio::EquipEstaEnLliga(String^ correu) {
            CercadoraEquip^ cercadora = gcnew CercadoraEquip(connectionString);
            return cercadora->EquipEstaEnLliga(correu);
        }

        String^ CtrlIniciSessio::ObtenirIdEquipDeCapita(String^ correu) {
            CercadoraEquip^ cercadora = gcnew CercadoraEquip(connectionString);
            PassarellaEquip^ pEquip = cercadora->LlegeixCapitaPerCorreu(correu);
            if (pEquip != nullptr) {
                return pEquip->GetIdEquip();
            }
            return "";
        }

        String^ CtrlIniciSessio::ObtenirIdUsuari(String^ correu) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            String^ idUsuari = cercadora->ObtenirIdUsuariPerCorreuString(correu);
            if (idUsuari == nullptr) {
                idUsuari = "";
            }
            return idUsuari;
        }
    }
}
