#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaConvocatoria {
        private:
            String^ connectionString;
        public:
            PassarellaConvocatoria(String^ connStr);

            void CrearConvocatoria(String^ idPartit, String^ idEquip);
            void AfegirJugadorConvocatoria(String^ idConvocatoria, String^ nomJugador);
            void ActualitzarDisponibilitatJugador(String^ idConvocatoria, String^ nomJugador, bool assistira);
            DataTable^ ObtenirConvocatoria(String^ idConvocatoria);
        };
    }
}
