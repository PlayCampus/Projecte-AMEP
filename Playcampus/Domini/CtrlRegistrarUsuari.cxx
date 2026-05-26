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
            if (!System::Text::RegularExpressions::Regex::IsMatch(correu, "^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$")) {
                throw gcnew Exception("El format del correu electrònic no és vàlid.");
            }

            Playcampus::Dades::CercadoraUsuari^ cercadoraUsuari = gcnew Playcampus::Dades::CercadoraUsuari(connectionString);
            if (cercadoraUsuari->LlegeixPerCorreu(correu) != nullptr) {
                throw gcnew Exception("Ja existeix un usuari registrat amb aquest correu electrònic.");
            }

            if (dataReg > DateTime::Now) {
                throw gcnew Exception("La data de registre no pot ser en el futur.");
            }


            Playcampus::Dades::PassarellaUsuari^ u = gcnew Playcampus::Dades::PassarellaUsuari(connectionString, nom, pass, dataReg, correu, tipus);
            u->SetTelefon(telefon);
            u->Insereix();
        }
    }
}
