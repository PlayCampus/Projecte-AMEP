#pragma once
#include <string>
#include "PassarellaJornada.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraJornada {
        private:
            String^ connectionString;

        public:
            CercadoraJornada(String^ connStr);

            List<Dictionary<String^, String^>^>^ ObtenirDictJornadesPerTemporada(String^ idTemporada);
            String^ ObtenirIdTemporadaPerJornada(String^ idJornada);
        };
    }
}