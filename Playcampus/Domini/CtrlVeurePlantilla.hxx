#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlVeurePlantilla {
        public:
            CtrlVeurePlantilla();
            DataTable^ ObtenirPlantillaEquip(String^ correuCapita);
        };
    }
}