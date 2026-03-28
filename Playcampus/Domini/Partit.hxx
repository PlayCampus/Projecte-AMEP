#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Partit {
        private:
            String^ idPartit;
            DateTime dataHora;
            String^ ubicacio;
            String^ estat;
            int golsLocal;
            int golsVisitant;

        public:
            Partit(String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant);

            String^ GetIdPartit();
            void SetIdPartit(String^ idPartit);

            DateTime GetDataHora();
            void SetDataHora(DateTime dataHora);

            String^ GetUbicacio();
            void SetUbicacio(String^ ubicacio);

            String^ GetEstat();
            void SetEstat(String^ estat);

            int GetGolsLocal();
            void SetGolsLocal(int golsLocal);

            int GetGolsVisitant();
            void SetGolsVisitant(int golsVisitant);
        };
    }
}
