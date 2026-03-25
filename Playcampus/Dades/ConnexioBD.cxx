#include "pch.h"
#include "ConnexioBD.hxx"

using namespace System;
using namespace System::IO;

namespace Playcampus {
    namespace Dades {
        String^ ConnexioBD::ObtenirConnectionString() {
            String^ connectionString = "Server=localhost;Database=playcampus_db;Uid=root;Pwd=;";
            try {
                if (File::Exists("configuracio.env")) {
                    StreamReader^ sr = gcnew StreamReader("configuracio.env");
                    String^ servidor = sr->ReadLine();
                    String^ port = sr->ReadLine();
                    String^ usuari = sr->ReadLine();
                    String^ password = sr->ReadLine();
                    sr->Close();
                    
                    if (servidor != nullptr && port != nullptr && usuari != nullptr && password != nullptr) {
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
