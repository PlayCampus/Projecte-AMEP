#pragma once

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Partit {
        private:
            String^ identificador;
            DateTime dataHora;
            String^ ubicacio;
            String^ estat;
            int golsLocal;
            int golsVisitant;
            String^ idJornada; 

        public:
            Partit(String^ identificador, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada);

            String^ GetIdentificador();
            DateTime GetDataHora();
            String^ GetUbicacio();
            String^ GetEstat();
            int GetGolsLocal();
            int GetGolsVisitant();
            String^ GetIdJornada();

            void SetEstat(String^ nouEstat);
            void SetResultat(int golsLocal, int golsVisitant);

            void MostrarInformacio();
        };
    }
}
