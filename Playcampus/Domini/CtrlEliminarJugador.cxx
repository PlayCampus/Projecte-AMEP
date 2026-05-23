#include "pch.h"
#include "CtrlEliminarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlEliminarJugador::CtrlEliminarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlEliminarJugador::EliminarJugador(String^ correuCapita, String^ idJugador) {
            if (String::IsNullOrWhiteSpace(correuCapita)) {
                throw gcnew UnauthorizedAccessException("No hi ha cap usuari connectat.");
            }
            if (String::IsNullOrWhiteSpace(idJugador)) {
                throw gcnew Exception("Cal seleccionar un jugador.");
            }

            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);
            if (usuariCapita == nullptr) {
                throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
            }
            if (String::IsNullOrWhiteSpace(usuariCapita->GetTipus()) || usuariCapita->GetTipus()->ToLower() != "capita") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden eliminar jugadors.");
            }

            CercadoraSistema^ cercadoraSistema = gcnew CercadoraSistema(connectionString);
            String^ idEquip = cercadoraSistema->ObtenirIdEquipCapitaPerIdentificador(usuariCapita->GetIdentificador());
            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té cap equip registrat.");
            }
            if (!cercadoraSistema->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
            }

            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->ExpulsarJugador(idJugador, idEquip);
            return "Jugador expulsat correctament de l'equip i ha passat a ser Estudiant.";
        }
    }
}
