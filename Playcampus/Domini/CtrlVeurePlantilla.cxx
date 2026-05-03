#include "pch.h"
#include "CtrlVeurePlantilla.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaJugador.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        CtrlVeurePlantilla::CtrlVeurePlantilla() {
        }

        DataTable^ CtrlVeurePlantilla::ObtenirPlantillaEquip(String^ correuCapita) {
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            // Get capita
            CercadoraUsuari^ cercadoraUser = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariCapita = cercadoraUser->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr || usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no és completament vàlid per consultar l'equip.");
            }

            // Get team using id
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            String^ idEquip = nullptr;

            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Capita WHERE identificador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", usuariCapita->GetIdentificador());

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    if (!reader->IsDBNull(0)) {
                        idEquip = reader->GetString(0);
                    }
                }
                reader->Close();
                conn->Close();
            }
            catch (Exception^ ex) {
                conn->Close();
                throw ex;
            }

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té equip assignat.");
            }

            // Get team players
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("IdJugador", String::typeid);
            dt->Columns->Add("Nom", String::typeid);
            dt->Columns->Add("Dorsal", int::typeid);
            dt->Columns->Add("Posició", String::typeid);

            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connStr);
            List<PassarellaJugador^>^ jugadors = cercadoraJugador->LlegeixTsPerEquip(idEquip);

            for each(PassarellaJugador^ p in jugadors) {
                dt->Rows->Add(p->GetIdJugador(), p->GetNom(), p->GetDorsal(), p->GetPosicio());
            }

            return dt;
        }
    }
}