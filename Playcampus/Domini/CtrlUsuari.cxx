#include "pch.h"
#include "CtrlUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlUsuari::CtrlUsuari() {
            connectionString = "Server=localhost;Database=playcampus_db;Uid=root;Pwd=;";
        }

        CtrlUsuari^ CtrlUsuari::GetInstancia() {
            if (instancia == nullptr)
                instancia = gcnew CtrlUsuari();
            return instancia;
        }

        bool CtrlUsuari::IniciarSessio(String^ correu, String^ contrasenya) {
            Playcampus::Dades::PassarellaUsuari^ pu = Playcampus::Dades::PassarellaUsuari::LlegeixPerCorreu(connectionString, correu);
            if (pu != nullptr) {
                if (pu->GetContrasenya() == contrasenya) {
                    return true;
                }
            }
            return false;
        }

        void CtrlUsuari::CrearUsuari(String^ id, String^ nom, String^ pass, DateTime dataReg, String^ correu, String^ tipus) {
            Playcampus::Dades::PassarellaUsuari^ pu = gcnew Playcampus::Dades::PassarellaUsuari(connectionString, id, nom, pass, dataReg, correu, tipus);
            pu->Insereix();
        }
    }
}
