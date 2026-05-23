#include "pch.h"
#include "CtrlVeureEstadistiquesJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesJugadors::CtrlVeureEstadistiquesJugadors() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirTotesEstadistiquesJugadors() {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirTotesEstadistiquesJugadors();
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesJugador(String^ idJugador) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstadistiquesJugador(idJugador);
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirDetallsPartit(String^ idPartit) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirDetallsPartitEstadistiques(idPartit);
        }

        DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesPartit(String^ idPartit) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstadistiquesPartit(idPartit);
        }
    }
}
