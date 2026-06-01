#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlAfegirJugador {
        public:
            CtrlAfegirJugador();

            String^ AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita, DateTime dataNaixement);
        };
    }
}
