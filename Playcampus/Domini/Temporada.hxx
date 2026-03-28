#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Temporada {
        private:
            DateTime dataInici; // ID
            DateTime dataFi;
            String^ estat;

        public:
            Temporada(DateTime dataInici, DateTime dataFi, String^ estat);

            DateTime GetDataInici();
            void SetDataInici(DateTime dataInici);

            DateTime GetDataFi();
            void SetDataFi(DateTime dataFi);

            String^ GetEstat();
            void SetEstat(String^ estat);

            // Validacions
            bool ValidarDates();
        };
    }
}
