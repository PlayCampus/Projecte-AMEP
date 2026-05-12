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
            // Método para actualizar los datos del jugador
            String^ ActualitzarJugador(String^ correuCapita, String^ idJugador, int dorsal, String^ posicio);
        };
    }
}