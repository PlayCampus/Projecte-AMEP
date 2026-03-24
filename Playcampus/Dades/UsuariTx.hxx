#pragma once
#include <string>

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        public ref class UsuariTx {
        private:
            String^ connectionString;

        public:
            UsuariTx(String^ connectionString);

            // Mètode Transaction Script per crear l'usuari a la BBDD
            void CrearUsuari(String^ identificador, String^ nom, String^ contrasenya, DateTime dataRegistre, String^ correuElectronic, String^ tipus, String^ dadaExtra1, String^ dadaExtra2);

            // Llegir usuaris depenent del seu tipus de la BBDD
            DataTable^ ObtenirUsuaris();

            // Mètode per iniciar sessió
            bool IniciarSessio(String^ correu, String^ contrasenya);

            // Canviar rol a capità
            void ConvertirACapita(String^ idUsuari);
        };
    }
}
