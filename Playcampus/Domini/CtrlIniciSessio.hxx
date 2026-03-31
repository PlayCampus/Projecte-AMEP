#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlIniciSessio {
        private:
            String^ connectionString;
        public:
            CtrlIniciSessio();
            bool IniciarSessio(String^ correu, String^ contrasenya);
            String^ ObtenirTipusUsuari(String^ correu);
        };
    }
}
