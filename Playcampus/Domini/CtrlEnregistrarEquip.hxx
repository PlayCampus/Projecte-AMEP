#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEnregistrarEquip {
        private:
            String^ connectionString;
        public:
            CtrlEnregistrarEquip();
            void EnregistrarEquip(String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, String^ tipusUsuari, String^ correuUsuari);
        };
    }
}
