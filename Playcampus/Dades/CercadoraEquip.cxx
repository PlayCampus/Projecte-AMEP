
#include "pch.h"
#include "CercadoraEquip.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

        CercadoraEquip::CercadoraEquip(String^ connStr) {
            connectionString = connStr;
        }
        List<String^>^ CercadoraEquip::ObtenirIdsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ idsEquips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Equip WHERE idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    idsEquips->Add(reader["idEquip"]->ToString());
                }
            }
            finally {
                conn->Close();
            }
            return idsEquips;
		}
    }
}
