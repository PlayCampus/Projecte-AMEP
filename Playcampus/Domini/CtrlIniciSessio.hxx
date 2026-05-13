#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlIniciSessio {
        private:
            String^ connectionString;
        public:
            System::String^ ObtenirIdEquipDeCapita(System::String^ correu);
            System::String^ ObtenirIdUsuari(System::String^ correu);
            CtrlIniciSessio();
            bool IniciarSessio(String^ correu, String^ contrasenya);
            String^ ObtenirTipusUsuari(String^ correu);
            bool CapitaTeEquip(String^ correu);
            bool EquipEstaEnLliga(String^ correu);
        };
    }
}
