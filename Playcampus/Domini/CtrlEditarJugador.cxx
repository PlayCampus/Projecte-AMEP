#include "pch.h"
#include "CtrlEditarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/PassarellaEquip.hxx"

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
				throw gcnew UnauthorizedAccessException("Només els capitans podem eliminar jugadors.");
			}

			CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
			PassarellaEquip^ pEquip = cercadoraEquip->LlegeixCapitaPerIdentificador(usuariCapita->GetIdentificador());
			if (pEquip == nullptr) {
				throw gcnew Exception("El capià no té cap equip registrat.");
			}
			String^ idEquip = pEquip->GetIdEquip();
			if (!cercadoraEquip->JugadorPertanyAEquip(idJugador, idEquip)) {
				throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
			}
			return "Validació d'edició realitzada correctament.";
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
				throw gcnew UnauthorizedAccessException("Només els capitans pueden editar jugadors.");
			}

			CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
			PassarellaEquip^ pEquip = cercadoraEquip->LlegeixCapitaPerIdentificador(usuariCapita->GetIdentificador());
			if (pEquip == nullptr) {
				throw gcnew Exception("El capià no té cap equip registrat.");
			}
			String^ idEquip = pEquip->GetIdEquip();
			if (!cercadoraEquip->JugadorPertanyAEquip(idJugador, idEquip)) {
				throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
			}

			PassarellaEquip^ passarella = gcnew PassarellaEquip(connectionString);
			passarella->ActualitzarJugador(idJugador, dorsal, posicio);
			return "Jugador actualitzat correctament.";
		}
	}
}
