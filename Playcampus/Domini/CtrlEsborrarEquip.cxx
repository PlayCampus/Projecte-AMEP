#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include "CtrlEsborrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include <stdexcept>

using namespace MySql::Data::MySqlClient;
using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlEsborrarEquip::CtrlEsborrarEquip() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEsborrarEquip::EsborrarEquip(String^ correuCapita) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ idEquipRecuperat = "";
            try {
                conn->Open();
                String^ queryCap = "SELECT C.idEquip FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu";
                MySqlCommand^ cmdCap = gcnew MySqlCommand(queryCap, conn);
                cmdCap->Parameters->AddWithValue("@correu", correuCapita);
                Object^ idEquipObj = cmdCap->ExecuteScalar();

                if (idEquipObj == nullptr || idEquipObj == DBNull::Value || String::IsNullOrWhiteSpace(idEquipObj->ToString())) {
                    throw gcnew Exception("Aquest capita no te un equip actiu per esborrar.");
                }
                idEquipRecuperat = idEquipObj->ToString()->Trim();
            }
            finally {
                delete conn;
            }
            Playcampus::Dades::PassarellaEquip^ equipDB = Playcampus::Dades::PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB != nullptr) {
                equipDB->Esborra();

                // Borrar l'idEquip del Capita
                MySqlConnection^ connUpdate = gcnew MySqlConnection(connectionString);
                try {
                    connUpdate->Open();
                    String^ queryUpdate = "UPDATE Capita C JOIN Usuari U ON C.identificador = U.identificador SET C.idEquip = NULL WHERE U.correu_electronic = @correu";
                    MySqlCommand^ cmdUpdate = gcnew MySqlCommand(queryUpdate, connUpdate);
                    cmdUpdate->Parameters->AddWithValue("@correu", correuCapita);
                    int filesAfectades = cmdUpdate->ExecuteNonQuery();
                    if (filesAfectades != 1) {
                        throw gcnew Exception("No s'ha pogut desvincular l'equip del capita.");
                    }

                    String^ queryVerificacio = "SELECT COUNT(*) FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu AND C.idEquip IS NULL";
                    MySqlCommand^ cmdVerificacio = gcnew MySqlCommand(queryVerificacio, connUpdate);
                    cmdVerificacio->Parameters->AddWithValue("@correu", correuCapita);
                    int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                    if (filesVerificades != 1) {
                        throw gcnew Exception("La base de dades no ha confirmat que el capita hagi quedat sense equip.");
                    }
                }
                finally {
                    delete connUpdate;
                }
            } else {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }
        }
    }
}
