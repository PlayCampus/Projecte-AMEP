#include "pch.h"
#include "CtrlEnregistrarEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlEnregistrarEquip::CtrlEnregistrarEquip() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlEnregistrarEquip::EnregistrarEquip(String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, String^ tipusUsuari, String^ correuUsuari) {
            // Verificar que l'usuari és un capità
            if (tipusUsuari->ToLower() != "capita" && tipusUsuari->ToLower() != "capità") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden enregistrar un equip.");
            }

            String^ idCapita = nullptr;
            if (!String::IsNullOrEmpty(correuUsuari)) {
                Playcampus::Dades::PassarellaUsuari^ capUser = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu( correuUsuari);
                if (capUser != nullptr && capUser->GetIdentificador() != nullptr) {
                    idCapita = capUser->GetIdentificador()->Trim();
                }
            }

            // Guardar a la base de dades utilitzant la passarella
            try {
                Playcampus::Dades::PassarellaEquip^ pe = gcnew Playcampus::Dades::PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport);
                pe->Insereix();
                
                // Actualitzem l'ID de l'equip al Capita a la base de dades
                if (idCapita != nullptr) {
                    MySql::Data::MySqlClient::MySqlConnection^ conn = gcnew MySql::Data::MySqlClient::MySqlConnection(connectionString);
                    try {
                        conn->Open();
                        // Assegurem que s'agafa el ID generat
                        String^ realIdEquip = pe->GetIdEquip();
                        if (String::IsNullOrEmpty(realIdEquip)) {
                            realIdEquip = idEquip;
                        }
                        String^ queryUpdateCapita = "UPDATE Capita SET idEquip = @idEquip WHERE identificador = @idCapita";
                        MySql::Data::MySqlClient::MySqlCommand^ cmd = gcnew MySql::Data::MySqlClient::MySqlCommand(queryUpdateCapita, conn);
                        cmd->Parameters->AddWithValue("@idEquip", realIdEquip);
                        cmd->Parameters->AddWithValue("@idCapita", idCapita);
                        int filesAfectades = cmd->ExecuteNonQuery();
                        if (filesAfectades != 1) {
                            throw gcnew Exception("No s'ha pogut actualitzar el capita amb l'equip creat.");
                        }

                        String^ queryVerificacio = "SELECT COUNT(*) FROM Capita WHERE identificador = @idCapita AND idEquip = @idEquip";
                        MySql::Data::MySqlClient::MySqlCommand^ cmdVerificacio = gcnew MySql::Data::MySqlClient::MySqlCommand(queryVerificacio, conn);
                        cmdVerificacio->Parameters->AddWithValue("@idCapita", idCapita);
                        cmdVerificacio->Parameters->AddWithValue("@idEquip", realIdEquip);
                        int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                        if (filesVerificades != 1) {
                            throw gcnew Exception("La base de dades no ha confirmat l'assignacio de l'equip al capita.");
                        }
                    }
                    finally {
                        delete conn;
                    }
                }
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Error al inserir l'equip: " + ex->Message);
            }
        }
    }
}
