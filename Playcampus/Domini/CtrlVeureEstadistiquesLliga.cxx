#include "pch.h"
#include "CtrlVeureEstadistiquesLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraTemporada.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesLliga::CtrlVeureEstadistiquesLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaPerNom(nomLliga);
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaAdmin(String^ correu) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaAdmin(correu);
        }

        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaCapita(String^ correu) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaCapita(correu);
        }


        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirTotesLligues() {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirTotesLliguesEstadistiques();
        }

        DataTable^ CtrlVeureEstadistiquesLliga::CercarLliguesPerNom(String^ textCerca) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->CercarLliguesPerNom(textCerca);
        }

        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirTemporadesLliga(String^ idLliga) {
            CercadoraTemporada^ cercadoraTemporada = gcnew CercadoraTemporada(connectionString);
            return cercadoraTemporada->ObtenirTemporadesLligaEstadistiques(idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirClassificacioLliga(String^ idLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirClassificacioLliga(idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirClassificacioLligaTemporada(String^ idLliga, String^ idTemporada) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirClassificacioLligaTemporada(idLliga, idTemporada);
        }
    }
}
