#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;


namespace Playcampus {
    namespace Dades {
        public ref class PassarellaJornada {
        private:
            String^ connectionString;
            String^ idJornada;
            String^ idTemporada;
            int numero;
            DateTime dataInici;
            DateTime dataFi;
            String^ estat;

        public:
            // Constructores
            PassarellaJornada(String^ connStr, String^ idJornada, String^ idTemporada,int numero, DateTime dataInici, DateTime dataFi, String^ estat);

            // Getters
            String^ GetIdJornada();
            String^ GetIdTemporada();
            DateTime GetDataInici();
            DateTime GetDataFi();
            String^ GetEstat();
            int GetNumero();


            // Métodos de base de datos
            void Insereix();

            static void ActualitzarEstats(String^ connString);
        };
    }
}