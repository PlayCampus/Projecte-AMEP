#pragma once
#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlUnirEquipLliga {
        private:
            String^ connectionString;
        public:
            CtrlUnirEquipLliga();

            String^ ComprovarSiLligaExisteix(String^ nomLliga);
            bool ValidarContrasenyaLliga(String^ nomLliga, String^ pass);
            String^ VincularEquip(String^ correuCapita, String^ nomLliga);
        };
    }
}