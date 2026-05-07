#include "pch.h"
#include "CtrlAfegirJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJugador.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlAfegirJugador::CtrlAfegirJugador() {
        }

        String^ CtrlAfegirJugador::AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita) {
            // Obtenir connexiÃ³ a la BD
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            // Cercar l'usuari estudiant
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariEstudiant = cercadora->LlegeixPerCorreu(correuEstudiant);

            if (usuariEstudiant == nullptr) {
                throw gcnew Exception("L'usuari estudiant no existeix.");
            }

            // Permetem tornar a inscriure un usuari que ja Ã©s de tipus Jugador perÃ² no estÃ  vinculat a cap equip
            // (p.ex. desprÃ©s d'haver estat expulsat). En aquest cas, es crearÃ  un nou registre a la taula Jugador.
            if (usuariEstudiant->GetTipus() != "Estudiant" && usuariEstudiant->GetTipus() != "Jugador") {
                throw gcnew Exception("L'usuari no Ã©s de tipus Estudiant ni Jugador.");
            }

            // Cercar el capta per obtenir l'idEquip
            PassarellaUsuari^ usuariCapita = cercadora->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew Exception("L'usuari capta no existeix.");
            }

            if (usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no Ã©s de tipus Capita.");
            }

            // Obtenir l'idEquip del capta (necesita consulta a BD)
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
                        idEquip = reader->GetString(0)->Trim();
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
                throw gcnew Exception("El capta no tÃ© equip assignat.");
            }

            // Verificar que l'equip existeix (evitar errors de clau forana)
            {
                MySqlConnection^ connEquip = gcnew MySqlConnection(connStr);
                try {
                    connEquip->Open();
                    String^ queryEquip = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip";
                    MySqlCommand^ cmdEquip = gcnew MySqlCommand(queryEquip, connEquip);
                    cmdEquip->Parameters->AddWithValue("@idEquip", idEquip);
                    int existeix = Convert::ToInt32(cmdEquip->ExecuteScalar());
                    if (existeix <= 0) {
                        throw gcnew Exception("L'equip associat al capitÃ  no existeix o no Ã©s vÃ lid.");
                    }
                }
                finally {
                    connEquip->Close();
                }
            }

            // Verificar que el dorsal no existeix en l'equip
            CercadoraJugador^ cerJugador = gcnew CercadoraJugador(connStr);
            if (cerJugador->ExisteixDorsalEnEquip(dorsal, idEquip)) {
                throw gcnew Exception("El dorsal " + dorsal.ToString() + " ja existeix en aquest equip.");
            }

            // Crear el jugador nou
            PassarellaJugador^ jugador = gcnew PassarellaJugador(connStr, dorsal, posicio, DateTime::Now);
            jugador->SetIdEquip(idEquip);

            // Inserir jugador (passant idJugador que Ã©s el identificador de l'Usuari)
            jugador->Insereix(usuariEstudiant->GetIdentificador());

            // Actualitzar tipus d'usuari de Estudiant a Jugador (si ja era Jugador, no cal)
            if (usuariEstudiant->GetTipus() != "Jugador") {
                usuariEstudiant->ActualitzaTipus("Jugador");
            }

            return "Jugador afegit correctament!";
        }
    }
}
