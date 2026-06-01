
#pragma once
#include <string>
#include "PassarellaEquip.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraEquip {
        private:
            String^ connectionString;

        public:
            CercadoraEquip(String^ connStr);

            String^ ObtenirIdEquipPerNom(String^ nomEquip);
            String^ ObtenirIdEquipCapita(String^ correuCapita);
            bool ExisteixEquipPerId(String^ idEquip);
            bool ExisteixEquipPerNom(String^ nomEquip);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsEquip(String^ idEquip);
            DataTable^ ObtenirPlantillaEquip(String^ idEquip);
        };
    }
}