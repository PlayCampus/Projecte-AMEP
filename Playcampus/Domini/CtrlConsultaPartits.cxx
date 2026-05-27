#include "pch.h"
#include "CtrlConsultaPartits.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlConsultaPartits::CtrlConsultaPartits() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        DataTable^ CtrlConsultaPartits::ObtenirProgramacioPartits() {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirProgramacioPartits();
        }

        DataTable^ CtrlConsultaPartits::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirCalendariCompletLligaPerId(idLliga);
        }
    }
}
