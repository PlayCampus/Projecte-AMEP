#include "pch.h"
#include "CtrlVeureEstadistiquesEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesEquip::CtrlVeureEstadistiquesEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlVeureEstadistiquesEquip::ExisteixEquip(String^ nomEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ExisteixEquipPerNom(nomEquip);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirLliguesEquip(String^ nomEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirLliguesEquip(nomEquip);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirTemporadesEquipLliga(nomEquip, idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstadistiquesEquip(nomEquip, idLliga, idTemporada);
        }
    }
}
