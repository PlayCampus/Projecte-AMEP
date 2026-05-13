#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultes {
        private:
            String^ connectionString;

        public:
            CtrlConsultes();

            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquips();
            DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            void TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin);
        };
    }
}
