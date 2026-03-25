#include "pch.h"
#include "ConnexioBD.hxx"

using namespace System;
using namespace System::IO;

namespace Playcampus {
    namespace Dades {
        String^ ConnexioBD::ObtenirConnectionString() {
            String^ connectionString = "Server=localhost;Database=playcampus_db;Uid=root;Pwd=;";
            String^ path = "configuracio.env";

            if (!File::Exists(path)) {
                if (File::Exists("../../configuracio.env")) {
                    path = "../../configuracio.env";
                }
                else if (File::Exists("../configuracio.env")) {
                    path = "../configuracio.env";
                }
            }

            try {
                if (File::Exists(path)) {
                    StreamReader^ sr = gcnew StreamReader(path);
                    String^ servidor = sr->ReadLine();
                    String^ port = sr->ReadLine();
                    String^ usuari = sr->ReadLine();
                    String^ password = sr->ReadLine();
                    sr->Close();
                    
                    if (servidor != nullptr && port != nullptr && usuari != nullptr && password != nullptr) {
                        servidor = servidor->Trim();
                        port = port->Trim();
                        usuari = usuari->Trim();
                        password = password->Trim();
                        connectionString = String::Format("Server={0};Port={1};Database=amep06;Uid={2};Pwd={3};",
                            servidor, port, usuari, password);
                    }
                }
            }
            catch (Exception^ ex) {
                Console::WriteLine("Error llegint configuracio.env: " + ex->Message);
            }
            return connectionString;
        }
    }
}
