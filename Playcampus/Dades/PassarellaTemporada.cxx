#include "pch.h"
#include "PassarellaTemporada.hxx"
#include <stdexcept>
#using <System.Data.dll>
using namespace System::Collections::Generic;

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

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
            //  busca la temporada por ID y devuelve el objeto correspondiente
            PassarellaTemporada^ temporada = nullptr;

            // buscar la temporada en la base de datos usando connectionString e idTemporada
            // Si se encuentra, inicializa y devuelve el objeto; si no, devuelve nullptr

            return temporada;
        }

        String^ PassarellaTemporada::ObtenirIdTemporadaMesRecent(String^ idLliga)
        {
            String^ idTemporadaMesRecent = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try
            {
                conn->Open();
                String^ query = "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC LIMIT 1";
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
