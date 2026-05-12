#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEditarJugador {
        private:
            String^ connectionString;

        public:
            CtrlEditarJugador();
            // Método para editar un jugador; la implementación concreta puede modificarse más adelante
            String^ EditarJugador(String^ correuCapita, String^ idJugador);
        };
    }
}