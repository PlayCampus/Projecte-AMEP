#include "pch.h"
#include "CtrlCrearPartit.hxx"
#include "../Dades/PassarellaPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {

        CtrlCrearPartit::CtrlCrearPartit() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlCrearPartit::CrearPartit(String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada, String^ tipusUsuari) {
            // Verificar que l'usuari és un administrador
            if (tipusUsuari == nullptr || tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear un Partit.");
            }

            // Crear l'objecte de domini Partit (assumint que existeix aquest constructor)
            Partit^ nouPartit = gcnew Partit(idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada);

            // Guardar a la base de dades utilitzant la passarel·la
            Playcampus::Dades::PassarellaPartit^ pp = gcnew Playcampus::Dades::PassarellaPartit(connectionString, idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada);
            pp->InsereixPartit();
        }

    }
}