#include "pch.h"
#include "CercadoraConvocatoria.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {
        CercadoraConvocatoria::CercadoraConvocatoria(String^ connStr) {
            this->connectionString = connStr;
        }

        DataTable^ CercadoraConvocatoria::CercaJugadorsEquip(String^ idEquip) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Assumim que existeix una taula Jugador amb un identificador i que pot estar relacionat amb un equip (o per Capita/Usuari etc)
                // Aquí fas una query genèrica assumint els jugadors d'un equip o un esquema simila r
                String^ query = "SELECT identificador, nom FROM Usuari JOIN Jugador ON Usuari.identificador = Jugador.identificador WHERE Jugador.idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                da->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }
        
        DataTable^ CercadoraConvocatoria::CercaConvocatoriesEquip(String^ idEquip) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                
                String^ query = "SELECT idConvocatoria, idPartit FROM Convocatoria WHERE idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                da->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }
    }
}
