#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultaLligues {
        private:
            String^ connectionString;

        public:
            CtrlConsultaLligues();

            String^ ObtenirDisciplinaLliga(String^ idLliga);
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquips();
            DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            void TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin);
        };
    }
}
