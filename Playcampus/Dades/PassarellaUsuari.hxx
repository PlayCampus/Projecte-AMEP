#pragma once
#include <string>

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaUsuari {
        private:
            String^ connectionString;
            String^ identificador;
            String^ nom;
            String^ contrasenya;
            DateTime dataRegistre;
            String^ correuElectronic;
            String^ tipus;

        public:
            PassarellaUsuari(String^ connStr);
            PassarellaUsuari(String^ connStr, String^ id, String^ n, String^ pwd, DateTime d, String^ correu, String^ t);

            String^ GetIdentificador();
            String^ GetNom();
            String^ GetContrasenya();
            DateTime GetDataRegistre();
            String^ GetCorreuElectronic();
            String^ GetTipus();

            void Insereix();
            void Modifica();
            void Esborra();

            static PassarellaUsuari^ LlegeixPerCorreu(String^ connStr, String^ correu);
            static PassarellaUsuari^ LlegeixPerNomUsuari(String^ connStr, String^ nomUsuari); 

        };
    }
}
