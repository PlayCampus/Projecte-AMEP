#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include "CtrlEsborrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"
#include <stdexcept>

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlEsborrarEquip::CtrlEsborrarEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEsborrarEquip::EsborrarEquip(String^ correuCapita) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ idEquipRecuperat = cercadora->ObtenirIdEquipCapitaPerCorreu(correuCapita);
            if (String::IsNullOrWhiteSpace(idEquipRecuperat)) {
                throw gcnew Exception("Aquest capita no te un equip actiu per esborrar.");
            }
            idEquipRecuperat = idEquipRecuperat->Trim();

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB != nullptr) {
                equipDB->Esborra();
                PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
                passarella->DesassignarEquipCapitaPerCorreu(correuCapita);
            }
            else {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }
        }
    }
}
