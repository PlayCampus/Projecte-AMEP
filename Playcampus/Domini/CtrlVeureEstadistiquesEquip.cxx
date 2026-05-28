#include "pch.h"
#include "CtrlVeureEstadistiquesEquip.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraEquipTemporada.hxx"

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
            CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew CercadoraEquipTemporada(connectionString);
            return cercadoraEquipTemporada->ObtenirLliguesEquip(nomEquip);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew CercadoraEquipTemporada(connectionString);
            return cercadoraEquipTemporada->ObtenirTemporadesEquipLliga(nomEquip, idLliga);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            CercadoraEquipTemporada^ cercadoraEquipTemporada = gcnew CercadoraEquipTemporada(connectionString);
            return cercadoraEquipTemporada->ObtenirEstadistiquesEquip(nomEquip, idLliga, idTemporada);
        }
    }
}
