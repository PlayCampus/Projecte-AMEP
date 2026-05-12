#include "pch.h"
#include "CercadoraTemporada.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

        CercadoraTemporada::CercadoraTemporada(String^ connStr) {
            connectionString = connStr;
        }

        List<Dictionary<String^, String^>^>^ CercadoraTemporada::ObtenirTemporadesAdmin(String^ correuAdmin) {

            // ACTUALITZEM ESTATS ABANS DE CONSULTAR
            PassarellaTemporada::ActualitzarEstats(connectionString);


            List<Dictionary<String^, String^>^>^ llista = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                String^ query = "SELECT t.idTemporada, t.dataInici, t.dataFi, t.estat "
                    "FROM Temporada t "
                    "INNER JOIN Lliga ll ON t.idLliga = ll.idLliga "
                    "INNER JOIN Usuari u ON ll.idAdministrador = u.identificador "
                    "WHERE u.correu_electronic = @correuAdmin";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ temp = gcnew Dictionary<String^, String^>();
                    temp["idTemporada"] = reader["idTemporada"]->ToString();
                    temp["dataInici"] = Convert::ToDateTime(reader["dataInici"]).ToString("dd/MM/yyyy HH:mm");
                    temp["dataFi"] = Convert::ToDateTime(reader["dataFi"]).ToString("dd/MM/yyyy HH:mm");
                    temp["estat"] = reader["estat"]->ToString();
                    llista->Add(temp);
                }
            }
            finally {
                conn->Close();
            }

            return llista;
        }

        String^ CercadoraTemporada::ObtenirIdTemporadaEnCurs(String^ idLliga) {

            

			String^ idTemporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga AND estat = 'EnCurs'";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr) {
                    idTemporada = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
			return idTemporada;

        }
    }
}
