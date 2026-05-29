#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;



namespace Playcampus {
    namespace Dades {
        public ref class PassarellaTemporada {
        private:
            String^ connectionString;
            String^ idTemporada;
            String^ idLliga;
            DateTime dataInici;
            DateTime dataFi;
            String^ estat;

        public:

            // NUEVO CONSTRUCTOR para consultas (solo necesita la conexión)
            PassarellaTemporada(String^ connString);

            // Constructor amb els paràmetres per insertar
            PassarellaTemporada(String^ connString, String^ idTemp, String^ idLlig, DateTime dInici, DateTime dFi, String^ est);

            // Mètode per guardar a la BD
            void Insereix();

            //Getters
            String^ GetIdTemporada();
            String^ GetIdLliga();
            DateTime GetDataInici();
            DateTime GetDataFi();
            String^ GetEstat();


            static void ActualitzarEstats(String^ connString);

            System::Collections::Generic::List<
                System::Collections::Generic::Dictionary<System::String^, System::String^>^>^
                ObtenirDictTemporadesPerLliga(System::String^ nomLliga);

            System::String^ ObtenirIdTemporadaMesRecent(System::String^ idLliga);

            void InicialitzarEquipsNovaTemporada(System::String^ idLliga, System::String^ idTemporadaNova);
            void InicialitzarEquipsTemporadaSeguent(System::String^ idLliga, System::String^ idTemporadaOrigen);

            void RetirarTemporada(System::String^ idLliga);

            static PassarellaTemporada^ Llegeix(System::String^ connectionString, System::String^ idTemporada);


        };
    }
}