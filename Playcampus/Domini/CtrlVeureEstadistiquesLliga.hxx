#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlVeureEstadistiquesLliga {
        private:
            String^ connectionString;
        public:
            CtrlVeureEstadistiquesLliga();

            // Metodes per obtenir la ID de la lliga segons el rol i les dades.
            String^ ObtenirIdLligaPerNom(String^ nomLliga);
            String^ ObtenirIdLligaAdmin(String^ correu);
            String^ ObtenirIdLligaCapita(String^ correu);

            // Metodes per obtenir les dades a mostrar.
            DataTable^ ObtenirTotesLligues();
            DataTable^ CercarLliguesPerNom(String^ textCerca);
            DataTable^ ObtenirTemporadesLliga(String^ idLliga);
            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
            DataTable^ ObtenirClassificacioLligaTemporada(String^ idLliga, String^ idTemporada);
        };
    }
}
