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
            String^ ObtenirIdEquip(String^ nomEquip, String^ idTemporada);

        public:
            CtrlCrearPartit();
            void CrearPartit(DateTime dataHora, String^ ubicacio, String^ nomEquipLocal, String^ nomEquipVisitant, String^ idJornada, String^ tipusUsuari);

            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirTemporadesLliga(String^ nomLliga);
            List<Dictionary<String^, String^>^>^ ObtenirJornadesTemporada(String^ idTemporada);
            List<String^>^ ObtenirNomsEquipsPerTemporada(String^ idTemporada);
        };
    }
}
