#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaEquipTemporada {
        private:
            String^ connectionString;
            String^ idEquip;
            String^ idTemporada;
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

            PassarellaEquipTemporada(String^ connStr);
            PassarellaEquipTemporada(String^ connStr, String^ idEquip, String^ idTemporada);
            PassarellaEquipTemporada(String^ connStr, String^ idEquip, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio, String^ idTemporada);

            //Getters
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
            String^ GetIdEquip();

            //Setters
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

            // Operaciones de BD
            void Insereix();
            void Modifica();
            void Esborra();
            static PassarellaEquipTemporada^ Llegeix(String^ connStr, String^ idEquip, String^ idTemporada);
        };
    }
}