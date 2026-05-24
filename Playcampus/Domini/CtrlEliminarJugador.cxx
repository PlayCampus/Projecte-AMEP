#include "pch.h"
#include "CtrlEliminarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaJugador.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlEliminarJugador::CtrlEliminarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlEliminarJugador::EliminarJugador(String^ correuCapita, String^ idJugador) {
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr || usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("Només els capitans poden eliminar jugadors.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);
            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té equip assignat.");
            }

            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);
            if (!cercadoraJugador->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador no pertany a l'equip del capità.");
            }

            PassarellaJugador^ passJugador = gcnew PassarellaJugador(connectionString);
            passJugador->ExpulsarJugadorDeEquip(idJugador, idEquip);

            return "Jugador expulsat correctament de l'equip i ha passat a ser Estudiant.";
        }
    }
}
