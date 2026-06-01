#include "pch.h"
#include "CtrlEditarJugador.hxx"
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
        CtrlEditarJugador::CtrlEditarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlEditarJugador::EditarJugador(String^ correuCapita, String^ idJugador) {
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
                throw gcnew UnauthorizedAccessException(L"Nom\u00E9s els capitans poden eliminar jugadors.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception(L"El capit\u00E0 no t\u00E9 cap equip registrat.");
            }

            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);
            if (!cercadoraJugador->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
            }

            return L"Validaci\u00F3 d'edici\u00F3 realitzada correctament.";
        }

        String^ CtrlEditarJugador::ActualitzarJugador(String^ correuCapita, String^ idJugador, int dorsal, String^ posicio) {
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
                throw gcnew UnauthorizedAccessException(L"Nom\u00E9s els capitans poden editar jugadors.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception(L"El capit\u00E0 no t\u00E9 cap equip registrat.");
            }

            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);
            if (!cercadoraJugador->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
            }

            PassarellaJugador^ passJugador = gcnew PassarellaJugador(connectionString);
            passJugador->ActualitzarDorsalIPosicio(idJugador, dorsal, posicio);

            return "Jugador actualitzat correctament.";
        }
    }
}
