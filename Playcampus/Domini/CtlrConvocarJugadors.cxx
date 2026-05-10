#include "pch.h"
#include "CtlrConvocarJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtlrConvocarJugadors::CtlrConvocarJugadors() {
            this->connectionString = ConnexioBD::ObtenirConnectionString();
        }

        // 1. Obtener partidos donde el usuario es el capitán
        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsCapita(String^ correuCapita) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                // Buscamos partidos donde el equipo del capitán sea local o visitante
                String^ query = "SELECT p.idPartit, el.nom AS local, ev.nom AS visitant, p.dataHora, "
                    "CONCAT(el.nom, ' vs ', ev.nom, ' (', p.dataHora, ')') AS nomMostrar "
                    "FROM Partit p "
                    "JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE (p.idEquipLocal = ("
                    "   SELECT c.idEquip FROM Capita c JOIN Usuari u ON c.identificador = u.identificador WHERE u.correu_electronic = @correu LIMIT 1"
                    ") "
                    "OR p.idEquipVisitant = ("
                    "   SELECT c.idEquip FROM Capita c JOIN Usuari u ON c.identificador = u.identificador WHERE u.correu_electronic = @correu LIMIT 1"
                    ")) "
                    "AND p.estat = 'Pendent' "
                    "ORDER BY p.dataHora DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuCapita);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["id_partit"] = reader["idPartit"]->ToString();
                    d["equip_local"] = reader["local"]->ToString();
                    d["equip_visitant"] = reader["visitant"]->ToString();
                    d["data"] = reader["dataHora"]->ToString();
                    // Campo extra para el ComboBox del Form1
                    d["nomMostrar"] = d["equip_local"] + " vs " + d["equip_visitant"];
                    partits->Add(d);
                }
                reader->Close();
            }
            finally { conn->Close(); }
            return partits;
        }

        // 2. Implementación de ObtenirConvocatoriaPartit
        // Nota: Para que esta función sepa qué jugadores mostrar (los del capitán), 
        // lo ideal es que use la lógica de buscar por el equipo del capitán.
        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirConvocatoriaPartit(String^ idPartit) {
            // Esta función es genérica, si necesitas filtrar por el equipo del capitán 
            // te recomiendo usar 'ObtenirEstatConvocatoria' pasándole el ID del equipo.
            return ObtenirPartitsDeLEquip(idPartit); // O una implementación similar
        }

        // 3. Obtener partidos de un equipo específico
        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsDeLEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idPartit, dataHora FROM Partit WHERE idEquipLocal = @id OR idEquipVisitant = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["idPartit"] = reader["idPartit"]->ToString();
                    d["dataHora"] = reader["dataHora"]->ToString();
                    partits->Add(d);
                }
            }
            finally { conn->Close(); }
            return partits;
        }

        // 4. Obtener lista de jugadores y su estado (EL QUE USA LA TABLA)
        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                // LEFT JOIN para ver a todos los jugadores aunque no estén en la tabla de convocatorias aún
                String^ query = "SELECT j.idJugador, u.nom, j.posicio, "
                    "IFNULL(cp.convocat, 0) AS convocat, IFNULL(cp.confirmat, 0) AS confirmat "
                    "FROM Jugador j "
                    "JOIN Usuari u ON j.idJugador = u.identificador "
                    "LEFT JOIN ConvocatoriaPartit cp ON j.idJugador = cp.idJugador AND cp.idPartit = @idPartit "
                    "WHERE j.idEquip = @idEquip";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["id_jugador"] = reader["idJugador"]->ToString();
                    d["nom"] = reader["nom"]->ToString();
                    d["posicio"] = reader["posicio"]->ToString();
                    // Convertimos el 1/0 de la BD a texto para la tabla
                    d["estat_convocatoria"] = (reader["convocat"]->ToString() == "1") ? "Convocat" : "No Convocat";
                    d["confirmacio"] = (reader["confirmat"]->ToString() == "1") ? "Confirmat" : "Pendent";
                    jugadors->Add(d);
                }
                reader->Close();
            }
            finally { conn->Close(); }
            return jugadors;
        }

        // 5. El capitán convoca o desconvoca
        void CtlrConvocarJugadors::ActualitzarConvocatoria(String^ idPartit, String^ idJugador, bool convocat) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO ConvocatoriaPartit (idPartit, idJugador, convocat, confirmat) "
                    "VALUES (@idP, @idJ, @conv, 0) "
                    "ON DUPLICATE KEY UPDATE convocat = @conv";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idP", idPartit);
                cmd->Parameters->AddWithValue("@idJ", idJugador);
                cmd->Parameters->AddWithValue("@conv", convocat ? 1 : 0);
                cmd->ExecuteNonQuery();
            }
            finally { conn->Close(); }
        }

        // 6. El jugador confirma asistencia
        void CtlrConvocarJugadors::ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE ConvocatoriaPartit SET confirmat = @conf "
                    "WHERE idPartit = @idP AND idJugador = @idJ";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idP", idPartit);
                cmd->Parameters->AddWithValue("@idJ", idJugador);
                cmd->Parameters->AddWithValue("@conf", assisteix ? 1 : 0);
                cmd->ExecuteNonQuery();
            }
            finally { conn->Close(); }
        }
        Dictionary<String^, String^>^ CtlrConvocarJugadors::ObtenirAvisPendent(String^ correuJugador) {
            Dictionary<String^, String^>^ avis = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Busca si el jugador está convocado (1) pero aún no ha confirmado (0)
                String^ query = "SELECT cp.idPartit, p.dataHora, el.nom AS local, ev.nom AS visitant "
                    "FROM ConvocatoriaPartit cp "
                    "JOIN Partit p ON cp.idPartit = p.idPartit "
                    "JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "JOIN Jugador j ON cp.idJugador = j.idJugador "
                    "JOIN Usuari u ON j.idJugador = u.identificador "
                    "WHERE u.correu_electronic = @correu AND cp.convocat = 1 AND cp.confirmat = 0 LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuJugador);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                if (reader->Read()) {
                    avis = gcnew Dictionary<String^, String^>();
                    avis["idPartit"] = reader["idPartit"]->ToString();
                    avis["missatge"] = "Has estat convocat pel partit:\n" + reader["local"]->ToString() + " vs " + reader["visitant"]->ToString() + "\n(" + reader["dataHora"]->ToString() + ")";
                }
                reader->Close();
            }
            finally { conn->Close(); }
            return avis;
        }
    }
}