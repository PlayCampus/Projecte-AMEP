#pragma once
#include <string>

using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class ConnexioBD {
        public:
            static String^ ObtenirConnectionString();
        };
    }
}
