#pragma once
#include <string>
#include "Partit.hxx"

using namespace System::Collections::Generic;
using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlCrearPartit {
        private:
            String^ connectionString;
            
            // Mètodes auxiliars per buscar IDs
            String^ ObtenirIdEquip(String^ nomEquip);

        public:
            CtrlCrearPartit();
            void CrearPartit(DateTime dataHora, String^ ubicacio, String^ nomEquipLocal, String^ nomEquipVisitant, String^ idJornada, String^ tipusUsuari);

            bool ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirTemporadesLliga(String^ nomLliga);
            List<Dictionary<String^, String^>^>^ ObtenirJornadesTemporada(String^ idTemporada);
            List<String^>^ ObtenirNomsEquipsPerLliga(String^ nomLliga);
        };
    }
}