#include "pch.h"
#include "CtrlVeurePlantilla.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraEquip.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlVeurePlantilla::CtrlVeurePlantilla() {
        }

        DataTable^ CtrlVeurePlantilla::ObtenirPlantillaEquip(String^ correuCapita) {
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            CercadoraUsuari^ cercadoraUser = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariCapita = cercadoraUser->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr || usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no és completament vàlid per consultar l'equip.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connStr);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té equip assignat.");
            }

            return cercadoraEquip->ObtenirPlantillaEquip(idEquip);
        }
    }
}
