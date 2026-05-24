#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaPartit {
        private:
            String^ connectionString;
            String^ idPartit;
            DateTime dataHora;
            String^ ubicacio;
            String^ estat;
            int golsLocal;
            int golsVisitant;
            String^ idJornada;
            String^ idEquipLocal;    // Aadido
            String^ idEquipVisitant; // Aadido
        public:
            PassarellaPartit(String^ connStr);
            PassarellaPartit(String^ connStr, String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada, String^ idEquipLocal, String^ idEquipVisitant);

            String^ GetIdPartit();
            DateTime GetDataHora();
            String^ GetUbicacio();
            String^ GetEstat();
            int GetGolsLocal();
            int GetGolsVisitant();
            String^ GetIdJornada();
            String^ GetIdEquipLocal();
            String^ GetIdEquipVisitant();

            void InsereixPartit();
            void EsborrarPartit(String^ idPartit);
            void ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat);
            void ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix);
            void AssignarJugadorAPartit(String^ idPartit, String^ idJugador);
            void ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit);
        };
    }
}