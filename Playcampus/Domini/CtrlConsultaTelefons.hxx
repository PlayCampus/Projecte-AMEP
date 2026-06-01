#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlConsultaTelefons {
        private:
            String^ connectionString;

            String^ ObtenirTipusUsuariPerCorreu(String^ correuUsuari);
            DataTable^ ObtenirTelefonsPerCapita(String^ correuUsuari);
            DataTable^ ObtenirTelefonsPerJugador(String^ correuUsuari);
            DataTable^ ObtenirTelefonsPerAdministrador(String^ correuUsuari);

        public:
            CtrlConsultaTelefons();

            DataTable^ ObtenirTelefonsContacte(String^ correuUsuari);
        };
    }
}
