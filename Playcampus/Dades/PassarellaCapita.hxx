#pragma once
#pragma once
#include <string>

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaCapita {
        
        private:
			String^ connectionString;

        public:
            PassarellaCapita(String^ connStr);

            void DesassignarEquip(String^ idEquip);
            void AssignarEquip(String^ idCapita, String^ idEquip);

        };
    }
}