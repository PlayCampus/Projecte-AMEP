#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaEquip {
        private:
            String^ connectionString;
            String^ idEquip;
            String^ nom;
            DateTime dataFundacio;
            String^ esport;
      
            

        public:
            PassarellaEquip(String^ connStr);
            PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport);

            String^ GetIdEquip();
            String^ GetNom();
            DateTime GetDataFundacio();
            String^ GetEsport();

            void Insereix();
            void Modifica();
            void Esborra();
            static PassarellaEquip^ Llegeix(String^ connStr, String^ idEq);
            List <String^>^ ObtenirNomsEquipsPerTemporada(String^ idTemporada);
            void TreureDeLaLligaSiAdmin(String^ idEquip, String^ correuAdmin);
        };
    }
}
