#pragma once
#include <string>
#include "PassarellaJugador.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraJugador {
        private:
            String^ connectionString;

        public:
            CercadoraJugador(String^ connStr);

            PassarellaJugador^ LlegeixPerEquip(String^ idEquip);
            PassarellaJugador^ LlegeixPerDorsalEquip(int dorsal, String^ idEquip);
            List<PassarellaJugador^>^ LlegeixTsPerEquip(String^ idEquip);
            bool ExisteixDorsalEnEquip(int dorsal, String^ idEquip);
        };
    }
}
