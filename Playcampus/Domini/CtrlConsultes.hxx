#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultes {
        public:
            CtrlConsultes();

            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquips();
            DataTable^ ObtenirCalendariCompletLligaPerId(String^ idLliga);
            DataTable^ ObtenirUltimsFitxatges(int limit);
            DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            DataTable^ ObtenirTelefonsContacte(String^ correuUsuari);
            void TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin);
        };
    }
}
