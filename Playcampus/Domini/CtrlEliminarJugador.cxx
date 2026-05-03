#include "pch.h"
#include "CtrlEliminarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;
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

            // Validar capita
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
            }

            if (String::IsNullOrWhiteSpace(usuariCapita->GetTipus()) || usuariCapita->GetTipus()->ToLower() != "capita") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden eliminar jugadors.");
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

                // Eliminar associació: set idEquip = NULL
                String^ queryUpdate = "UPDATE Jugador SET idEquip = NULL WHERE idJugador = @idJugador AND idEquip = @idEquip";
                MySqlCommand^ cmdUpdate = gcnew MySqlCommand(queryUpdate, conn);
                cmdUpdate->Parameters->AddWithValue("@idJugador", idJugador);
                cmdUpdate->Parameters->AddWithValue("@idEquip", idEquip);

                int files = cmdUpdate->ExecuteNonQuery();
                if (files != 1) {
                    throw gcnew Exception("No s'ha pogut expulsar el jugador de l'equip.");
                }
            }
            finally {
                conn->Close();
            }

            return "Jugador expulsat correctament de l'equip.";
        }
    }
}
