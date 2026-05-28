#pragma once
#include <string>
#include "PassarellaEquipTemporada.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraEquipTemporada {
        private:
            String^ connectionString;

        public:
            CercadoraEquipTemporada(String^ connStr);

            List<String^>^ ObtenirIdsEquipsPerTemporada(String^ idTemporada);
            String^ ObtenirIdTemporadaPerEquip(String^ idEquip);
            List<String^>^ ObtenirNomsEquipsPerTemporada(String^ idTemporada);
            String^ ObtenirIdEquipPerNomITemporada(String^ nomEquip, String^ idTemporada);

            List<String^>^ ObtenirNomsEquipsPerLliga(String^ nomLliga);
            DataTable^ ObtenirLliguesEquip(String^ nomEquip);
            DataTable^ ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga);
            DataTable^ ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada);
        };
    }
}