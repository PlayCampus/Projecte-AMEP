#include "pch.h"
#include "CtrlAfegirJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJugador.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlAfegirJugador::CtrlAfegirJugador() {
        }

        String^ CtrlAfegirJugador::AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita) {
            // Obtenir connexió a la BD
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            // Cercar l'usuari estudiant
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariEstudiant = cercadora->LlegeixPerCorreu(correuEstudiant);

            if (usuariEstudiant == nullptr) {
                throw gcnew Exception("L'usuari estudiant no existeix.");
            }

            if (usuariEstudiant->GetTipus() != "Estudiant") {
                throw gcnew Exception("L'usuari no és de tipus Estudiant.");
            }

            // Cercar el capta per obtenir l'idEquip
            PassarellaUsuari^ usuariCapita = cercadora->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew Exception("L'usuari capta no existeix.");
            }

            if (usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no és de tipus Capita.");
            }

            // Obtenir l'idEquip del capta (necesita consulta a BD)
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            String^ idEquip = nullptr;

            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Capita WHERE identificador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", usuariCapita->GetIdentificador());

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    if (!reader->IsDBNull(0)) {
                        idEquip = reader->GetString(0);
                    }
                }
                reader->Close();

                conn->Close();
            }
            catch (Exception^ ex) {
                conn->Close();
                throw ex;
            }

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capta no té equip assignat.");
            }

            // Verificar que el dorsal no existeix en l'equip
            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connStr);
            if (cercadoraJugador->ExisteixDorsalEnEquip(dorsal, idEquip)) {
                throw gcnew Exception("El dorsal " + dorsal.ToString() + " ja existeix en aquest equip.");
            }

            // Crear el jugador nou
            String^ idJugador = "J-" + Guid::NewGuid().ToString()->Substring(0, 8);
            PassarellaJugador^ jugador = gcnew PassarellaJugador(connStr, idJugador, usuariEstudiant->GetNom(), dorsal, posicio, DateTime::Now);
            jugador->SetIdEquip(idEquip);

            // Inserir jugador
            jugador->Insereix();

            // Actualitzar tipus d'usuari de Estudiant a Jugador
            usuariEstudiant->ActualitzaTipus("Jugador");

            return "Jugador afegit correctament!";
        }
    }
}
