#include "pch.h"
#include "CtrlEsborrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaCapita.hxx"
#include <stdexcept>

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlEsborrarEquip::CtrlEsborrarEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEsborrarEquip::EsborrarEquip(String^ correuCapita) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquipRecuperat = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquipRecuperat)) {
                throw gcnew Exception("Aquest capita no te un equip actiu per esborrar.");
            }

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }

            PassarellaCapita^ passCapita = gcnew PassarellaCapita(connectionString);
            passCapita->DesassignarEquip(idEquipRecuperat);

            equipDB->Esborra();
        }
    }
}
