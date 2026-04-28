#pragma once
#include <string>
#include "PassarellaUsuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraUsuari {
        private:
            String^ connectionString;

        public:
            CercadoraUsuari(String^ connStr);

            PassarellaUsuari^ LlegeixPerCorreu(String^ correu);
            PassarellaUsuari^ LlegeixPerNomUsuari(String^ nomUsuari);
        };
    }
}