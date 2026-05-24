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
            void SetPartitsJugats(unsigned int partits);
            void SetVictories(unsigned int victories);
            void SetDerrotes(unsigned int derrotes);
            void SetEmpats(unsigned int empats);
            void SetPunts(unsigned int punts);
            void SetGolsAFavor(unsigned int golsAFavor);
            void SetGolsEnContra(unsigned int golsEnContra);
            void SetDiferenciaGols(int diferencia);
            void SetPosicioClassificacio(int posicio);

            void Insereix();
            void Modifica();
            void Esborra();
            static PassarellaEquip^ Llegeix(String^ connStr, String^ idEq);
            List <String^>^ ObtenirNomsEquipsPerTemporada(String^ idTemporada);
            void TreureDeLaLligaSiAdmin(String^ idEquip, String^ correuAdmin);
        };
    }
}
