#include "pch.h"
#include "CercadoraLliga.hxx"
#include "PassarellaTemporada.hxx"

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


        DataTable^ CercadoraLliga::ObtenirTotesLliguesEstadistiques() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT L.idLliga AS IdLliga, L.nom AS NomLliga, L.disciplina AS Esport, "
                    "IFNULL(U.nom, '') AS Administrador, COUNT(DISTINCT T.idTemporada) AS Temporades "
                    "FROM Lliga L "
                    "LEFT JOIN Administrador A ON A.identificador = L.idAdministrador "
                    "LEFT JOIN Usuari U ON U.identificador = A.identificador "
                    "LEFT JOIN Temporada T ON T.idLliga = L.idLliga "
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

        DataTable^ CercadoraLliga::CercarLliguesPerNom(String^ textCerca) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT L.idLliga AS IdLliga, L.nom AS NomLliga, L.disciplina AS Esport, "
                    "IFNULL(U.nom, '') AS Administrador, COUNT(DISTINCT T.idTemporada) AS Temporades "
                    "FROM Lliga L "
                    "LEFT JOIN Administrador A ON A.identificador = L.idAdministrador "
                    "LEFT JOIN Usuari U ON U.identificador = A.identificador "
                    "LEFT JOIN Temporada T ON T.idLliga = L.idLliga "
                    "WHERE L.nom LIKE @textCerca "
                    "GROUP BY L.idLliga, L.nom, L.disciplina, U.nom "
                    "ORDER BY L.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                String^ patroCerca = gcnew String(L"%");
                patroCerca += textCerca;
                patroCerca += gcnew String(L"%");
                cmd->Parameters->AddWithValue("@textCerca", patroCerca);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
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
            PassarellaTemporada::ActualitzarEstats(connectionString);
            String^ idLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT T.idLliga FROM EquipTemporada ET "
                    "INNER JOIN Equip E ON E.idEquip = ET.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = ET.idTemporada "
                    "INNER JOIN Capita C ON E.idEquip = C.idEquip "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu "
                    "ORDER BY CASE WHEN T.estat = 'EnCurs' THEN 0 WHEN T.estat <> 'Finalitzat' THEN 1 ELSE 2 END, T.dataInici DESC "
                    "LIMIT 1";
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
            PassarellaTemporada::ActualitzarEstats(connectionString);
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
                    "ET.partitsJugats AS PartitsJugats, ET.victories AS Victories, ET.empats AS Empats, "
                    "ET.derrotes AS Derrotes, ET.punts AS Punts "
                    "FROM Lliga L "
                    "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "INNER JOIN Temporada T ON T.idLliga = L.idLliga "
                    "AND T.idTemporada = ("
                    "    SELECT T2.idTemporada FROM Temporada T2 "
                    "    WHERE T2.idLliga = L.idLliga "
                    "    ORDER BY CASE WHEN T2.estat = 'EnCurs' THEN 0 WHEN T2.estat <> 'Finalitzat' THEN 1 ELSE 2 END, T2.dataInici DESC, T2.dataFi DESC "
                    "    LIMIT 1"
                    ") "
                    "INNER JOIN EquipTemporada ET ON ET.idTemporada = T.idTemporada "
                    "INNER JOIN Equip E ON E.idEquip = ET.idEquip "
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
            PassarellaTemporada::ActualitzarEstats(connectionString);
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.nom AS Equip, ET.partitsJugats AS PJ, ET.victories AS V, ET.empats AS E, "
                    "ET.derrotes AS D, ET.golsAFavor AS GF, ET.golsEnContra AS GC, "
                    "ET.diferenciaGols AS DG, ET.punts AS Punts "
                    "FROM EquipTemporada ET "
                    "INNER JOIN Equip E ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "WHERE T.idLliga = @idLliga "
                    "AND T.idTemporada = ("
                    "    SELECT T2.idTemporada FROM Temporada T2 "
                    "    WHERE T2.idLliga = @idLliga "
                    "    ORDER BY CASE WHEN T2.estat = 'EnCurs' THEN 0 WHEN T2.estat <> 'Finalitzat' THEN 1 ELSE 2 END, T2.dataInici DESC, T2.dataFi DESC "
                    "    LIMIT 1"
                    ") "
                    "ORDER BY ET.punts DESC, ET.diferenciaGols DESC, E.nom ASC";
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

        DataTable^ CercadoraLliga::ObtenirClassificacioLligaTemporada(String^ idLliga, String^ idTemporada) {
            PassarellaTemporada::ActualitzarEstats(connectionString);
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
                    "SELECT E.nom AS Equip, ET.partitsJugats AS PJ, ET.victories AS V, ET.empats AS E, "
                    "ET.derrotes AS D, ET.golsAFavor AS " + labelFavor + ", ET.golsEnContra AS " + labelContra + ", "
                    "ET.diferenciaGols AS " + labelDif + ", ET.punts AS Punts "
                    "FROM EquipTemporada ET "
                    "INNER JOIN Equip E ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "WHERE T.idLliga = @idLliga AND T.idTemporada = @idTemporada "
                    "ORDER BY ET.punts DESC, ET.diferenciaGols DESC, E.nom ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }


        DataTable^ CercadoraLliga::ObtenirClassificacioLligaSeguida(String^ idLliga, String^ idTemporada) {
            PassarellaTemporada::ActualitzarEstats(connectionString);
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
                    "SELECT E.nom AS Equip, ET.partitsJugats AS PJ, ET.victories AS V, ET.empats AS E, "
                    "ET.derrotes AS D, ET.golsAFavor AS " + labelFavor + ", ET.golsEnContra AS " + labelContra + ", "
                    "ET.diferenciaGols AS " + labelDif + ", ET.punts AS Punts "
                    "FROM EquipTemporada ET "
                    "INNER JOIN Equip E ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "WHERE T.idLliga = @idLliga AND T.idTemporada = @idTemporada "
                    "ORDER BY ET.punts DESC, ET.diferenciaGols DESC, E.nom ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }


        DataTable^ CercadoraLliga::ObtenirEstatLligues() {
            PassarellaTemporada::ActualitzarEstats(connectionString);
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT L.nom AS Lliga, L.disciplina AS Esport, "
                    "IFNULL(U.nom, '') AS Administrador, COUNT(DISTINCT ET.idEquip) AS NumEquips "
                    "FROM Lliga L "
                    "LEFT JOIN Temporada T ON T.idLliga = L.idLliga "
                    "AND T.idTemporada = ("
                    "    SELECT T2.idTemporada FROM Temporada T2 "
                    "    WHERE T2.idLliga = L.idLliga "
                    "    ORDER BY CASE WHEN T2.estat = 'EnCurs' THEN 0 WHEN T2.estat <> 'Finalitzat' THEN 1 ELSE 2 END, T2.dataInici DESC, T2.dataFi DESC "
                    "    LIMIT 1"
                    ") "
                    "LEFT JOIN EquipTemporada ET ON ET.idTemporada = T.idTemporada "
                    "LEFT JOIN Equip E ON E.idEquip = ET.idEquip "
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
            PassarellaTemporada::ActualitzarEstats(connectionString);
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT IFNULL(L.nom, 'Sense lliga') AS Lliga, E.nom AS Equip, E.esport AS Esport, "
                    "ET.partitsJugats AS PartitsJugats, ET.victories AS Victories, ET.empats AS Empats, "
                    "ET.derrotes AS Derrotes, ET.punts AS Punts, ET.golsAFavor AS GolsAFavor, "
                    "ET.golsEnContra AS GolsEnContra, ET.diferenciaGols AS DiferenciaGols, "
                    "ET.posicioClassificacio AS PosicioClassificacio "
                    "FROM Equip E "
                    "LEFT JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "LEFT JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "LEFT JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE T.idTemporada IS NULL OR T.idTemporada = ("
                    "    SELECT T2.idTemporada FROM Temporada T2 "
                    "    WHERE T2.idLliga = T.idLliga "
                    "    ORDER BY CASE WHEN T2.estat = 'EnCurs' THEN 0 WHEN T2.estat <> 'Finalitzat' THEN 1 ELSE 2 END, T2.dataInici DESC, T2.dataFi DESC "
                    "    LIMIT 1"
                    ") "
                    "ORDER BY IFNULL(L.nom, ''), ET.posicioClassificacio ASC, ET.punts DESC, E.nom ASC";
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
                    "INNER JOIN EquipTemporada ET ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = ET.idTemporada "
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
                    "INNER JOIN EquipTemporada ET ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = ET.idTemporada "
                    "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                    "WHERE UJ.correu_electronic = @correu "
                    "AND C.telefonContacte IS NOT NULL AND C.telefonContacte <> '' "
                    "UNION "
                    "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                    "A.telefonContacte AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                    "FROM Usuari UJ "
                    "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                    "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                    "INNER JOIN EquipTemporada ET ON ET.idEquip = E.idEquip "
                    "INNER JOIN Temporada T ON T.idTemporada = ET.idTemporada "
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
                    "INNER JOIN EquipTemporada ET ON T.idTemporada = ET.idTemporada "
                    "INNER JOIN Equip E ON ET.idEquip = E.idEquip "
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