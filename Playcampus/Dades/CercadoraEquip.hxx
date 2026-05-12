#pragma once
#include <string>
#include "PassarellaEquip.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraEquip {
        private:
            String^ connectionString;

        public:
            CercadoraEquip(String^ connStr);

			List<String^>^ ObtenirIdsEquipsPerTemporada(String^ idTemporada);
           

        };
    }
}