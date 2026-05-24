#include "pch.h"
#include "CercadoraLliga.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        CercadoraLliga::CercadoraLliga(String^ connStr) {
            connectionString = connStr;
        }


        String^ CercadoraLliga::ObtenirLligaActivaAdmin(String^ idAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE idAdministrador = @idAdmin LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idAdmin", idAdmin);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

        String^ CercadoraLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

        DataTable^ CercadoraLliga::ObtenirTotesLligues() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga, nom FROM Lliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }


        String^ CercadoraLliga::ObtenirDisciplinaLliga(String^ idLliga) {
            String^ disciplina = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    disciplina = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return disciplina;
        }

        String^ CercadoraLliga::ObtenirNomLligaPerId(String^ idLliga) {
            String^ nom = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT nom FROM Lliga WHERE idLliga = @idLliga LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    nom = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return nom;
        }

        String^ CercadoraLliga::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            String^ nomLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT l.nom FROM Lliga l "
                    "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                    "WHERE u.correu_electronic = @correuAdmin "
                    "ORDER BY l.nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    nomLliga = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return nomLliga;
        }

        String^ CercadoraLliga::ObtenirIdLligaSeguida(String^ correuUsuari) {
            String^ idLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT USL.idLliga "
                    "FROM UsuariSegueixLliga USL "
                    "INNER JOIN Usuari U ON USL.idUsuari = U.identificador "
                    "WHERE U.correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuUsuari);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idLliga;
        }

        String^ CercadoraLliga::ObtenirIdLligaAdmin(String^ correu) {
            String^ idLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT L.idLliga FROM Lliga L "
                    "INNER JOIN Administrador A ON L.idAdministrador = A.identificador "
                    "INNER JOIN Usuari U ON A.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idLliga;
        }

        String^ CercadoraLliga::ObtenirIdLligaCapita(String^ correu) {
            String^ idLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT T.idLliga FROM Temporada T "
                    "INNER JOIN Equip E ON T.idTemporada = E.idTemporada "
                    "INNER JOIN Capita C ON E.idEquip = C.idEquip "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idLliga;
        }

        DataTable^ CercadoraLliga::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
                    "E.partitsJugats AS PartitsJugats, E.victories AS Victories, E.empats AS Empats, "
                    "E.derrotes AS Derrotes, E.punts AS Punts "
                    "FROM Lliga L "
                    "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "INNER JOIN Temporada T ON T.idLliga = L.idLliga "
                    "INNER JOIN Equip E ON E.idTemporada = T.idTemporada "
                    "WHERE U.correu_electronic = @correuAdmin "
                    "ORDER BY E.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        
        DataTable^ CercadoraLliga::ObtenirClassificacioLliga(String^ idLliga) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
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
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraLliga::ObtenirClassificacioLligaSeguida(String^ idLliga, String^ idTemporada) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ disciplina = ObtenirDisciplinaLliga(idLliga);
                bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
                String^ labelFavor = esFutbol ? "GF" : "PF";
                String^ labelContra = esFutbol ? "GC" : "PC";
                String^ labelDif = esFutbol ? "DG" : "DP";

                String^ query =
                    "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
                    "E.derrotes AS D, E.golsAFavor AS " + labelFavor + ", E.golsEnContra AS " + labelContra + ", "
                    "E.diferenciaGols AS " + labelDif + ", E.punts AS Punts "
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
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraLliga::ObtenirEstatLligues() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT L.nom AS Lliga, L.disciplina AS Esport, "
                    "IFNULL(U.nom, '') AS Administrador, COUNT(DISTINCT E.idEquip) AS NumEquips "
                    "FROM Lliga L "
                    "LEFT JOIN Temporada T ON T.idLliga = L.idLliga "
                    "LEFT JOIN Equip E ON E.idTemporada = T.idTemporada "
                    "LEFT JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "GROUP BY L.idLliga, L.nom, L.disciplina, U.nom "
                    "ORDER BY L.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        
        DataTable^ CercadoraLliga::ObtenirEstadistiquesEquips() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT IFNULL(L.nom, 'Sense lliga') AS Lliga, E.nom AS Equip, E.esport AS Esport, "
                    "E.partitsJugats AS PartitsJugats, E.victories AS Victories, E.empats AS Empats, "
                    "E.derrotes AS Derrotes, E.punts AS Punts, E.golsAFavor AS GolsAFavor, "
                    "E.golsEnContra AS GolsEnContra, E.diferenciaGols AS DiferenciaGols, "
                    "E.posicioClassificacio AS PosicioClassificacio "
                    "FROM Equip E "
                    "LEFT JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "LEFT JOIN Lliga L ON T.idLliga = L.idLliga "
                    "ORDER BY IFNULL(L.nom, ''), E.posicioClassificacio ASC, E.punts DESC, E.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        
        DataTable^ CercadoraLliga::ObtenirTelefonsAdministradorPerCapita(String^ correuUsuari) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                    "A.telefonContacte AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                    "FROM Usuari UC "
                    "INNER JOIN Capita C ON C.identificador = UC.identificador "
                    "INNER JOIN Equip E ON E.idEquip = C.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada "
                    "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                    "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                    "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                    "WHERE UC.correu_electronic = @correu "
                    "AND A.telefonContacte IS NOT NULL AND A.telefonContacte <> ''";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuUsuari);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraLliga::ObtenirTelefonsContactePerJugador(String^ correuUsuari) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                    "C.telefonContacte AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                    "FROM Usuari UJ "
                    "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                    "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                    "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                    "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                    "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada "
                    "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                    "WHERE UJ.correu_electronic = @correu "
                    "AND C.telefonContacte IS NOT NULL AND C.telefonContacte <> '' "
                    "UNION "
                    "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                    "A.telefonContacte AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                    "FROM Usuari UJ "
                    "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                    "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada "
                    "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                    "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                    "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                    "WHERE UJ.correu_electronic = @correu "
                    "AND A.telefonContacte IS NOT NULL AND A.telefonContacte <> ''";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuUsuari);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraLliga::ObtenirTelefonsCapitansPerAdministrador(String^ correuUsuari) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                    "C.telefonContacte AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                    "FROM Usuari UA "
                    "INNER JOIN Administrador A ON A.identificador = UA.identificador "
                    "INNER JOIN Lliga L ON L.idAdministrador = A.identificador "
                    "INNER JOIN Temporada T ON T.idLliga = L.idLliga "
                    "INNER JOIN Equip E ON E.idTemporada = T.idTemporada "
                    "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                    "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                    "WHERE UA.correu_electronic = @correu "
                    "AND C.telefonContacte IS NOT NULL AND C.telefonContacte <> '' "
                    "ORDER BY L.nom, E.nom, UC.nom";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuUsuari);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }


        String^ CercadoraLliga::ObtenirContrasenyaLliga(String^ nomLliga) {
            String^ contrasenya = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT contrasenya FROM Lliga WHERE nom = @nomLliga LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    contrasenya = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return contrasenya;
        }

    }
}