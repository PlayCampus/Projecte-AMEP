#include "pch.h"
#include "CtrlVeureEstadistiquesJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/CercadoraPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesJugadors::CtrlVeureEstadistiquesJugadors() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesJugador(String^ idJugador) {
            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);
            return cercadoraJugador->ObtenirEstadistiquesJugador(idJugador);
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirDetallsPartit(String^ idPartit) {
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirDetallsPartitEstadistiques(idPartit);
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesPartit(String^ idPartit) {
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirEstadistiquesPartit(idPartit);
        }
    }
}
