#include "pch.h"
#include "CtrlConsultes.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlConsultes::CtrlConsultes() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultes::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirDisciplinaLliga(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirProgramacioPartits() {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirProgramacioPartits();
        }

        DataTable^ CtrlConsultes::ObtenirEstatLligues() {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstatLligues();
        }

        DataTable^ CtrlConsultes::ObtenirEstadistiquesEquips() {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstadistiquesEquipsGenerals();
        }

        DataTable^ CtrlConsultes::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirCalendariCompletLligaPerId(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirUltimsFitxatges(int limit) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirUltimsFitxatges(limit);
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEquipsDeLaLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultes::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirNomLligaAdministrador(correuAdmin);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsContacte(String^ correuUsuari) {
            if (String::IsNullOrWhiteSpace(correuUsuari)) {
                throw gcnew Exception("No s'ha pogut identificar l'usuari actual.");
            }

            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ tipusUsuari = cercadora->ObtenirTipusUsuariPerCorreu(correuUsuari);
            String^ tipusNormalitzat = "";
            if (!String::IsNullOrEmpty(tipusUsuari)) {
                tipusNormalitzat = tipusUsuari->ToLower();
            }

            DataTable^ resultat = gcnew DataTable();
            if (tipusNormalitzat == "capita") {
                resultat = cercadora->ObtenirTelefonsAdministradorPerCapita(correuUsuari);
            }
            else if (tipusNormalitzat == "jugador") {
                resultat = cercadora->ObtenirTelefonsContactePerJugador(correuUsuari);
            }
            else if (tipusNormalitzat == "administrador") {
                resultat = cercadora->ObtenirTelefonsCapitansPerAdministrador(correuUsuari);
            }
            else {
                throw gcnew Exception("Aquest usuari no té permisos per consultar números de telèfon.");
            }
            return resultat;
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->TreureEquipDeLaLliga(idEquip, correuAdmin);
        }
    }
}
