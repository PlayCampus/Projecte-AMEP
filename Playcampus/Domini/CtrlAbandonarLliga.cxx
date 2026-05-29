#include "pch.h"
#include "CtrlAbandonarLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraEquipTemporada.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaEquipTemporada.hxx"
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

            CercadoraEquipTemporada^ cercadoraEquipTemp = gcnew CercadoraEquipTemporada(connectionString);
            String^ idTemporada = cercadoraEquipTemp->ObtenirIdTemporadaPerEquip(idEquipRecuperat);

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            PassarellaEquipTemporada^ equipDBTemporada = PassarellaEquipTemporada::Llegeix(connectionString, idEquipRecuperat,idTemporada);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }

            String^ nomEquip = equipDB->GetNom();
            /*
            equipDBTemporada->SetIdTemporada(nullptr);
            equipDBTemporada->SetPartitsJugats(0);
            equipDBTemporada->SetVictories(0);
            equipDBTemporada->SetDerrotes(0);
            equipDBTemporada->SetEmpats(0);
            equipDBTemporada->SetPunts(0);
            equipDBTemporada->SetGolsAFavor(0);
            equipDBTemporada->SetGolsEnContra(0);
            equipDBTemporada->SetDiferenciaGols(0);
            equipDBTemporada->SetPosicioClassificacio(0);
            equipDBTemporada->Modifica();

 

            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }
            if (equipDBTemporada == nullptr) {
                throw gcnew Exception("L'equip no esta vinculat a cap lliga o temporada actualment.");
            }
            */
          

            // Eliminamos la vinculación (la tabla intermedia EquipTemporada)
            equipDBTemporada->Esborra();

            // Comprobamos que el borrado ha surtido efecto intentando leer de nuevo.
            PassarellaEquipTemporada^ equipComprovat = PassarellaEquipTemporada::Llegeix(connectionString, idEquipRecuperat, idTemporada);
            if (equipComprovat != nullptr) {
                throw gcnew Exception("La base de dades no ha confirmat l'abandó de la lliga.");
            }

            return "L'equip " + nomEquip + " ha abandonat la lliga. Les estadistiques han sigut reiniciades.";
        }
    }
}
