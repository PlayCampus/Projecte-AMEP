#pragma once

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Usuari {
        protected:
            String^ identificador;
            String^ nom;
            String^ contrasenya;
            DateTime data_registre;
            String^ correu_electronic;

        public:
            Usuari(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic);

            // Getters i Setters
            String^ GetIdentificador();
            String^ GetNom();
            String^ GetContrasenya();
            DateTime GetDataRegistre();
            String^ GetCorreuElectronic();

            virtual void MostrarInformacio();
        };
    }
}
