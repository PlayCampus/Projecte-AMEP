#include "pch.h"
#include "UsuariTx.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        UsuariTx::UsuariTx(String^ connectionString) {
            this->connectionString = connectionString;
        }

        void UsuariTx::CrearUsuari(String^ identificador, String^ nom, String^ contrasenya, DateTime dataRegistre, String^ correuElectronic, String^ tipus, String^ dadaExtra1, String^ dadaExtra2) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlTransaction^ trans = conn->BeginTransaction();
                try {
                    String^ queryPrincipal = "INSERT INTO Usuari (identificador, nom, contrasenya, data_registre, correu_electronic, Tipus) VALUES (@id, @nom, @contrasenya, @dataReg, @correu, @tipus)";
                    MySqlCommand^ cmd = gcnew MySqlCommand(queryPrincipal, conn, trans);
                    cmd->Parameters->AddWithValue("@id", identificador);
                    cmd->Parameters->AddWithValue("@nom", nom);
                    cmd->Parameters->AddWithValue("@contrasenya", contrasenya);
                    cmd->Parameters->AddWithValue("@dataReg", dataRegistre);
                    cmd->Parameters->AddWithValue("@correu", correuElectronic);
                    cmd->Parameters->AddWithValue("@tipus", tipus);
                    cmd->ExecuteNonQuery();

                    if (tipus == "Administrador") {
                        String^ queryAdmin = "INSERT INTO Administrador (identificador, telefonContacte) VALUES (@id, @tel)";
                        MySqlCommand^ cmdAdm = gcnew MySqlCommand(queryAdmin, conn, trans);
                        cmdAdm->Parameters->AddWithValue("@id", identificador);
                        cmdAdm->Parameters->AddWithValue("@tel", dadaExtra1);
                        cmdAdm->ExecuteNonQuery();
                    }
                    else if (tipus == "Capita") {
                        String^ queryCapita = "INSERT INTO Capita (identificador, telefonContacte, idEquip, validatPerAdmin) VALUES (@id, @tel, @idEquip, false)";
                        MySqlCommand^ cmdCap = gcnew MySqlCommand(queryCapita, conn, trans);
                        cmdCap->Parameters->AddWithValue("@id", identificador);
                        cmdCap->Parameters->AddWithValue("@tel", dadaExtra1);
                        cmdCap->Parameters->AddWithValue("@idEquip", dadaExtra2);
                        cmdCap->ExecuteNonQuery();
                    }
                    else if (tipus == "Estudiant") {
                        String^ queryEstud = "INSERT INTO Estudiant (identificador, carrera) VALUES (@id, @carrera)";
                        MySqlCommand^ cmdEst = gcnew MySqlCommand(queryEstud, conn, trans);
                        cmdEst->Parameters->AddWithValue("@id", identificador);
                        cmdEst->Parameters->AddWithValue("@carrera", dadaExtra1);
                        cmdEst->ExecuteNonQuery();
                    }
                    trans->Commit();
                }
                catch (Exception^ ex) {
                    trans->Rollback();
                    Console::WriteLine(ex->Message);
                }
            }
            catch (Exception^ ex) {
                Console::WriteLine(ex->Message);
            }
            finally {
                conn->Close();
            }
        }

        DataTable^ UsuariTx::ObtenirUsuaris() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            DataTable^ taulaUsuaris = gcnew DataTable();
            try {
                conn->Open();
                String^ query = "SELECT * FROM Usuari";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);

                adapter->Fill(taulaUsuaris);
            }
            catch (Exception^ ex) {
                Console::WriteLine(ex->Message);
            }
            finally {
                conn->Close();
            }
            return taulaUsuaris;
        }

        bool UsuariTx::IniciarSessio(String^ correu, String^ contrasenya) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            bool esValid = false;
            try {
                conn->Open();
                String^ query = "SELECT COUNT(1) FROM Usuari WHERE correu_electronic = @correu AND contrasenya = @contrasenya";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                cmd->Parameters->AddWithValue("@contrasenya", contrasenya);

                int count = Convert::ToInt32(cmd->ExecuteScalar());
                if (count > 0) {
                    esValid = true;
                }
            }
            catch (Exception^ ex) {
                Console::WriteLine(ex->Message);
            }
            finally {
                conn->Close();
            }
            return esValid;
        }

        void UsuariTx::ConvertirACapita(String^ idUsuari) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlTransaction^ trans = conn->BeginTransaction();
                try {
                    String^ queryType = "UPDATE Usuari SET Tipus = 'Capita' WHERE identificador = @id";
                    MySqlCommand^ cmdType = gcnew MySqlCommand(queryType, conn, trans);
                    cmdType->Parameters->AddWithValue("@id", idUsuari);
                    cmdType->ExecuteNonQuery();

                    String^ check = "SELECT COUNT(1) FROM Capita WHERE identificador = @id";
                    MySqlCommand^ cmdCheck = gcnew MySqlCommand(check, conn, trans);
                    cmdCheck->Parameters->AddWithValue("@id", idUsuari);
                    int count = Convert::ToInt32(cmdCheck->ExecuteScalar());
                    
                    if (count == 0) {
                        String^ ins = "INSERT INTO Capita (identificador, validatPerAdmin) VALUES (@id, false)";
                        MySqlCommand^ cmdIns = gcnew MySqlCommand(ins, conn, trans);
                        cmdIns->Parameters->AddWithValue("@id", idUsuari);
                        cmdIns->ExecuteNonQuery();
                    }

                    trans->Commit();
                } catch(Exception^ ex) {
                    trans->Rollback();
                    Console::WriteLine(ex->Message);
                }
            }
            catch (Exception^ ex) {
                Console::WriteLine(ex->Message);
            }
            finally {
                conn->Close();
            }
        }
    }
}
