#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlAssignarJugador {
        private:
            String^ connectionString;

            String^ ObtenirIdEquipCapita(String^ correuCapita);
            void ValidarUsuariCapita(String^ correuCapita);
            bool PartitDisponiblePerEquip(String^ idPartit, String^ idEquip, MySqlConnection^ conn);
            bool JugadorPertanyAEquip(String^ idJugador, String^ idEquip, MySqlConnection^ conn);
            bool AssignacioJaExisteix(String^ idPartit, String^ idJugador, MySqlConnection^ conn);

        public:
            CtrlAssignarJugador();

            List<Dictionary<String^, String^>^>^ ObtenirPartitsDisponibles(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsEquip(String^ correuCapita);
            String^ AssignarJugador(String^ correuCapita, String^ idPartit, String^ idJugador);
        };
    }
}
