#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlRegistrarUsuari {
        private:
            String^ connectionString;
        public:
            CtrlRegistrarUsuari();
            void CrearUsuari(String^ nom, String^ pass, DateTime dataReg, String^ correu, String^ tipus, String^ telefon);
        };
    }
}
