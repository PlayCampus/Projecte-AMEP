#pragma once
#include <string>
#include "PassarellaUsuari.hxx"

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraUsuari {
        private:
            String^ connectionString;

        public:
            CercadoraUsuari(String^ connStr);

            PassarellaUsuari^ LlegeixPerCorreu(String^ correu);
            PassarellaUsuari^ LlegeixPerNomUsuari(String^ nomUsuari);

            String^ ObtenirTipusUsuariPerCorreu(String^ correu);
            String^ ObtenirNomUsuariPerIdentificador(String^ identificador);
            String^ ObtenirIdUsuariPerCorreuString(String^ correu);
            int ObtenirIdUsuariPerCorreuInt(String^ correu);

            DataTable^ ObtenirTelefonsAdministradorPerCapita(String^ correuCapita);
            DataTable^ ObtenirTelefonsContactePerJugador(String^ correuJugador);
            DataTable^ ObtenirTelefonsCapitansPerAdministrador(String^ correuAdministrador);
        };
    }
}
