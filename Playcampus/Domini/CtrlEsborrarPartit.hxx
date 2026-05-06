#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEsborrarPartit {
        private:
            String^ connectionString;

        public:
            CtrlEsborrarPartit();

            // Mètodes delegats cap a les cercadores
            List<Dictionary<String^, String^>^>^ ObtenirTemporadesAdmin(String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirJornadesPerTemporada(String^ idTemporada);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerJornada(String^ idJornada);

            // Mètode per la Passarella
            void EsborrarPartit(String^ idPartit);
        };
    }
}