#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlVeureEstadistiquesEquip {
        private:
            String^ connectionString;

        public:
            CtrlVeureEstadistiquesEquip();

            bool ExisteixEquip(String^ nomEquip);
            DataTable^ ObtenirLliguesEquip(String^ nomEquip);
            DataTable^ ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga);
            DataTable^ ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada);
        };
    }
}
