#pragma once
#include <string>
#include "PassarellaLliga.hxx"
using namespace System;
using namespace System::Data;


using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraLliga {
        private:
            String^ connectionString;

        public:
            CercadoraLliga(String^ connStr);

            String^ ObtenirLligaActivaAdmin(String^ idAdmin);
            String^ ObtenirIdLligaPerNom(String^ nomLliga);
            DataTable^ ObtenirTotesLligues();
        };
    }
}




