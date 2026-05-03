#pragma once
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
