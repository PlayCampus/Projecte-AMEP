#pragma once
#include "Usuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Administrador : public Usuari {
        private:
            String^ telefonContacte;

        public:
            Administrador(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ telefonContacte);

            String^ GetTelefonContacte();

            void ValidarEquip(String^ idEquip);

            void AssignarRolCapita(Usuari^ usuari);

            void ConfigurarLliga(String^ nomLliga);

            void EstablirCalendariOficial(String^ iLliga);

            void ValidarResultatsJornada(int jornadaId);
        };
    }
}
