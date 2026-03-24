#pragma once
#include "Usuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Capita : public Usuari {
        private:
            String^ telefonContacte;
            String^ idEquip;
            bool validatPerAdmin;

        public:
            Capita(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ telefonContacte, String^ idEquip);

            String^ GetTelefonContacte();

            void MarcarComValidat();

            void DonarDAltaJugador(String^ idJugador);

            void TramitarBaixaJugador(String^ idJugador);

            void InscriureEquipCompeticio(String^ idCompeticio);
        };
    }
}
