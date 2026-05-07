#include "pch.h"
#include "EditarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaJugador.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;

namespace Playcampus {
	namespace Domini {
		EditarJugador::EditarJugador() {
			connectionString = ConnexioBD::ObtenirConnectionString();
		}

		String^ EditarJugador::Editar(String^ correuCapita, String^ idJugador, int nouDorsal, String^ novaPosicio) {
			if (String::IsNullOrWhiteSpace(correuCapita)) {
				throw gcnew UnauthorizedAccessException("No hi ha cap usuari connectat.");
			}

			if (String::IsNullOrWhiteSpace(idJugador)) {
				throw gcnew Exception("Cal seleccionar un jugador.");
			}

			// Validar capita
			CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
			PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

			if (usuariCapita == nullptr) {
				throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
			}

			if (String::IsNullOrWhiteSpace(usuariCapita->GetTipus()) || usuariCapita->GetTipus()->ToLower() != "capita") {
				throw gcnew UnauthorizedAccessException("Només els capitans poden modificar jugadors.");
			}

			// Obtenir idEquip del capita
			String^ idEquip = nullptr;
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();

				String^ queryEquip = "SELECT idEquip FROM Capita WHERE identificador = @identificador LIMIT 1";
				MySqlCommand^ cmdEquip = gcnew MySqlCommand(queryEquip, conn);
				cmdEquip->Parameters->AddWithValue("@identificador", usuariCapita->GetIdentificador());

				Object^ resEquip = cmdEquip->ExecuteScalar();
				if (resEquip != nullptr && resEquip != DBNull::Value) {
					idEquip = resEquip->ToString();
				}

				if (String::IsNullOrWhiteSpace(idEquip)) {
					throw gcnew Exception("El capità no té cap equip registrat.");
				}

				// Comprovar que el jugador pertany a l'equip del capità
				String^ queryPertany = "SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip";
				MySqlCommand^ cmdPertany = gcnew MySqlCommand(queryPertany, conn);
				cmdPertany->Parameters->AddWithValue("@idJugador", idJugador);
				cmdPertany->Parameters->AddWithValue("@idEquip", idEquip);

				int count = Convert::ToInt32(cmdPertany->ExecuteScalar());
				if (count <= 0) {
					throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
				}

				// Verificar que el nou dorsal no està en ús per un altre jugador de l'equip
				CercadoraJugador^ cercadorJugador = gcnew CercadoraJugador(connectionString);
				if (cercadorJugador->ExisteixDorsalEnEquip(nouDorsal, idEquip)) {
					// Pot ser el mateix jugador té ja aquest dorsal; cal comprovar idJugador
					// Obtenir dorsal actual del idJugador
					PassarellaJugador^ jugadorActual = PassarellaJugador::Llegeix(connectionString, idJugador);
					if (jugadorActual == nullptr) {
						throw gcnew Exception("No s'ha trobat la informació del jugador.");
					}
					if (jugadorActual->GetDorsal() != nouDorsal) {
						throw gcnew Exception("El dorsal " + nouDorsal.ToString() + " ja existeix en aquest equip.");
					}
				}

				// Llegir dades existents per mantenir estadístiques i altres camps
				PassarellaJugador^ jugador = PassarellaJugador::Llegeix(connectionString, idJugador);
				if (jugador == nullptr) {
					throw gcnew Exception("No s'ha trobat el jugador a la base de dades.");
				}

				// Actualitzar objecte PassarellaJugador amb nous valors
				jugador->SetDorsal(nouDorsal);
				// posició és string, però PassarellaJugador no té setter directe per posició; es passa a través del constructor i Modifica usa el membre 'posicio'
				// No hi ha un SetPosicio públic en PassarellaJugador, així que accedim reinicialitzant un nou PassarellaJugador amb valors existents

				PassarellaJugador^ nouJugador = gcnew PassarellaJugador(connectionString,
					nouDorsal,
					(novaPosicio != nullptr) ? novaPosicio : jugador->GetPosicio(),
					jugador->GetDataNaixement(),
					jugador->GetPartitsJugats(),
					jugador->GetAnotacions(),
					jugador->GetAssistencies(),
					jugador->GetFaltesLleus(),
					jugador->GetFaltesGreus(),
					jugador->GetMinutsJugats(),
					jugador->GetIdEquip());

				// Copiar a la variable usada per Modifica
				// Modifica utilitza els camps de la instància per actualitzar la BD
				// Per això, cridem Modifica sobre l'instància que conté els nous valors
				nouJugador->Modifica(idJugador);

				conn->Close();
			}
			catch (Exception^ ex) {
				conn->Close();
				throw ex;
			}

			return "Jugador modificat correctament.";
		}
	}
}
