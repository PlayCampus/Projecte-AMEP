#include "pch.h"
#include "CtrlAbandonarLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlAbandonarLliga::CtrlAbandonarLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlAbandonarLliga::AbandonarLliga(String^ correuCapita) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquipRecuperat = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquipRecuperat)) {
                throw gcnew Exception("Aquest capita no te un equip actiu.");
            }

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }

            String^ nomEquip = equipDB->GetNom();

            equipDB->SetIdTemporada(nullptr);
            equipDB->SetPartitsJugats(0);
            equipDB->SetVictories(0);
            equipDB->SetDerrotes(0);
            equipDB->SetEmpats(0);
            equipDB->SetPunts(0);
            equipDB->SetGolsAFavor(0);
            equipDB->SetGolsEnContra(0);
            equipDB->SetDiferenciaGols(0);
            equipDB->SetPosicioClassificacio(0);
            equipDB->Modifica();

            PassarellaEquip^ equipComprovat = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipComprovat == nullptr || equipComprovat->GetIdTemporada() != nullptr) {
                throw gcnew Exception("La base de dades no ha confirmat l'abandó de la lliga.");
            }

            if (equipComprovat->GetPunts() != 0 || equipComprovat->GetVictories() != 0) {
                throw gcnew Exception("La base de dades no ha confirmat la reinicialitzacio de les estadistiques.");
            }

            return "L'equip " + nomEquip + " ha abandonat la lliga. Les estadistiques han sigut reiniciades.";
        }
    }
}
