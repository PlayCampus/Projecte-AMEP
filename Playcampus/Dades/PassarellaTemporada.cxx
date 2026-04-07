#include "pch.h"
#include "PassarellaTemporada.hxx"
#include <stdexcept>
#using <System.Data.dll>
using namespace System::Collections::Generic;

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        // NUEVA IMPLEMENTACIÓN del constructor
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
 
    }
}