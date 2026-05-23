#pragma once
#include <string>
#include "PassarellaLliga.hxx"
using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraLliga {
        private:
            String^ connectionString;

        public:
            CercadoraLliga(String^ connStr);

            String^ ObtenirLligaActivaAdmin(String^ idAdmin);
            String^ ObtenirIdLligaPerNom(String^ nomLliga);
            DataTable^ ObtenirTotesLligues();

            String^ ObtenirNomLligaAdmin(String^ correuAdmin);
            String^ ObtenirNomLligaPerId(String^ idLliga);
            String^ ObtenirContrasenyaLligaPerNom(String^ nomLliga);
            String^ ObtenirIdTemporadaRellevant(String^ idLliga);
            String^ ObtenirDisciplinaLliga(String^ idLliga);
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquipsGenerals();
            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
            DataTable^ ObtenirProximsPartits(String^ idLliga, int limit);
            DataTable^ ObtenirUltimsResultats(String^ idLliga, int limit);
            String^ ObtenirIdLligaAdminPerCorreu(String^ correuAdmin);
            String^ ObtenirIdLligaCapitaPerCorreu(String^ correuCapita);
            DataTable^ ObtenirTemporadesLligaEstadistiques(String^ idLliga);
            DataTable^ ObtenirClassificacioLligaEstadistiques(String^ idLliga);
        };
    }
}




