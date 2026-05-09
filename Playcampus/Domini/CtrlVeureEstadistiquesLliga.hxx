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

            // Mètodes per obtenir la ID de la lliga segons el rol i les dades
            String^ ObtenirIdLligaPerNom(String^ nomLliga); // Per a Estudiants (Cercador)
            String^ ObtenirIdLligaAdmin(String^ telefon);    
            String^ ObtenirIdLligaCapita(String^ telefon);  

            // Mètodes per obtenir les dades a mostrar
            DataTable^ ObtenirTemporadesLliga(String^ idLliga);
            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
        };
    }
}