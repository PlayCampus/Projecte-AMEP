#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CercadoraConvocatoria {
        private:
            String^ connectionString;
        public:
            CercadoraConvocatoria(String^ connStr);
            DataTable^ CercaJugadorsEquip(String^ idEquip);
            DataTable^ CercaConvocatoriesEquip(String^ idEquip);
        };
    }
}
