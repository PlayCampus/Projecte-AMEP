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
                    conn->Close();
                    delete conn;
                }
            }

            return resultat;
        }

        CtrlConsultes::CtrlConsultes() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultes::ObtenirDisciplinaLliga(String^ idLliga) {
            if (String::IsNullOrEmpty(idLliga)) return nullptr;

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ consulta = "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat == nullptr || resultat == DBNull::Value) return nullptr;
                return resultat->ToString();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
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
                "SELECT L.nom AS Lliga, L.disciplina AS Esport, "
                "IFNULL(U.nom, '') AS Administrador, COUNT(DISTINCT E.idEquip) AS NumEquips "
                "FROM Lliga L "
                "LEFT JOIN Temporada T ON T.idLliga = L.idLliga "
                "LEFT JOIN Equip E ON E.idTemporada = T.idTemporada "
                "LEFT JOIN Usuari U ON L.idAdministrador = U.identificador "
                "GROUP BY L.idLliga, L.nom, L.disciplina, U.nom "
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
                "LEFT JOIN Temporada T ON E.idTemporada = T.idTemporada "
                "LEFT JOIN Lliga L ON T.idLliga = L.idLliga "
                "ORDER BY IFNULL(L.nom, ''), E.posicioClassificacio ASC, E.punts DESC, E.nom ASC";

            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CtrlConsultes::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            String^ disciplina = ObtenirDisciplinaLliga(idLliga);
            bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
            String^ labelLocal = esFutbol ? "Gols locals" : "Punts locals";
            String^ labelVisitant = esFutbol ? "Gols visitant" : "Punts visitant";

            String^ consulta =
                "SELECT J.numero AS Jornada, "
                "DATE_FORMAT(P.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                "COALESCE(EL.nom, '(TBD)') AS Local, COALESCE(EV.nom, '(TBD)') AS Visitant, "
                "P.ubicacio AS Ubicacio, P.estat AS Estat, "
                "P.golsLocal AS `" + labelLocal + "`, P.golsVisitant AS `" + labelVisitant + "` "
                "FROM Partit P "
                "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                "LEFT JOIN Equip EL ON P.idEquipLocal = EL.idEquip "
                "LEFT JOIN Equip EV ON P.idEquipVisitant = EV.idEquip "
                "WHERE T.idLliga = @idLliga "
                "ORDER BY J.numero ASC, P.dataHora ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@idLliga", idLliga);
            return ExecutaConsulta(connectionString, consulta, parametres);
        }

        DataTable^ CtrlConsultes::ObtenirUltimsFitxatges(int limit) {
            if (limit <= 0) limit = 10;

            String^ consulta =
              "SELECT DATE_FORMAT(J.data_naixement, '%d/%m/%Y') AS Data, "
                "U.nom AS Jugador, "
                "COALESCE(E.nom, '(Sense equip)') AS Equip, "
                "COALESCE(E.esport, '') AS Esport "
                "FROM Jugador J "
                "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                "LEFT JOIN Equip E ON J.idEquip = E.idEquip "
                "WHERE J.idEquip IS NOT NULL "
                "ORDER BY J.data_naixement DESC, J.idJugador DESC "
                "LIMIT " + limit;

            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            String^ consulta =
                "SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
                "E.partitsJugats AS PartitsJugats, E.victories AS Victories, E.empats AS Empats, "
                "E.derrotes AS Derrotes, E.punts AS Punts "
                "FROM Lliga L "
                "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                "INNER JOIN Temporada T ON T.idLliga = L.idLliga "
                "INNER JOIN Equip E ON E.idTemporada = T.idTemporada "
                "WHERE U.correu_electronic = @correuAdmin "
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
                    "WHERE U.correu_electronic = @correuAdmin "
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
                    conn->Close();
                    delete conn;
                }
            }

            return nomLliga;
        }

        String^ CtrlConsultes::ObtenirTipusUsuariPerCorreu(String^ correuUsuari) {
            String^ tipus = "";

            if (!String::IsNullOrWhiteSpace(correuUsuari)) {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                try {
                    conn->Open();
                    String^ consulta =
                        "SELECT Tipus "
                        "FROM Usuari "
                        "WHERE correu_electronic = @correuUsuari "
                        "LIMIT 1";

                    MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                    cmd->Parameters->AddWithValue("@correuUsuari", correuUsuari);

                    Object^ resultat = cmd->ExecuteScalar();
                    if (resultat != nullptr && resultat != DBNull::Value) {
                        tipus = resultat->ToString();
                    }
                }
                finally {
                    if (conn != nullptr) {
                        conn->Close();
                    }
                }
            }

            return tipus;
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerCapita(String^ correuUsuari) {
            String^ consulta =
                "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                "COALESCE(A.telefonContacte, '') AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                "FROM Usuari UC "
                "INNER JOIN Capita C ON C.identificador = UC.identificador "
                "INNER JOIN Equip E ON E.idEquip = C.idEquip "
                "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada "
                "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UC.correu_electronic = @correuUsuari "
                "ORDER BY L.nom ASC, UA.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuUsuari);
            return ExecutaConsulta(connectionString, consulta, parametres);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerJugador(String^ correuUsuari) {
            String^ consulta =
                "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                "COALESCE(C.telefonContacte, '') AS Telefon, E.nom AS Equip, '' AS Lliga "
                "FROM Usuari UJ "
                "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                "WHERE UJ.correu_electronic = @correuUsuari "
                "UNION "
                "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                "COALESCE(A.telefonContacte, '') AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                "FROM Usuari UJ "
                "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada "
                "INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UJ.correu_electronic = @correuUsuari "
                "ORDER BY Rol ASC, Nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuUsuari);
            return ExecutaConsulta(connectionString, consulta, parametres);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerAdministrador(String^ correuUsuari) {
            String^ consulta =
                "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                "COALESCE(C.telefonContacte, '') AS Telefon, COALESCE(E.nom, '') AS Equip, "
                "COALESCE(L.nom, '') AS Lliga "
                "FROM Usuari UA "
                "INNER JOIN Administrador ALogin ON ALogin.identificador = UA.identificador "
                "INNER JOIN Capita C ON 1 = 1 "
                "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                "LEFT JOIN Equip E ON E.idEquip = C.idEquip "
                "LEFT JOIN Temporada T ON T.idTemporada = E.idTemporada "
                "LEFT JOIN Lliga L ON L.idLliga = T.idLliga "
                "WHERE UA.correu_electronic = @correuUsuari "
                "ORDER BY UC.nom ASC, E.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuUsuari);
            return ExecutaConsulta(connectionString, consulta, parametres);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsContacte(String^ correuUsuari) {
            DataTable^ resultat = gcnew DataTable();

            if (String::IsNullOrWhiteSpace(correuUsuari)) {
                throw gcnew Exception("No s'ha pogut identificar l'usuari actual.");
            }

            String^ tipusUsuari = ObtenirTipusUsuariPerCorreu(correuUsuari);

            if (tipusUsuari == "Capita") {
                resultat = ObtenirTelefonsPerCapita(correuUsuari);
            }
            else if (tipusUsuari == "Jugador") {
                resultat = ObtenirTelefonsPerJugador(correuUsuari);
            }
            else if (tipusUsuari == "Administrador") {
                resultat = ObtenirTelefonsPerAdministrador(correuUsuari);
            }
            else {
                throw gcnew Exception("Aquest usuari no té permisos per consultar números de telèfon.");
            }

            return resultat;
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ consulta =
                    "UPDATE Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                    "SET E.idTemporada = NULL "
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
                    conn->Close();
                    delete conn;
                }
            }
        }
    }
}
