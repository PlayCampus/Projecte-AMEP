#include "pch.h"
#include "CtrlVeurePlantilla.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraSistema.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;
using namespace System::Collections::Generic;

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

            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connStr);
            String^ idEquip = cercadora->ObtenirIdEquipCapitaPerIdentificador(usuariCapita->GetIdentificador());

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té equip assignat.");
            }

            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("IdJugador", String::typeid);
            dt->Columns->Add("Nom", String::typeid);
            dt->Columns->Add("Dorsal", int::typeid);
            dt->Columns->Add("PosiciÃ³", String::typeid);

            List<Dictionary<String^, String^>^>^ jugadors = cercadora->ObtenirPlantillaPerEquip(idEquip);
            for (int i = 0; i < jugadors->Count; ++i) {
                Dictionary<String^, String^>^ jugador = jugadors[i];
                int dorsal = 0;
                if (jugador->ContainsKey("dorsal") && !String::IsNullOrWhiteSpace(jugador["dorsal"])) {
                    dorsal = Int32::Parse(jugador["dorsal"]);
                }

                dt->Rows->Add(
                    jugador["idJugador"],
                    jugador["nom"],
                    dorsal,
                    jugador["posicio"]
                );
            }

            return dt;
        }
    }
}
