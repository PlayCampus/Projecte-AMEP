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
            String^ idLliga;
            String^ nom;
            DateTime dataFundacio;
            String^ esport;
            unsigned int partitsJugats;
            unsigned int victories;
            unsigned int derrotes;
            unsigned int empats;
            unsigned int punts;
            unsigned int golsAFavor;
            unsigned int golsEnContra;
            int diferenciaGols;
            int posicioClassificacio;
            

        public:
            PassarellaEquip(String^ connStr);
            PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport);

            PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio, String^ idLliga);

            String^ GetIdEquip();
            String^ GetNom();
            DateTime GetDataFundacio();
            String^ GetEsport();

            unsigned int GetPartitsJugats();
            unsigned int GetVictories();
            unsigned int GetDerrotes();
            unsigned int GetEmpats();
            unsigned int GetPunts();
            unsigned int GetGolsAFavor();
            unsigned int GetGolsEnContra();
            int GetDiferenciaGols();
            int GetPosicioClassificacio();
            String^ GetIdLliga();
            
            void SetIdLliga(String^ nouIdLliga);

            void Insereix();
            void Modifica();
            static PassarellaEquip^ Llegeix(String^ connStr, String^ idEq);
            List <String^>^ ObtenirNomsEquipsPerLliga(String^ idLliga);
        };
    }
}
