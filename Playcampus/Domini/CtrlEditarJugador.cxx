#include "pch.h"
#include "CtrlEditarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;
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

            // Validar capita
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
            }

            if (String::IsNullOrWhiteSpace(usuariCapita->GetTipus()) || usuariCapita->GetTipus()->ToLower() != "capita") {
                throw gcnew UnauthorizedAccessException("NomÃ©s els capitans poden eliminar jugadors.");
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
                    throw gcnew Exception("El capità  no té cap equip registrat.");
                }

                // Comprovar que el jugador pertany a l'equip del capitÃ 
                String^ queryPertany = "SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip";
                MySqlCommand^ cmdPertany = gcnew MySqlCommand(queryPertany, conn);
                cmdPertany->Parameters->AddWithValue("@idJugador", idJugador);
                cmdPertany->Parameters->AddWithValue("@idEquip", idEquip);

                int count = Convert::ToInt32(cmdPertany->ExecuteScalar());
                if (count <= 0) {
                    throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
                }

                // Aquí se dejará la lógica de edición; por ahora comprobamos pertenencia y devolvemos OK.
                // Si se requiere modificar campos concretos, implementarlo según requisitos.
            }
            finally {
                conn->Close();
            }

            return "Validació d'edició realitzada correctament.";
        }
    }
}