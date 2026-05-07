#include "pch.h"
#include "CtrlTancarSessio.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlTancarSessio::CtrlTancarSessio() {
        }

        void CtrlTancarSessio::TancarSessio() {
            MySql::Data::MySqlClient::MySqlConnection::ClearAllPools();
        }
    }
}
