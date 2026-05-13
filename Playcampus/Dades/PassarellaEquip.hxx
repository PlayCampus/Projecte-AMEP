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
            String^ idTemporada;
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

            PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio, String^ idTemporada);

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
            String^ GetIdTemporada();

            void SetIdTemporada(String^ nouIdTemporada);

            void Insereix();
            void Modifica();
            void Esborra();
            static PassarellaEquip^ Llegeix(String^ connStr, String^ idEq);
            List <String^>^ ObtenirNomsEquipsPerTemporada(String^ idTemporada);
        };
    }
}
