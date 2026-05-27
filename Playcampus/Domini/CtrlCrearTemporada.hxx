#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;
namespace Playcampus {
    namespace Domini {
        public ref class CtrlCrearTemporada {
        private:
            String^ connectionString;
        public:
            CtrlCrearTemporada();

            // Mètode principal per crear la temporada
            void CrearTemporada(DateTime dataInici, DateTime dataFi, String^ correuAdmin);
            
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);

            List<Dictionary<String^, String^>^>^ ObtenirTemporadesPerLliga(String^ nomLliga);
        };
    }
}