#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEsborrarJornada {
        private:
            String^ connectionString;

        public:
            CtrlEsborrarJornada();

            List<Dictionary<String^, String^>^>^ ObtenirTemporadesAdmin(String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirJornadesPerTemporada(String^ idTemporada);

            void EsborrarJornada(String^ idJornada);
        };
    }
}
