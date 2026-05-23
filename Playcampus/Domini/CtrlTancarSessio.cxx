#include "pch.h"
#include "CtrlTancarSessio.hxx"
#include "../Dades/PassarellaSistema.hxx"
#include "../Dades/ConnexioBD.hxx"

namespace Playcampus {
    namespace Domini {
        CtrlTancarSessio::CtrlTancarSessio() {}

        void CtrlTancarSessio::TancarSessio() {
            Playcampus::Dades::PassarellaSistema^ passarella = gcnew Playcampus::Dades::PassarellaSistema(Playcampus::Dades::ConnexioBD::ObtenirConnectionString());
            passarella->TancarPools();
        }
    }
}
