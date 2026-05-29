#include "pch.h"
#include "PassarellaTemporada.hxx"
#include <stdexcept>
#using <System.Data.dll>
using namespace System::Collections::Generic;

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        static bool EstatFinalitzatLocal(String^ estat) {
            return estat != nullptr &&
                (estat->Equals("Finalitzat", StringComparison::OrdinalIgnoreCase) ||
                    estat->Equals("Finalitzada", StringComparison::OrdinalIgnoreCase) ||
                    estat->Equals("Retirat", StringComparison::OrdinalIgnoreCase) ||
                    estat->Equals("Retirada", StringComparison::OrdinalIgnoreCase));
        }

        static void CopiarEquipsEntreTemporades(String^ connectionString, String^ idTemporadaOrigen, String^ idTemporadaDesti) {
            if (String::IsNullOrEmpty(idTemporadaOrigen) || String::IsNullOrEmpty(idTemporadaDesti) ||
                idTemporadaOrigen->Equals(idTemporadaDesti, StringComparison::OrdinalIgnoreCase)) {
                return;
            }

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "INSERT INTO EquipTemporada (idEquip, idTemporada, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio) "
                    "SELECT DISTINCT et.idEquip, @idTemporadaDesti, 0, 0, 0, 0, 0, 0, 0, 0, 0 "
                    "FROM EquipTemporada et "
                    "LEFT JOIN EquipTemporada etd ON etd.idEquip = et.idEquip AND etd.idTemporada = @idTemporadaDesti "
                    "WHERE et.idTemporada = @idTemporadaOrigen "
                    "AND etd.idEquip IS NULL";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporadaOrigen", idTemporadaOrigen);
                cmd->Parameters->AddWithValue("@idTemporadaDesti", idTemporadaDesti);
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }


        PassarellaTemporada::PassarellaTemporada(String^ connString) {
            connectionString = connString;
        }

        PassarellaTemporada::PassarellaTemporada(String^ connString, String^ idTemp, String^ idLlig, DateTime dInici, DateTime dFi, String^ est) {
            connectionString = connString;
            idTemporada = idTemp;
            idLliga = idLlig;
            dataInici = dInici;
            dataFi = dFi;
            estat = est;
        }

        //Getters
        String^ PassarellaTemporada::GetIdTemporada() { return idTemporada; }
        String^ PassarellaTemporada::GetIdLliga() { return idLliga; }
        DateTime PassarellaTemporada::GetDataInici() { return dataInici; }
        DateTime PassarellaTemporada::GetDataFi() { return dataFi; }
        String^ PassarellaTemporada::GetEstat() { return estat; }


        void PassarellaTemporada::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO Temporada (idTemporada, idLliga, dataInici, dataFi, estat) "
                    "VALUES (@idTemp, @idLliga, @dataInici, @dataFi, @estat)";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemp", idTemporada);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                // Depenent de com sigui la columna a la teva BD de MySQL escull format ShortDate
                cmd->Parameters->AddWithValue("@dataInici", dataInici.ToString("yyyy-MM-dd"));
                cmd->Parameters->AddWithValue("@dataFi", dataFi.ToString("yyyy-MM-dd"));
                cmd->Parameters->AddWithValue("@estat", estat);

                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaTemporada::ActualitzarEstats(String^ connStr) {
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ queryT = "UPDATE Temporada SET estat = CASE "
                    "WHEN NOW() >= dataInici AND NOW() <= dataFi AND estat != 'Finalitzat' THEN 'EnCurs' "
                    "WHEN NOW() > dataFi THEN 'Finalitzat' "
                    "ELSE estat END "
                    "WHERE (NOW() >= dataInici AND NOW() <= dataFi AND estat != 'EnCurs') "
                    "OR (NOW() > dataFi AND estat != 'Finalitzat')";

                MySqlCommand^ cmd = gcnew MySqlCommand(queryT, conn);
                cmd->ExecuteNonQuery();

                // Si ja hi ha una temporada nova creada i encara no te equips,
                // copiem els equips de la temporada anterior amb estadistiques a zero.
                String^ queryMigracio =
                    "INSERT INTO EquipTemporada (idEquip, idTemporada, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio) "
                    "SELECT DISTINCT etOrigen.idEquip, tNova.idTemporada, 0, 0, 0, 0, 0, 0, 0, 0, 0 "
                    "FROM Temporada tNova "
                    "INNER JOIN Temporada tOrigen ON tOrigen.idLliga = tNova.idLliga "
                    "INNER JOIN EquipTemporada etOrigen ON etOrigen.idTemporada = tOrigen.idTemporada "
                    "LEFT JOIN EquipTemporada etDesti ON etDesti.idEquip = etOrigen.idEquip AND etDesti.idTemporada = tNova.idTemporada "
                    "WHERE tNova.idTemporada <> tOrigen.idTemporada "
                    "AND tNova.estat <> 'Finalitzat' "
                    "AND tOrigen.idTemporada = ("
                    "   SELECT t2.idTemporada "
                    "   FROM Temporada t2 "
                    "   INNER JOIN EquipTemporada et2 ON et2.idTemporada = t2.idTemporada "
                    "   WHERE t2.idLliga = tNova.idLliga AND t2.idTemporada <> tNova.idTemporada "
                    "   GROUP BY t2.idTemporada, t2.dataInici, t2.dataFi, t2.estat "
                    "   ORDER BY CASE WHEN t2.dataInici <= tNova.dataInici THEN 0 ELSE 1 END, t2.dataInici DESC, t2.dataFi DESC "
                    "   LIMIT 1"
                    ") "
                    "AND etDesti.idEquip IS NULL";
                MySqlCommand^ cmdMigracio = gcnew MySqlCommand(queryMigracio, conn);
                cmdMigracio->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }


        List<Dictionary<String^, String^>^>^ PassarellaTemporada::ObtenirDictTemporadesPerLliga(String^ nomLliga)
        {
            List<Dictionary<String^, String^>^>^ temporades = gcnew List<Dictionary<String^, String^>^>();

            String^ query = "SELECT t.IdTemporada, t.DataInici, t.DataFi, t.Estat "
                "FROM Temporada t "
                "INNER JOIN Lliga l ON t.IdLliga = l.IdLliga "
                "WHERE l.Nom = @NomLliga";


            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@NomLliga", nomLliga);

            try
            {
                conn->Open();

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read())
                {
                    Dictionary<String^, String^>^ dict = gcnew Dictionary<String^, String^>();
                    dict["idTemporada"] = reader["IdTemporada"]->ToString();
                    dict["dataInici"] = reader["DataInici"]->ToString();
                    dict["dataFi"] = reader["DataFi"]->ToString();
                    dict["estat"] = reader["Estat"]->ToString();
                    temporades->Add(dict);
                }
                reader->Close();
            }
            finally
            {
                conn->Close();
            }

            return temporades;
        }

        PassarellaTemporada^ PassarellaTemporada::Llegeix(System::String^ connectionString, System::String^ idTemporada)
        {
            PassarellaTemporada^ temporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try
            {
                conn->Open();
                String^ query = "SELECT idTemporada, idLliga, dataInici, dataFi, estat FROM Temporada WHERE idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read())
                {
                    String^ idTemp = reader["idTemporada"]->ToString();
                    String^ idLlig = reader["idLliga"]->ToString();
                    DateTime dInici = Convert::ToDateTime(reader["dataInici"]);
                    DateTime dFi = Convert::ToDateTime(reader["dataFi"]);
                    String^ est = reader["estat"]->ToString();

                    temporada = gcnew PassarellaTemporada(connectionString, idTemp, idLlig, dInici, dFi, est);
                }
                reader->Close();
            }
            finally
            {
                conn->Close();
            }

            return temporada;
        }

        String^ PassarellaTemporada::ObtenirIdTemporadaMesRecent(String^ idLliga)
        {
            PassarellaTemporada::ActualitzarEstats(connectionString);
            String^ idTemporadaMesRecent = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try
            {
                conn->Open();
                String^ query =
                    "SELECT idTemporada FROM Temporada "
                    "WHERE idLliga = @idLliga "
                    "ORDER BY CASE "
                    "WHEN estat = 'EnCurs' THEN 0 "
                    "WHEN estat <> 'Finalitzat' THEN 1 "
                    "ELSE 2 END, dataInici DESC LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idTemporadaMesRecent = result->ToString();
                }
            }
            finally
            {
                conn->Close();
            }

            return idTemporadaMesRecent;
        }


        void PassarellaTemporada::InicialitzarEquipsNovaTemporada(String^ idLliga, String^ idTemporadaNova)
        {
            if (String::IsNullOrEmpty(idLliga) || String::IsNullOrEmpty(idTemporadaNova)) {
                return;
            }

            String^ idTemporadaOrigen = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT tAnt.idTemporada "
                    "FROM Temporada tAnt "
                    "INNER JOIN Temporada tNova ON tNova.idTemporada = @idTemporadaNova "
                    "WHERE tAnt.idLliga = @idLliga "
                    "AND tAnt.idTemporada <> @idTemporadaNova "
                    "AND EXISTS (SELECT 1 FROM EquipTemporada et WHERE et.idTemporada = tAnt.idTemporada) "
                    "ORDER BY CASE WHEN tAnt.dataInici <= tNova.dataInici THEN 0 ELSE 1 END, "
                    "CASE WHEN tAnt.estat = 'EnCurs' THEN 0 WHEN tAnt.estat = 'Finalitzat' THEN 1 ELSE 2 END, "
                    "tAnt.dataInici DESC, tAnt.dataFi DESC "
                    "LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@idTemporadaNova", idTemporadaNova);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idTemporadaOrigen = result->ToString();
                }
            }
            finally {
                conn->Close();
            }

            CopiarEquipsEntreTemporades(connectionString, idTemporadaOrigen, idTemporadaNova);
        }

        void PassarellaTemporada::InicialitzarEquipsTemporadaSeguent(String^ idLliga, String^ idTemporadaOrigen)
        {
            if (String::IsNullOrEmpty(idLliga) || String::IsNullOrEmpty(idTemporadaOrigen)) {
                return;
            }

            String^ idTemporadaDesti = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT tDesti.idTemporada "
                    "FROM Temporada tDesti "
                    "INNER JOIN Temporada tOrigen ON tOrigen.idTemporada = @idTemporadaOrigen "
                    "WHERE tDesti.idLliga = @idLliga "
                    "AND tDesti.idTemporada <> @idTemporadaOrigen "
                    "AND tDesti.estat <> 'Finalitzat' "
                    "ORDER BY CASE WHEN tDesti.dataInici >= tOrigen.dataInici THEN 0 ELSE 1 END, tDesti.dataInici ASC "
                    "LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@idTemporadaOrigen", idTemporadaOrigen);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idTemporadaDesti = result->ToString();
                }
            }
            finally {
                conn->Close();
            }

            CopiarEquipsEntreTemporades(connectionString, idTemporadaOrigen, idTemporadaDesti);
        }


        void PassarellaTemporada::RetirarTemporada(String^ idLliga)
        {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Actualizamos a 'Finalitzat' solo la temporada que esté 'EnCurs' para esta liga
                String^ query = "UPDATE Temporada SET estat = 'Finalitzat' WHERE idLliga = @idLliga AND estat = 'EnCurs'";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);

                int filesInfectades = cmd->ExecuteNonQuery();
                if (filesInfectades == 0) {
                    throw gcnew Exception("No s'ha trobat cap temporada en curs per a aquesta lliga.");
                }
            }
            finally {
                conn->Close();
            }
        }


    }
}
