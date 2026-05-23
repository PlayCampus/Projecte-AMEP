#include "pch.h"
#include "CtrlConsultes.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlConsultes::CtrlConsultes() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultes::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirDisciplinaLliga(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirProgramacioPartits() {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirProgramacioPartits();
        }

        DataTable^ CtrlConsultes::ObtenirEstatLligues() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstatLligues();
        }

        DataTable^ CtrlConsultes::ObtenirEstadistiquesEquips() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstadistiquesEquipsGenerals();
        }

        DataTable^ CtrlConsultes::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirCalendariCompletLligaPerId(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirUltimsFitxatges(int limit) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DATE_FORMAT(J.data_naixement, '%d/%m/%Y') AS Data, "
                    "U.nom AS Jugador, E.nom AS Equip, J.dorsal AS Dorsal, J.posicio AS Posicio "
                    "FROM Jugador J "
                    "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                    "LEFT JOIN Equip E ON J.idEquip = E.idEquip "
                    "ORDER BY U.data_registre DESC "
                    "LIMIT @limit";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@limit", limit);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            CercadoraEquip^ cercadora = gcnew CercadoraEquip(connectionString);
            return cercadora->ObtenirEquipsDeLaLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultes::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirNomLligaAdmin(correuAdmin);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsContacte(String^ correuUsuari) {
            if (String::IsNullOrWhiteSpace(correuUsuari)) {
                throw gcnew Exception("No s'ha pogut identificar l'usuari actual.");
            }

            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            String^ tipusUsuari = cercadora->ObtenirTipusUsuariPerCorreu(correuUsuari);
            String^ tipusNormalitzat = "";
            if (!String::IsNullOrEmpty(tipusUsuari)) {
                tipusNormalitzat = tipusUsuari->ToLower();
            }

            DataTable^ resultat = gcnew DataTable();
            if (tipusNormalitzat == "capita") {
                resultat = cercadora->ObtenirTelefonsAdministradorPerCapita(correuUsuari);
            }
            else if (tipusNormalitzat == "jugador") {
                resultat = cercadora->ObtenirTelefonsContactePerJugador(correuUsuari);
            }
            else if (tipusNormalitzat == "administrador") {
                resultat = cercadora->ObtenirTelefonsCapitansPerAdministrador(correuUsuari);
            }
            else {
                throw gcnew Exception("Aquest usuari no té permisos per consultar números de telèfon.");
            }
            return resultat;
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            PassarellaEquip^ passarella = gcnew PassarellaEquip(connectionString);
            passarella->TreureEquipDeLaLliga(idEquip, correuAdmin);
        }
    }
}
