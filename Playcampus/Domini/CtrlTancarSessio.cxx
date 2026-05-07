#include "pch.h"
#include "CtrlTancarSessio.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlTancarSessio::CtrlTancarSessio() {
        }

        void CtrlTancarSessio::TancarSessio() {
            // Actualment no requereix fer res a nivell de dades per tancar sessiÃ³.
            // Si hi haguÃ©s una sessiÃ³ global manejada per domini, s'esborraria aquÃ­.
        }
    }
}
