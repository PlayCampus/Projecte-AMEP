#pragma once
#include <string>
using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlAssignarJugador {
        private:
            String^ connectionString;
            String^ ObtenirIdEquipCapita(String^ correuCapita);
            void ValidarUsuariCapita(String^ correuCapita);
            bool PartitDisponiblePerEquip(String^ idPartit, String^ idEquip);
            bool JugadorPertanyAEquip(String^ idJugador, String^ idEquip);
            bool AssignacioJaExisteix(String^ idPartit, String^ idJugador);

        public:
            CtrlAssignarJugador();
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDisponibles(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsEquip(String^ correuCapita);
            String^ AssignarJugador(String^ correuCapita, String^ idPartit, String^ idJugador);
        };
    }
}
