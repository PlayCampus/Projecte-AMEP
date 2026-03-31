#include "pch.h"
#include "CtrlUnirEquipLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include <stdexcept>

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {

        CtrlUnirEquipLliga::CtrlUnirEquipLliga() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlUnirEquipLliga::ComprovarSiLligaExisteix(String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ idLliga = nullptr;
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idLliga = result->ToString();
                }
            }
            finally {
                delete conn;
            }
            return idLliga;
        }

        bool CtrlUnirEquipLliga::ValidarContrasenyaLliga(String^ nomLliga, String^ pass) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            bool isValid = false;
            try {
                conn->Open();
                String^ query = "SELECT contrasenya FROM Lliga WHERE nom = @nomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    String^ currentPass = result->ToString();
                    isValid = (currentPass == pass);
                }
            }
            finally {
                delete conn;
            }
            return isValid;
        }

        String^ CtrlUnirEquipLliga::VincularEquip(String^ correuCapita, String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            String^ missatgeExit = "";
            try {
                conn->Open();

                // 1. Obtenir l'idEquip associat al Capità a través del correu
                String^ queryCap = "SELECT C.idEquip FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu";
                MySqlCommand^ cmdCap = gcnew MySqlCommand(queryCap, conn);
                cmdCap->Parameters->AddWithValue("@correu", correuCapita);
                Object^ idEquipObj = cmdCap->ExecuteScalar();

                if (idEquipObj == nullptr || idEquipObj == DBNull::Value) {
                    throw gcnew Exception("Aquest capità no té un equip actiu. Primer enregistra't un.");
                }
                String^ idEquipRecuperat = idEquipObj->ToString();

                // 2. Obtenir ID de la Lliga
                String^ idLligaEncontrado = ComprovarSiLligaExisteix(nomLliga);
                if (idLligaEncontrado == nullptr) {
                    throw gcnew Exception("La lliga no existeix.");
                }

                // 3. Modificar l'Equip mitjançant la seva Passarella
                Playcampus::Dades::PassarellaEquip^ equipDB = Playcampus::Dades::PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
                if (equipDB != nullptr) {
                    equipDB->SetIdLliga(idLligaEncontrado);
                    equipDB->Modifica();
                    missatgeExit = "L'equip " + equipDB->GetNom() + " ha sigut enregistrat amb èxit a la lliga " + nomLliga + ".";
                }
                else {
                    throw gcnew Exception("Equip no trobat a la base de dades.");
                }
            }
            finally {
                delete conn;
            }
            return missatgeExit;
        }
    }
}