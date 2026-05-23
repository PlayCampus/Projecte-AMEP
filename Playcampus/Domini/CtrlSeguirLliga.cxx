#include "pch.h"
#include "CtrlSeguirLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlSeguirLliga::CtrlSeguirLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        int CtrlSeguirLliga::ObtenirIdUsuariPerCorreu(String^ correu) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            int idUsuari = cercadora->ObtenirIdUsuariPerCorreuInt(correu);
            if (idUsuari < 0) {
                throw gcnew Exception("Usuari no trobat.");
            }
            return idUsuari;
        }

        String^ CtrlSeguirLliga::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirDisciplinaLliga(idLliga);
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaPerNom(nomLliga);
        }

        String^ CtrlSeguirLliga::ObtenirNomLligaPerId(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirNomLligaPerId(idLliga);
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaSeguida(String^ correuUsuari) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaSeguida(idUsuari);
        }

        bool CtrlSeguirLliga::TeLligaSeguida(String^ correuUsuari) {
            return ObtenirIdLligaSeguida(correuUsuari) != nullptr;
        }

        void CtrlSeguirLliga::SeguirLliga(String^ correuUsuari, String^ nomLliga) {
            String^ idLliga = ObtenirIdLligaPerNom(nomLliga);
            if (String::IsNullOrEmpty(idLliga)) {
                throw gcnew Exception("La lliga no existeix.");
            }
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->SeguirLliga(idUsuari, idLliga);
        }

        void CtrlSeguirLliga::DeixarDeSeguir(String^ correuUsuari) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->DeixarDeSeguir(idUsuari);
        }

        String^ CtrlSeguirLliga::ObtenirIdTemporadaRellevant(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdTemporadaRellevant(idLliga);
        }

        DataTable^ CtrlSeguirLliga::ObtenirClassificacioLliga(String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirClassificacioLliga(idLliga);
        }

        DataTable^ CtrlSeguirLliga::ObtenirProximsPartits(String^ idLliga, int limit) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirProximsPartits(idLliga, limit);
        }

        DataTable^ CtrlSeguirLliga::ObtenirUltimsResultats(String^ idLliga, int limit) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirUltimsResultats(idLliga, limit);
        }
    }
}
