#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultaPartits {
        private:
            String^ connectionString;

        public:
            CtrlConsultaPartits();

            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirCalendariCompletLligaPerId(String^ idLliga);
        };
    }
}
