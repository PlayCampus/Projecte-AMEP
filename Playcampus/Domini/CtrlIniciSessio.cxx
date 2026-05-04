#include "pch.h"
#include "CtrlIniciSessio.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlIniciSessio::CtrlIniciSessio() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlIniciSessio::IniciarSessio(String^ correu, String^ contrasenya) {
            Playcampus::Dades::PassarellaUsuari^ pu = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu( correu);
            if (pu != nullptr) {
                if (pu->GetContrasenya() == contrasenya) {
                    return true;
                }
            }
            return false;
        }

        String^ CtrlIniciSessio::ObtenirTipusUsuari(String^ correu) {
            Playcampus::Dades::PassarellaUsuari^ pu = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu( correu);
            if (pu != nullptr) {
                return pu->GetTipus();
            }
            return "";
        }

        bool CtrlIniciSessio::CapitaTeEquip(String^ correu) {
            MySql::Data::MySqlClient::MySqlConnection^ conn = gcnew MySql::Data::MySqlClient::MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT C.idEquip FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu";
                MySql::Data::MySqlClient::MySqlCommand^ cmd = gcnew MySql::Data::MySqlClient::MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ result = cmd->ExecuteScalar();
                
                if (result != nullptr && result != DBNull::Value && !String::IsNullOrWhiteSpace(result->ToString())) {
                    return true;
                }
            }
            finally {
                delete conn;
            }
            return false;
        }

        bool CtrlIniciSessio::EquipEstaEnLliga(String^ correu) {
            MySql::Data::MySqlClient::MySqlConnection^ conn = gcnew MySql::Data::MySqlClient::MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT E.idTemporada FROM Equip E JOIN Capita C ON E.idEquip = C.idEquip JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu";
                MySql::Data::MySqlClient::MySqlCommand^ cmd = gcnew MySql::Data::MySqlClient::MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ result = cmd->ExecuteScalar();

                if (result != nullptr && result != DBNull::Value && !String::IsNullOrWhiteSpace(result->ToString())) {
                    return true;
                }
            }
            finally {
                delete conn;
            }
            return false;
        }
    }
}
