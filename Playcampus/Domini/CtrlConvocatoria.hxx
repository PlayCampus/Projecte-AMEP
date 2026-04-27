#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConvocatoria {
        private:
            String^ connectionString;
        public:
            CtrlConvocatoria(String^ connStr);

            void CrearConvocatoria(String^ idPartit, String^ idEquip);
            void AfegirJugadorConvocatoria(String^ idConvocatoria, String^ nomJugador);
            void ActualitzarDisponibilitatJugador(String^ idConvocatoria, String^ nomJugador, bool assistira);
        };
    }
}
