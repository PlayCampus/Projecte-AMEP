#pragma once
#include <string>
#include "PassarellaUsuari.hxx"

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraUsuari {
        private:
            String^ connectionString;

        public:
            CercadoraUsuari(String^ connStr);

            PassarellaUsuari^ LlegeixPerCorreu(String^ correu);
            PassarellaUsuari^ LlegeixPerNomUsuari(String^ nomUsuari);
            int ObtenirIdUsuariPerCorreu(String^ correu);
            String^ ObtenirIdUsuariStringPerCorreu(String^ correu);
            String^ ObtenirTipusUsuariPerCorreu(String^ correu);
            bool CapitaTeEquip(String^ correu);
            bool EquipEstaEnLliga(String^ correu);
        };
    }
}