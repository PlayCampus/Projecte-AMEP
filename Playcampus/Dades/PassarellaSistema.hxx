#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaSistema {
        private:
            String^ connectionString;

        public:
            PassarellaSistema(String^ connStr);

            void InserirAssignacioJugadorPartit(String^ idPartit, String^ idJugador);
            void ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat);
            void ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix);
            void ActualitzarJugador(String^ idJugador, int dorsal, String^ posicio);
            void ExpulsarJugador(String^ idJugador, String^ idEquip);
            void TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin);
            void SeguirLliga(int idUsuari, String^ idLliga);
            void DeixarDeSeguir(int idUsuari);
            void ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ disciplina, String^ estatAnterior, int golsLocalAnterior, int golsVisitantAnterior, Nullable<DateTime> novaDataPartit);
            void AssignarEquipACapita(String^ idCapita, String^ idEquip);
            void DesassignarEquipCapitaPerCorreu(String^ correuCapita);
            void TancarPools();
        };
    }
}
