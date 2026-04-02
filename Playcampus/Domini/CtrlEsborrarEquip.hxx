#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEsborrarEquip {
        private:
            String^ connectionString;
        public:
            CtrlEsborrarEquip();
            void EsborrarEquip(String^ idEquip);
        };
    }
}
