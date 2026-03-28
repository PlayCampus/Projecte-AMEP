#include "pch.h"
#include "CtrlCrearLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlCrearLliga::CtrlCrearLliga() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlCrearLliga::CrearLliga(String^ idLliga, String^ nom, Disciplina disciplina, String^ descripcio, String^ estat, String^ contrasenya, String^ tipusUsuari) {
            // Verificar que l'usuari és un administrador
            if (tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear una lliga.");
            }

            // Aquí es crearia la Lliga. Actualment es crea l'objecte de domini.
            Lliga^ novaLliga = gcnew Lliga(idLliga, nom, disciplina, descripcio, estat, contrasenya);

            // Guardar a la base de dades utilitzant la passarella
            Playcampus::Dades::PassarellaLliga^ pl = gcnew Playcampus::Dades::PassarellaLliga(connectionString, idLliga, nom, disciplina, descripcio, estat, contrasenya);
            pl->Insereix();
        }
        bool CtrlCrearLliga::ExisteixLliga(String^ nomLliga) {
            Playcampus::Dades::PassarellaLliga^ p = gcnew Playcampus::Dades::PassarellaLliga(connectionString);
            return p->ExisteixPerNom(nomLliga);
        }
    }
}
