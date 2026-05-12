#pragma once
// Header preserved: no functional changes to class declaration.
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEliminarJugador {
        private:
            String^ connectionString;

        public:
            CtrlEliminarJugador();
            String^ EliminarJugador(String^ correuCapita, String^ idJugador);
        };
    }
}
