#include "pch.h"
#include "CtrlTancarSessio.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlTancarSessio::CtrlTancarSessio() {
        }

        void CtrlTancarSessio::TancarSessio() {
            // Actualment no requereix fer res a nivell de dades per tancar sessió.
            // Si hi hagués una sessió global manejada per domini, s'esborraria aquí.
        }
    }
}
