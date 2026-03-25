#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlUsuari {
        private:
            String^ connectionString;
            static CtrlUsuari^ instancia = nullptr;
            CtrlUsuari();

        public:
            static CtrlUsuari^ GetInstancia();

            bool IniciarSessio(String^ correu, String^ contrasenya);
            void CrearUsuari(String^ id, String^ nom, String^ pass, DateTime dataReg, String^ correu, String^ tipus);
        };
    }
}
