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
                throw gcnew Exception(L"Nom\u00E9s els capitans poden eliminar jugadors.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);
            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception(L"El capit\u00E0 no t\u00E9 equip assignat.");
            }

            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);
            if (!cercadoraJugador->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception(L"El jugador no pertany a l'equip del capit\u00E0.");
            }

            PassarellaJugador^ passJugador = gcnew PassarellaJugador(connectionString);
            passJugador->ExpulsarJugadorDeEquip(idJugador, idEquip);

            return "Jugador expulsat correctament de l'equip i ha passat a ser Estudiant.";
        }
    }
}
