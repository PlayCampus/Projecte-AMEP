#include "pch.h"
#include "CtrlAssignarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlAssignarJugador::CtrlAssignarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlAssignarJugador::ValidarUsuariCapita(String^ correuCapita) {
            if (String::IsNullOrWhiteSpace(correuCapita)) {
                throw gcnew UnauthorizedAccessException("No hi ha cap usuari connectat.");
            }

            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuari = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuari == nullptr) {
                throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
            }

            if (String::IsNullOrWhiteSpace(usuari->GetTipus()) || usuari->GetTipus()->ToLower() != "capita") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden assignar jugadors a partits.");
            }
        }

        String^ CtrlAssignarJugador::ObtenirIdEquipCapita(String^ correuCapita) {
            ValidarUsuariCapita(correuCapita);

            String^ idEquip = nullptr;
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Capita WHERE identificador = @identificador LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@identificador", usuariCapita->GetIdentificador());

                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString();
                }
            }
            finally {
                conn->Close();
            }

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té cap equip registrat.");
            }

            return idEquip;
        }

        void CtrlAssignarJugador::AssegurarTaulaConvocatoria(MySqlConnection^ conn) {
            String^ query =
                "CREATE TABLE IF NOT EXISTS AssignacioJugadorPartit ("
                "idPartit VARCHAR(100) NOT NULL, "
                "idJugador VARCHAR(100) NOT NULL, "
                "dataAssignacio DATETIME NOT NULL, "
                "PRIMARY KEY (idPartit, idJugador)"
                ")";

            MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
            cmd->ExecuteNonQuery();
        }

        bool CtrlAssignarJugador::PartitDisponiblePerEquip(String^ idPartit, String^ idEquip, MySqlConnection^ conn) {
            bool disponible = false;
            String^ query =
                "SELECT COUNT(*) FROM Partit "
                "WHERE idPartit = @idPartit "
                "AND (idEquipLocal = @idEquip OR idEquipVisitant = @idEquip) "
                "AND (estat IS NULL OR LOWER(estat) <> 'finalitzat')";

            MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@idPartit", idPartit);
            cmd->Parameters->AddWithValue("@idEquip", idEquip);

            Object^ resultat = cmd->ExecuteScalar();
            int total = Convert::ToInt32(resultat);
            if (total > 0) {
                disponible = true;
            }

            return disponible;
        }

        bool CtrlAssignarJugador::JugadorPertanyAEquip(String^ idJugador, String^ idEquip, MySqlConnection^ conn) {
            bool pertany = false;
            String^ query = "SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip";

            MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@idJugador", idJugador);
            cmd->Parameters->AddWithValue("@idEquip", idEquip);

            Object^ resultat = cmd->ExecuteScalar();
            int total = Convert::ToInt32(resultat);
            if (total > 0) {
                pertany = true;
            }

            return pertany;
        }

        bool CtrlAssignarJugador::AssignacioJaExisteix(String^ idPartit, String^ idJugador, MySqlConnection^ conn) {
            bool existeix = false;
            String^ query = "SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = @idPartit AND idJugador = @idJugador";

            MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@idPartit", idPartit);
            cmd->Parameters->AddWithValue("@idJugador", idJugador);

            Object^ resultat = cmd->ExecuteScalar();
            int total = Convert::ToInt32(resultat);
            if (total > 0) {
                existeix = true;
            }

            return existeix;
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirPartitsDisponibles(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
                    "el.nom AS equipLocal, ev.nom AS equipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE (p.idEquipLocal = @idEquip OR p.idEquipVisitant = @idEquip) "
                    "AND (p.estat IS NULL OR LOWER(p.estat) <> 'finalitzat') "
                    "ORDER BY p.dataHora ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                while (reader->Read()) {
                    Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                    partit["idPartit"] = reader["idPartit"]->ToString();
                    partit["dataHora"] = reader["dataHora"]->ToString();
                    partit["ubicacio"] = reader->IsDBNull(reader->GetOrdinal("ubicacio")) ? "" : reader["ubicacio"]->ToString();
                    partit["estat"] = reader->IsDBNull(reader->GetOrdinal("estat")) ? "" : reader["estat"]->ToString();
                    partit["equipLocal"] = reader["equipLocal"]->ToString();
                    partit["equipVisitant"] = reader["equipVisitant"]->ToString();
                    partits->Add(partit);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }

            return partits;
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirJugadorsEquip(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT J.idJugador, U.nom, J.dorsal, J.posicio "
                    "FROM Jugador J "
                    "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                    "WHERE J.idEquip = @idEquip "
                    "ORDER BY J.dorsal ASC, U.nom ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                while (reader->Read()) {
                    Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
                    String^ idJugador = reader["idJugador"]->ToString();
                    jugador["idJugador"] = idJugador;
                    jugador["dorsal"] = reader->IsDBNull(reader->GetOrdinal("dorsal")) ? "" : reader["dorsal"]->ToString();
                    jugador["posicio"] = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader["posicio"]->ToString();
                    
                    // Obtenir el nom de l'Usuari mittançant CercadoraUsuari
                    // Creem una query directa per a l'usuari
                    MySqlConnection^ connU = gcnew MySqlConnection(connectionString);
                    try {
                        connU->Open();
                        String^ queryU = "SELECT nom FROM Usuari WHERE identificador = @id";
                        MySqlCommand^ cmdU = gcnew MySqlCommand(queryU, connU);
                        cmdU->Parameters->AddWithValue("@id", idJugador);
                        Object^ nomResult = cmdU->ExecuteScalar();
                        jugador["nom"] = (nomResult != nullptr) ? nomResult->ToString() : "";
                    }
                    finally {
                        connU->Close();
                    }
                    
                    jugadors->Add(jugador);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }

            return jugadors;
        }

        String^ CtrlAssignarJugador::AssignarJugador(String^ correuCapita, String^ idPartit, String^ idJugador) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idPartit)) {
                throw gcnew Exception("Cal seleccionar un partit.");
            }

            if (String::IsNullOrWhiteSpace(idJugador)) {
                throw gcnew Exception("Cal seleccionar un jugador.");
            }

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                AssegurarTaulaConvocatoria(conn);

                if (!PartitDisponiblePerEquip(idPartit, idEquip, conn)) {
                    throw gcnew Exception("El partit seleccionat no està disponible per a l'equip del capità o ja està finalitzat.");
                }

                if (!JugadorPertanyAEquip(idJugador, idEquip, conn)) {
                    throw gcnew Exception("El jugador seleccionat no pertany a l'equip del capità.");
                }

                if (AssignacioJaExisteix(idPartit, idJugador, conn)) {
                    throw gcnew Exception("Aquest jugador ja està assignat a aquest partit.");
                }

                String^ query = "INSERT INTO AssignacioJugadorPartit (idPartit, idJugador, dataAssignacio) VALUES (@idPartit, @idJugador, NOW())";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idJugador", idJugador);
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }

            return "Jugador assignat correctament al partit.";
        }
    }
}
