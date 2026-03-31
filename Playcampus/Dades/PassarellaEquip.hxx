#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaEquip {
        private:
            String^ connectionString;
            String^ idEquip;
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

            PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio);

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

            void Insereix();
        };
    }
}
