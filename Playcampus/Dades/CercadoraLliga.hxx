#pragma once
#include <string>
#include "PassarellaLliga.hxx"
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;


using namespace System;

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
            DataTable^ ObtenirTotesLliguesEstadistiques();
            DataTable^ CercarLliguesPerNom(String^ textCerca);
            String^ ObtenirDisciplinaLliga(String^ idLliga);
            String^ ObtenirNomLligaPerId(String^ idLliga);
            String^ ObtenirContrasenyaLliga(String^ nomLliga);
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            String^ ObtenirIdLligaSeguida(String^ correuUsuari);
            String^ ObtenirIdLligaAdmin(String^ correu);
            String^ ObtenirIdLligaCapita(String^ correu);
            DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);
            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
            DataTable^ ObtenirClassificacioLligaTemporada(String^ idLliga, String^ idTemporada);
            DataTable^ ObtenirClassificacioLligaSeguida(String^ idLliga, String^ idTemporada);
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquips();
            DataTable^ ObtenirTelefonsAdministradorPerCapita(String^ correuUsuari);
            DataTable^ ObtenirTelefonsContactePerJugador(String^ correuUsuari);
            DataTable^ ObtenirTelefonsCapitansPerAdministrador(String^ correuUsuari);
        };
    }
}




