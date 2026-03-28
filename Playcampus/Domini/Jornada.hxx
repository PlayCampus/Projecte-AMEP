#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Jornada {
        private:
            String^ idJornada; // ID
            int numero;
            DateTime dataInici;
            DateTime dataFi;

        public:
            Jornada(String^ idJornada, int numero, DateTime dataInici, DateTime dataFi);

            String^ GetIdJornada();
            void SetIdJornada(String^ idJornada);

            int GetNumero();
            void SetNumero(int numero);

            DateTime GetDataInici();
            void SetDataInici(DateTime dataInici);

            DateTime GetDataFi();
            void SetDataFi(DateTime dataFi);

            // Validacions
            bool ValidarDates();
            bool ValidarNumero();
        };
    }
}
