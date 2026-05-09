#include "pch.h"
#include "Domini/CtrlVeureEstadistiquesLliga.hxx"
#include "Dades/ConnexioBD.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {

        // ==========================================================
        // CONSTRUCTOR
        // ==========================================================
        CtrlVeureEstadistiquesLliga::CtrlVeureEstadistiquesLliga() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        // ==========================================================
        // 1. OBTENIR ID LLIGA PER NOM (Para el buscador de Estudiantes)
        // ==========================================================
        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ idLliga = nullptr;
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return idLliga;
        }

        // ==========================================================
        // 2. OBTENIR ID LLIGA ADMIN (Lliga -> Administrador -> Usuari)
        // ==========================================================
        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaAdmin(String^ correu) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ idLliga = nullptr;
            try {
                conn->Open();
                String^ query = "SELECT L.idLliga FROM Lliga L "
                    "INNER JOIN Administrador A ON L.idAdministrador = A.identificador "
                    "INNER JOIN Usuari U ON A.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return idLliga;
        }

        // ==========================================================
        // 3. OBTENIR ID LLIGA CAPITÀ (Lliga <- Temporada <- Equip <- Capitán)
        // ==========================================================
        String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaCapita(String^ correu) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ idLliga = nullptr;
            try {
                conn->Open();
                // Usamos Temporada como puente para llegar a la Liga desde el Equip
                String^ query = "SELECT T.idLliga FROM Temporada T "
                    "INNER JOIN Equip E ON T.idTemporada = E.idTemporada "
                    "INNER JOIN Capita C ON E.idEquip = C.idEquip "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return idLliga;
        }

        // ==========================================================
        // 4. OBTENIR TEMPORADES DE LA LLIGA
        // ==========================================================
        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirTemporadesLliga(String^ idLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            DataTable^ dt = gcnew DataTable();
            try {
                conn->Open();
                String^ query = "SELECT idTemporada, CONCAT('Temporada ', DATE_FORMAT(dataInici, '%Y'), '-', DATE_FORMAT(dataFi, '%Y')) AS NomTemporada "
                    "FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return dt;
        }

        // ==========================================================
        // 5. OBTENIR CLASSIFICACIÓ (Filtrando por la Temporada de la Liga)
        // ==========================================================
        DataTable^ CtrlVeureEstadistiquesLliga::ObtenirClassificacioLliga(String^ idLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            DataTable^ dt = gcnew DataTable();
            try {
                conn->Open();
                // Seleccionamos los equipos que están en temporadas que pertenecen a esta liga
                String^ query = "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
                    "E.derrotes AS D, E.golsAFavor AS GF, E.golsEnContra AS GC, "
                    "E.diferenciaGols AS DG, E.punts AS Punts "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "WHERE T.idLliga = @idLliga "
                    "ORDER BY E.punts DESC, E.diferenciaGols DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return dt;
        }

    }
}