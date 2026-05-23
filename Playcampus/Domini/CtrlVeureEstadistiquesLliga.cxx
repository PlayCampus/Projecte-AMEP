#include "pch.h"
#include "CtrlVeureEstadistiquesLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesLliga::CtrlVeureEstadistiquesLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaPerNom(nomLliga);
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaAdmin(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaAdminPerCorreu(correu);
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaCapita(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaCapitaPerCorreu(correu);
        }

        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirTemporadesLliga(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirTemporadesLligaEstadistiques(idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirClassificacioLliga(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirClassificacioLligaEstadistiques(idLliga);
        }
    }
}
