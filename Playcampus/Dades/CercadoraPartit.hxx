#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraPartit {
        private:
            String^ connectionString;

        public:
            CercadoraPartit(String^ connStr);

            DataTable^ ObtenirPartits();
        };
    }
}