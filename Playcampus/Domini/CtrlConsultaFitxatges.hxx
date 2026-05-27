#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultaFitxatges {
        private:
            String^ connectionString;

        public:
            CtrlConsultaFitxatges();

            DataTable^ ObtenirUltimsFitxatges(int limit);
        };
    }
}
