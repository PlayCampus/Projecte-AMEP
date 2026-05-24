#include "pch.h"
#include "CtrlVeureEstadistiquesEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraEquip.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesEquip::CtrlVeureEstadistiquesEquip() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlVeureEstadistiquesEquip::ExisteixEquip(String^ nomEquip) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ExisteixEquipPerNom(nomEquip);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirLliguesEquip(String^ nomEquip) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirLliguesEquip(nomEquip);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirTemporadesEquipLliga(nomEquip, idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirEstadistiquesEquip(nomEquip, idLliga, idTemporada);
        }
    }
}
