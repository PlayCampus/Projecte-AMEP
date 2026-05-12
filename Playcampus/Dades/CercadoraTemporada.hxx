#pragma once
#include <string>
#include "PassarellaTemporada.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraTemporada {
        private:
            String^ connectionString;

        public:
            CercadoraTemporada(String^ connStr);

            List<Dictionary<String^, String^>^>^ ObtenirTemporadesAdmin(String^ correuAdmin);

            String^ ObtenirIdTemporadaEnCurs(String^ idLliga);

        };
    }
}