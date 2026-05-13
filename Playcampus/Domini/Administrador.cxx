#include "pch.h"
#include "Administrador.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        Administrador::Administrador(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ telefonContacte) 
            : Usuari(identificador, nom, contrasenya, data_registre, correu_electronic) {
            this->telefonContacte = telefonContacte;
        }

        String^ Administrador::GetTelefonContacte() { return telefonContacte; }

        void Administrador::ValidarEquip(String^ idEquip) {
            // LÃ²gica de validaciÃ³ d'equips
        }

        void Administrador::AssignarRolCapita(Usuari^ usuari) {
            // Assignar rol de capitÃ  a l'usuari
        }

        void Administrador::ConfigurarLliga(String^ nomLliga) {
            // Configurar parÃ metres de la lliga
        }

        void Administrador::EstablirCalendariOficial(String^ iLliga) {
            // Establir calendari de la lliga
        }

        void Administrador::ValidarResultatsJornada(int jornadaId) {
            // Tancar les actes dels partits
        }
    }
}
