#include "pch.h"
#include "CtrlConsultes.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {
        static DataTable^ ExecutaConsulta(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            DataTable^ resultat = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for each (MySqlParameter^ p in parametres) {
                        cmd->Parameters->Add(p);
                    }
                }

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(resultat);
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }

            return resultat;
        }

        CtrlConsultes::CtrlConsultes() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        DataTable^ CtrlConsultes::ObtenirProgramacioPartits() {
            String^ consulta =
                "SELECT L.nom AS Lliga, J.numero AS Jornada, "
                "EL.nom AS EquipLocal, EV.nom AS EquipVisitant, "
                "P.dataHora AS DataPartit, P.ubicacio AS Ubicacio, P.estat AS Estat, "
                "P.golsLocal AS GolsLocal, P.golsVisitant AS GolsVisitant "
                "FROM Partit P "
                "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                "INNER JOIN Equip EL ON P.idEquipLocal = EL.idEquip "
                "INNER JOIN Equip EV ON P.idEquipVisitant = EV.idEquip "
                "ORDER BY P.dataHora ASC";

            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CtrlConsultes::ObtenirEstatLligues() {
            String^ consulta =
                "SELECT L.nom AS Lliga, L.disciplina AS Esport, L.estat AS Estat, "
                "IFNULL(U.nom, '') AS Administrador, COUNT(E.idEquip) AS NumEquips "
                "FROM Lliga L "
                "LEFT JOIN Equip E ON E.idLliga = L.idLliga "
                "LEFT JOIN Usuari U ON L.idAdministrador = U.identificador "
                "GROUP BY L.idLliga, L.nom, L.disciplina, L.estat, U.nom "
                "ORDER BY L.nom ASC";

            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CtrlConsultes::ObtenirEstadistiquesEquips() {
            String^ consulta =
                "SELECT IFNULL(L.nom, 'Sense lliga') AS Lliga, E.nom AS Equip, E.esport AS Esport, "
                "E.partitsJugats AS PartitsJugats, E.victories AS Victories, E.empats AS Empats, "
                "E.derrotes AS Derrotes, E.punts AS Punts, E.golsAFavor AS GolsAFavor, "
                "E.golsEnContra AS GolsEnContra, E.diferenciaGols AS DiferenciaGols, "
                "E.posicioClassificacio AS PosicioClassificacio "
                "FROM Equip E "
                "LEFT JOIN Lliga L ON E.idLliga = L.idLliga "
                "ORDER BY IFNULL(L.nom, ''), E.posicioClassificacio ASC, E.punts DESC, E.nom ASC";

            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            String^ consulta =
                "SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
                "E.partitsJugats AS PartitsJugats, E.victories AS Victories, E.empats AS Empats, "
                "E.derrotes AS Derrotes, E.punts AS Punts "
                "FROM Lliga L "
                "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                "INNER JOIN Equip E ON E.idLliga = L.idLliga "
                "WHERE U.correu_electronic = @correuAdmin AND L.estat = 'en_curs' "
                "ORDER BY E.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuAdmin", correuAdmin);
            return ExecutaConsulta(connectionString, consulta, parametres);
        }

        String^ CtrlConsultes::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            String^ nomLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ consulta =
                    "SELECT L.nom FROM Lliga L "
                    "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "WHERE U.correu_electronic = @correuAdmin AND L.estat = 'en_curs' "
                    "ORDER BY L.nom ASC LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    nomLliga = resultat->ToString();
                }
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }

            return nomLliga;
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ consulta =
                    "UPDATE Equip E "
                    "INNER JOIN Lliga L ON E.idLliga = L.idLliga "
                    "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "SET E.idLliga = NULL "
                    "WHERE E.idEquip = @idEquip AND U.correu_electronic = @correuAdmin";
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);
                int filesAfectades = cmd->ExecuteNonQuery();
                if (filesAfectades == 0) {
                    throw gcnew Exception("No s'ha trobat l'equip dins d'una lliga administrada per aquest usuari.");
                }
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
    }
}
