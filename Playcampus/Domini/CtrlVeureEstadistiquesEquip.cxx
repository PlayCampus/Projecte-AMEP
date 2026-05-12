#include "pch.h"
#include "CtrlVeureEstadistiquesEquip.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {

        CtrlVeureEstadistiquesEquip::CtrlVeureEstadistiquesEquip() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        static DataTable^ ExecutarConsultaEstadistiquesEquip(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            DataTable^ resultat = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);

                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(resultat);
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                }
            }

            return resultat;
        }

        static Object^ ExecutarEscalarEstadistiquesEquip(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);

                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }

                resultat = cmd->ExecuteScalar();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                }
            }

            return resultat;
        }



        static bool EquipTeColumna(String^ connectionString, String^ nomColumna) {
            bool existeix = false;

            String^ consulta =
                "SELECT COUNT(*) "
                "FROM INFORMATION_SCHEMA.COLUMNS "
                "WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomColumna", nomColumna);

            Object^ resultat = ExecutarEscalarEstadistiquesEquip(connectionString, consulta, parametres);
            if (resultat != nullptr && resultat != DBNull::Value) {
                existeix = Convert::ToInt32(resultat) > 0;
            }

            return existeix;
        }

        bool CtrlVeureEstadistiquesEquip::ExisteixEquip(String^ nomEquip) {
            bool existeix = false;

            String^ consulta =
                "SELECT COUNT(*) "
                "FROM Equip "
                "WHERE nom = @nomEquip";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);

            Object^ resultat = ExecutarEscalarEstadistiquesEquip(connectionString, consulta, parametres);
            if (resultat != nullptr && resultat != DBNull::Value) {
                existeix = Convert::ToInt32(resultat) > 0;
            }

            return existeix;
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirLliguesEquip(String^ nomEquip) {
            String^ consulta = nullptr;
            bool teIdTemporada = EquipTeColumna(connectionString, "idTemporada");

            if (teIdTemporada) {
                consulta =
                    "SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "UNION "
                    "SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "ORDER BY NomLliga ASC";
            }
            else {
                consulta =
                    "SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Lliga L ON E.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "UNION "
                    "SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "ORDER BY NomLliga ASC";
            }

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);

            return ExecutarConsultaEstadistiquesEquip(connectionString, consulta, parametres);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            String^ consulta = nullptr;
            bool teIdTemporada = EquipTeColumna(connectionString, "idTemporada");

            if (teIdTemporada) {
                consulta =
                    "SELECT DISTINCT T.idTemporada AS IdTemporada, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
                    "UNION "
                    "SELECT DISTINCT T.idTemporada AS IdTemporada, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
                    "ORDER BY NomTemporada DESC";
            }
            else {
                consulta =
                    "SELECT DISTINCT T.idTemporada AS IdTemporada, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
                    "FROM Equip E "
                    "INNER JOIN Lliga L ON E.idLliga = L.idLliga "
                    "INNER JOIN Temporada T ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip AND L.idLliga = @idLliga "
                    "UNION "
                    "SELECT DISTINCT T.idTemporada AS IdTemporada, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
                    "ORDER BY NomTemporada DESC";
            }

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(2);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);
            parametres[1] = gcnew MySqlParameter("@idLliga", idLliga);

            return ExecutarConsultaEstadistiquesEquip(connectionString, consulta, parametres);
        }

        DataTable^ CtrlVeureEstadistiquesEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            String^ condicioAssociacio = "P.idPartit IS NOT NULL";
            bool teIdTemporada = EquipTeColumna(connectionString, "idTemporada");
            if (teIdTemporada) {
                condicioAssociacio = "E.idTemporada = T.idTemporada OR P.idPartit IS NOT NULL";
            }
            else {
                condicioAssociacio = "E.idLliga = L.idLliga OR P.idPartit IS NOT NULL";
            }

            String^ consultaBase =
                "SELECT L.nom AS Lliga, "
                "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS Temporada, "
                "E.nom AS Equip, E.esport AS Esport, "
                "COUNT(CASE WHEN P.estat = 'Finalitzat' THEN P.idPartit END) AS PartitsJugats, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal > P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant > P.golsLocal)) THEN 1 ELSE 0 END), 0) AS Victories, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.golsLocal = P.golsVisitant THEN 1 ELSE 0 END), 0) AS Empats, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal < P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant < P.golsLocal)) THEN 1 ELSE 0 END), 0) AS Derrotes, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal > P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant > P.golsLocal)) THEN 3 WHEN P.estat = 'Finalitzat' AND P.golsLocal = P.golsVisitant THEN 1 ELSE 0 END), 0) AS Punts, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsLocal, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsVisitant, 0) ELSE 0 END), 0) AS GolsAFavor, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsVisitant, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsLocal, 0) ELSE 0 END), 0) AS GolsEnContra, "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsLocal, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsVisitant, 0) ELSE 0 END), 0) - "
                "IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsVisitant, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsLocal, 0) ELSE 0 END), 0) AS DiferenciaGols, "
                "E.posicioClassificacio AS PosicioClassificacio "
                "FROM Equip E "
                "INNER JOIN Temporada T ON T.idTemporada = @idTemporada "
                "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                "LEFT JOIN Jornada J ON J.idTemporada = T.idTemporada "
                "LEFT JOIN Partit P ON P.idJornada = J.idJornada AND (P.idEquipLocal = E.idEquip OR P.idEquipVisitant = E.idEquip) "
                "WHERE E.nom = @nomEquip AND T.idLliga = @idLliga AND T.idTemporada = @idTemporada "
                "AND (";

            String^ consultaFinal =
                ") "
                "GROUP BY L.nom, T.idTemporada, T.dataInici, T.dataFi, E.idEquip, E.nom, E.esport, E.posicioClassificacio "
                "ORDER BY E.nom ASC";

            String^ consulta = consultaBase + condicioAssociacio + consultaFinal;

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(3);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);
            parametres[1] = gcnew MySqlParameter("@idLliga", idLliga);
            parametres[2] = gcnew MySqlParameter("@idTemporada", idTemporada);

            return ExecutarConsultaEstadistiquesEquip(connectionString, consulta, parametres);
        }
    }
}
