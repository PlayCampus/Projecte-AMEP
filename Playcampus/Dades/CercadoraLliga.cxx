#include "pch.h"
#include "CercadoraLliga.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        static void AfegeixParametres(MySqlCommand^ cmd, Dictionary<String^, Object^>^ parametres) {
            if (parametres != nullptr) {
                for each (KeyValuePair<String^, Object^> parella in parametres) {
                    Object^ valor = parella.Value;
                    if (valor == nullptr) {
                        valor = DBNull::Value;
                    }
                    cmd->Parameters->AddWithValue(parella.Key, valor);
                }
            }
        }

        static DataTable^ ExecutaConsulta(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            DataTable^ taula = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                AfegeixParametres(cmd, parametres);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(taula);
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return taula;
        }

        static Object^ ExecutaEscalar(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                AfegeixParametres(cmd, parametres);
                resultat = cmd->ExecuteScalar();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return resultat;
        }

        static Dictionary<String^, Object^>^ Params1(String^ k1, Object^ v1) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p[k1] = v1;
            return p;
        }

        static Dictionary<String^, Object^>^ Params2(String^ k1, Object^ v1, String^ k2, Object^ v2) {
            Dictionary<String^, Object^>^ p = Params1(k1, v1);
            p[k2] = v2;
            return p;
        }

        static String^ EscalarString(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            String^ valor = nullptr;
            Object^ resultat = ExecutaEscalar(connectionString, query, parametres);
            if (resultat != nullptr && resultat != DBNull::Value) {
                valor = resultat->ToString();
            }
            return valor;
        }

        CercadoraLliga::CercadoraLliga(String^ connStr) {
            connectionString = connStr;
        }

        String^ CercadoraLliga::ObtenirLligaActivaAdmin(String^ idAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE idAdministrador = @idAdmin LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idAdmin", idAdmin);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

        String^ CercadoraLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            return EscalarString(connectionString,
                "SELECT idLliga FROM Lliga WHERE nom = @nomLliga",
                Params1("@nomLliga", nomLliga));
        }

        String^ CercadoraLliga::ObtenirNomLligaAdmin(String^ correuAdmin) {
            String^ query =
                "SELECT l.nom "
                "FROM Lliga l "
                "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                "WHERE u.correu_electronic = @correuAdmin "
                "ORDER BY l.nom "
                "LIMIT 1";
            return EscalarString(connectionString, query, Params1("@correuAdmin", correuAdmin));
        }

        String^ CercadoraLliga::ObtenirNomLligaPerId(String^ idLliga) {
            return EscalarString(connectionString,
                "SELECT nom FROM Lliga WHERE idLliga = @idLliga",
                Params1("@idLliga", idLliga));
        }

        String^ CercadoraLliga::ObtenirContrasenyaLligaPerNom(String^ nomLliga) {
            return EscalarString(connectionString,
                "SELECT contrasenya FROM Lliga WHERE nom = @nomLliga",
                Params1("@nomLliga", nomLliga));
        }

        String^ CercadoraLliga::ObtenirIdTemporadaRellevant(String^ idLliga) {
            String^ idTemporada = EscalarString(connectionString,
                "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga AND estat = 'EnCurs' ORDER BY dataInici DESC LIMIT 1",
                Params1("@idLliga", idLliga));
            if (String::IsNullOrWhiteSpace(idTemporada)) {
                idTemporada = EscalarString(connectionString,
                    "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC LIMIT 1",
                    Params1("@idLliga", idLliga));
            }
            return idTemporada;
        }

        String^ CercadoraLliga::ObtenirDisciplinaLliga(String^ idLliga) {
            return EscalarString(connectionString,
                "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga",
                Params1("@idLliga", idLliga));
        }

        String^ CercadoraLliga::ObtenirIdLligaAdminPerCorreu(String^ correuAdmin) {
            String^ query =
                "SELECT L.idLliga FROM Lliga L "
                "INNER JOIN Administrador A ON L.idAdministrador = A.identificador "
                "INNER JOIN Usuari U ON A.identificador = U.identificador "
                "WHERE U.correu_electronic = @correu";
            return EscalarString(connectionString, query, Params1("@correu", correuAdmin));
        }

        String^ CercadoraLliga::ObtenirIdLligaCapitaPerCorreu(String^ correuCapita) {
            String^ query =
                "SELECT T.idLliga FROM Temporada T "
                "INNER JOIN Equip E ON T.idTemporada = E.idTemporada "
                "INNER JOIN Capita C ON E.idEquip = C.idEquip "
                "INNER JOIN Usuari U ON C.identificador = U.identificador "
                "WHERE U.correu_electronic = @correu";
            return EscalarString(connectionString, query, Params1("@correu", correuCapita));
        }

        DataTable^ CercadoraLliga::ObtenirTotesLligues() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga, nom FROM Lliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

        DataTable^ CercadoraLliga::ObtenirEstatLligues() {
            String^ consulta =
                "SELECT L.nom AS Lliga, L.disciplina AS Esport, "
                "T.dataInici AS DataInici, T.dataFi AS DataFi, T.estat AS EstatTemporada "
                "FROM Lliga L "
                "LEFT JOIN Temporada T ON L.idLliga = T.idLliga "
                "ORDER BY L.nom, T.dataInici DESC";
            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CercadoraLliga::ObtenirEstadistiquesEquipsGenerals() {
            String^ consulta =
                "SELECT IFNULL(L.nom, 'Sense lliga') AS Lliga, E.nom AS Equip, E.esport AS Esport, "
                "E.partitsJugats AS PartitsJugats, E.victories AS Victories, "
                "E.derrotes AS Derrotes, E.empats AS Empats, E.punts AS Punts, "
                "E.golsAFavor AS GolsAFavor, E.golsEnContra AS GolsEnContra, "
                "E.diferenciaGols AS DiferenciaGols, E.posicioClassificacio AS Posicio "
                "FROM Equip E "
                "LEFT JOIN Temporada T ON E.idTemporada = T.idTemporada "
                "LEFT JOIN Lliga L ON T.idLliga = L.idLliga "
                "ORDER BY L.nom, E.punts DESC, E.diferenciaGols DESC";
            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CercadoraLliga::ObtenirClassificacioLliga(String^ idLliga) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            DataTable^ taula = gcnew DataTable();
            if (!String::IsNullOrWhiteSpace(idTemporada)) {
                String^ query =
                    "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
                    "E.derrotes AS D, E.golsAFavor AS GF, E.golsEnContra AS GC, "
                    "E.diferenciaGols AS DG, E.punts AS Punts "
                    "FROM Equip E "
                    "WHERE E.idTemporada = @idTemporada "
                    "ORDER BY E.punts DESC, E.diferenciaGols DESC";
                taula = ExecutaConsulta(connectionString, query, Params1("@idTemporada", idTemporada));
            }
            return taula;
        }

        DataTable^ CercadoraLliga::ObtenirProximsPartits(String^ idLliga, int limit) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            DataTable^ taula = gcnew DataTable();
            if (!String::IsNullOrWhiteSpace(idTemporada)) {
                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                    "el.nom AS Local, ev.nom AS Visitant, p.ubicacio AS Ubicacio, p.estat AS Estat "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE j.idTemporada = @idTemporada AND p.dataHora >= NOW() "
                    "ORDER BY p.dataHora ASC LIMIT @limit";
                taula = ExecutaConsulta(connectionString, query, Params2("@idTemporada", idTemporada, "@limit", limit));
            }
            return taula;
        }

        DataTable^ CercadoraLliga::ObtenirUltimsResultats(String^ idLliga, int limit) {
            String^ idTemporada = ObtenirIdTemporadaRellevant(idLliga);
            DataTable^ taula = gcnew DataTable();
            if (!String::IsNullOrWhiteSpace(idTemporada)) {
                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                    "el.nom AS Local, ev.nom AS Visitant, p.golsLocal AS GolsLocal, "
                    "p.golsVisitant AS GolsVisitant, p.estat AS Estat "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE j.idTemporada = @idTemporada AND p.estat = 'Finalitzat' "
                    "ORDER BY p.dataHora DESC LIMIT @limit";
                taula = ExecutaConsulta(connectionString, query, Params2("@idTemporada", idTemporada, "@limit", limit));
            }
            return taula;
        }

        DataTable^ CercadoraLliga::ObtenirTemporadesLligaEstadistiques(String^ idLliga) {
            String^ query =
                "SELECT idTemporada, CONCAT('Temporada ', DATE_FORMAT(dataInici, '%Y'), '-', DATE_FORMAT(dataFi, '%Y')) AS NomTemporada "
                "FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
            return ExecutaConsulta(connectionString, query, Params1("@idLliga", idLliga));
        }

        DataTable^ CercadoraLliga::ObtenirClassificacioLligaEstadistiques(String^ idLliga) {
            String^ query =
                "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
                "E.derrotes AS D, E.golsAFavor AS GF, E.golsEnContra AS GC, "
                "E.diferenciaGols AS DG, E.punts AS Punts "
                "FROM Equip E "
                "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                "WHERE T.idLliga = @idLliga "
                "ORDER BY E.punts DESC, E.diferenciaGols DESC";
            return ExecutaConsulta(connectionString, query, Params1("@idLliga", idLliga));
        }

    }
}
