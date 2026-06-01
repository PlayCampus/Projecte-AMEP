#include "pch.h"
#include "CtrlSeguirLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/PassarellaLliga.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlSeguirLliga::CtrlSeguirLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        int CtrlSeguirLliga::ObtenirIdUsuariPerCorreu(String^ correu) {
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            return cercadoraUsuari->ObtenirIdUsuariPerCorreu(correu);
        }

        String^ CtrlSeguirLliga::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirDisciplinaLliga(idLliga);
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaPerNom(nomLliga);
        }

        String^ CtrlSeguirLliga::ObtenirNomLligaPerId(String^ idLliga) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirNomLligaPerId(idLliga);
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaSeguida(String^ correuUsuari) {
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirIdLligaSeguida(correuUsuari);
        }

        bool CtrlSeguirLliga::TeLligaSeguida(String^ correuUsuari) {
            return !String::IsNullOrWhiteSpace(ObtenirIdLligaSeguida(correuUsuari));
        }

        void CtrlSeguirLliga::SeguirLliga(String^ correuUsuari, String^ nomLliga) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            if (idUsuari < 0) {
                throw gcnew Exception("No s'ha trobat l'usuari.");
            }

            String^ idLliga = ObtenirIdLligaPerNom(nomLliga);
            if (String::IsNullOrWhiteSpace(idLliga)) {
                throw gcnew Exception("No s'ha trobat la lliga.");
            }

            PassarellaLliga^ passarellaLliga = gcnew PassarellaLliga(connectionString);
            passarellaLliga->SeguirLliga(idUsuari.ToString(), idLliga);
        }

        void CtrlSeguirLliga::DeixarDeSeguir(String^ correuUsuari) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            if (idUsuari < 0) {
                throw gcnew Exception("No s'ha trobat l'usuari.");
            }

            PassarellaLliga^ passarellaLliga = gcnew PassarellaLliga(connectionString);
            passarellaLliga->DeixarDeSeguir(idUsuari.ToString());
        }

        String^ CtrlSeguirLliga::ObtenirIdTemporadaRellevant(String^ idLliga) {
            CercadoraTemporada^ cercadoraTemporada = gcnew CercadoraTemporada(connectionString);
            return cercadoraTemporada->ObtenirIdTemporadaRellevant(idLliga);
        }

        DataTable^ CtrlSeguirLliga::ObtenirClassificacioLliga(String^ idLliga) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            if (String::IsNullOrWhiteSpace(idTemporada)) {
                return gcnew DataTable();
            }
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirClassificacioLligaSeguida(idLliga, idTemporada);
        }

        DataTable^ CtrlSeguirLliga::ObtenirProximsPartits(String^ idLliga, int limit) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            if (String::IsNullOrWhiteSpace(idTemporada)) {
                return gcnew DataTable();
            }
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirProximsPartits(idLliga, idTemporada, limit);
        }

        DataTable^ CtrlSeguirLliga::ObtenirUltimsResultats(String^ idLliga, int limit) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            if (String::IsNullOrWhiteSpace(idTemporada)) {
                return gcnew DataTable();
            }
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirUltimsResultats(idLliga, idTemporada, limit);
        }
    }
}
