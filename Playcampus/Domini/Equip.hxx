#pragma once
#include <string>
#include "Disciplina.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Equip {
        private:
            String^ nom;
            DateTime dataFundacio;
            Disciplina esport;
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
            Equip(String^ nom, DateTime dataFundacio, Disciplina esport);

            String^ GetNom();
            void SetNom(String^ nom);

            DateTime GetDataFundacio();
            void SetDataFundacio(DateTime dataFundacio);

            Disciplina GetEsport();
            void SetEsport(Disciplina esport);

            unsigned int GetPartitsJugats();
            void SetPartitsJugats(unsigned int partitsJugats);

            unsigned int GetVictories();
            void SetVictories(unsigned int victories);

            unsigned int GetDerrotes();
            void SetDerrotes(unsigned int derrotes);

            unsigned int GetEmpats();
            void SetEmpats(unsigned int empats);

            unsigned int GetPunts();
            void SetPunts(unsigned int punts);

            unsigned int GetGolsAFavor();
            void SetGolsAFavor(unsigned int golsAFavor);

            unsigned int GetGolsEnContra();
            void SetGolsEnContra(unsigned int golsEnContra);

            int GetDiferenciaGols();
            void SetDiferenciaGols(int diferenciaGols);

            int GetPosicioClassificacio();
            void SetPosicioClassificacio(int posicioClassificacio);

            // Validacions relacionades
            bool ValidarDataFundacio();
        };
    }
}
