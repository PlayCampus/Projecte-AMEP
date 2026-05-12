#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlRetirarTemporada {
        private:
            String^ connectionString;

        public:
            CtrlRetirarTemporada();

            // Mètode principal per retirar la temporada
            void RetirarTemporada(String^ correuAdmin);
        };
    }
}