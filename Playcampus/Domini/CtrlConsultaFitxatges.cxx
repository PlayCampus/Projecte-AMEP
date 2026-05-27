#include "pch.h"
#include "CtrlConsultaFitxatges.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraJugador.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlConsultaFitxatges::CtrlConsultaFitxatges() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        DataTable^ CtrlConsultaFitxatges::ObtenirUltimsFitxatges(int limit) {
            CercadoraJugador^ cercadora = gcnew CercadoraJugador(connectionString);
            return cercadora->ObtenirUltimsFitxatges(limit);
        }
    }
}
