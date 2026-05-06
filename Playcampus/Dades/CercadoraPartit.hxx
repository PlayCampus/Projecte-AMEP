#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraPartit {
        private:
            String^ connectionString;

        public:
            CercadoraPartit(String^ connStr);

            DataTable^ ObtenirPartits();

            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerJornada(String^ idJornada);
        };
    }
}