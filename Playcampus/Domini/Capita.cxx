#include "pch.h"
#include "Capita.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        Capita::Capita(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ telefonContacte, String^ idEquip) 
            : Usuari(identificador, nom, contrasenya, data_registre, correu_electronic) {
            this->telefonContacte = telefonContacte;
            this->idEquip = idEquip;
            this->validatPerAdmin = false; // Requereix validaciÃ³ prÃ¨via
        }

        String^ Capita::GetTelefonContacte() { return telefonContacte; }

        void Capita::MarcarComValidat() {
            validatPerAdmin = true;
        }

        void Capita::DonarDAltaJugador(String^ idJugador) {
            if(validatPerAdmin) {
                // Codi per donar d'alta a la plantilla
            }
        }

        void Capita::TramitarBaixaJugador(String^ idJugador) {
            if(validatPerAdmin) {
                // Codi per tramitar la baixa
            }
        }

        void Capita::InscriureEquipCompeticio(String^ idCompeticio) {
            if(validatPerAdmin) {
                // Inscriure equip en els terminis establerts
            }
        }
    }
}
