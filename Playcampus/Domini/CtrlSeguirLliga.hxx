#pragma once

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlSeguirLliga {
        private:
            String^ connectionString;
            int ObtenirIdUsuariPerCorreu(String^ correu);
            String^ ObtenirIdTemporadaRellevant(String^ idLliga);
            String^ ObtenirDisciplinaLliga(String^ idLliga);
        public:
            CtrlSeguirLliga();

            String^ ObtenirIdLligaPerNom(String^ nomLliga);
            String^ ObtenirNomLligaPerId(String^ idLliga);

            String^ ObtenirIdLligaSeguida(String^ correuUsuari);
            bool TeLligaSeguida(String^ correuUsuari);

            void SeguirLliga(String^ correuUsuari, String^ nomLliga);
            void DeixarDeSeguir(String^ correuUsuari);

            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
            DataTable^ ObtenirProximsPartits(String^ idLliga, int limit);
            DataTable^ ObtenirUltimsResultats(String^ idLliga, int limit);
        };
    }
}
