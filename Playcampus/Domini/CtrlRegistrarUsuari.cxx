#include "pch.h"
#include "CtrlRegistrarUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlRegistrarUsuari::CtrlRegistrarUsuari() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlRegistrarUsuari::CrearUsuari(String^ nom, String^ pass, DateTime dataReg, String^ correu, String^ tipus, String^ telefon) {
            Playcampus::Dades::PassarellaUsuari^ u = gcnew Playcampus::Dades::PassarellaUsuari(connectionString, nom, pass, dataReg, correu, tipus);
            u->SetTelefon(telefon);
            u->Insereix();
        }
    }
}
