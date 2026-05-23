#include "pch.h"
#include "CercadoraPartit.hxx"

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

        static Dictionary<String^, Object^>^ Params3(String^ k1, Object^ v1, String^ k2, Object^ v2, String^ k3, Object^ v3) {
            Dictionary<String^, Object^>^ p = Params2(k1, v1, k2, v2);
            p[k3] = v3;
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

        static bool EscalarBoolCount(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            bool existeix = false;
            Object^ resultat = ExecutaEscalar(connectionString, query, parametres);
            if (resultat != nullptr && resultat != DBNull::Value) {
                existeix = Convert::ToInt32(resultat) > 0;
            }
            return existeix;
        }

        CercadoraPartit::CercadoraPartit(String^ connStr) {
            connectionString = connStr;
        }

        DataTable^ CercadoraPartit::ObtenirPartits() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada, idEquipLocal, idEquipVisitant FROM Partit";
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(query, conn);
                da->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsPerJornada(String^ idJornada) {
            List<Dictionary<String^, String^>^>^ llista = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                String^ query = "SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
                    "el.Nom AS equipLocal, ev.Nom AS equipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE p.idJornada = @idJornada "
                    "ORDER BY p.dataHora ASC";


                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idJornada", idJornada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                    partit["idPartit"] = reader["idPartit"]->ToString();
                    partit["dataHora"] = Convert::ToDateTime(reader["dataHora"]).ToString("dd/MM/yyyy HH:mm");
                    partit["ubicacio"] = reader["ubicacio"]->ToString();
                    partit["estat"] = reader["estat"]->ToString();
                    partit["equipLocal"] = reader["equipLocal"]->ToString();
                    partit["equipVisitant"] = reader["equipVisitant"]->ToString();
                    llista->Add(partit);
                }
            }
            finally {
                conn->Close();
            }

            return llista;
        }

        DataTable^ CercadoraPartit::ObtenirPartitsFinalitzatsPerTemporada(String^ idTemporada) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE j.idTemporada = @idTemporada AND p.estat = 'Finalitzat' "
                    "ORDER BY p.dataHora DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

        bool CercadoraPartit::PartitDisponiblePerEquip(String^ idPartit, String^ idEquip) {
            String^ query =
                "SELECT COUNT(*) FROM Partit "
                "WHERE idPartit = @idPartit "
                "AND (idEquipLocal = @idEquip OR idEquipVisitant = @idEquip) "
                "AND (estat IS NULL OR LOWER(estat) <> 'finalitzat')";
            return EscalarBoolCount(connectionString, query, Params2("@idPartit", idPartit, "@idEquip", idEquip));
        }

        bool CercadoraPartit::AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = @idPartit AND idJugador = @idJugador",
                Params2("@idPartit", idPartit, "@idJugador", idJugador));
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsCapita(String^ correuCapita) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT p.idPartit, el.nom AS local, ev.nom AS visitant, p.dataHora, "
                "CONCAT(el.nom, ' vs ', ev.nom, ' (', p.dataHora, ')') AS nomMostrar "
                "FROM Partit p "
                "JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "WHERE (p.idEquipLocal = ("
                "   SELECT c.idEquip FROM Capita c JOIN Usuari u ON c.identificador = u.identificador WHERE u.correu_electronic = @correu LIMIT 1"
                ") "
                "OR p.idEquipVisitant = ("
                "   SELECT c.idEquip FROM Capita c JOIN Usuari u ON c.identificador = u.identificador WHERE u.correu_electronic = @correu LIMIT 1"
                ")) "
                "AND p.estat = 'Pendent' "
                "ORDER BY p.dataHora DESC";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@correu", correuCapita));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                d["id_partit"] = row["idPartit"]->ToString();
                d["equip_local"] = row["local"]->ToString();
                d["equip_visitant"] = row["visitant"]->ToString();
                d["data"] = row["dataHora"]->ToString();
                d["nomMostrar"] = row["nomMostrar"]->ToString();
                partits->Add(d);
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsDeLEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            DataTable^ taula = ExecutaConsulta(connectionString,
                "SELECT idPartit, dataHora FROM Partit WHERE idEquipLocal = @id OR idEquipVisitant = @id",
                Params1("@id", idEquip));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                d["idPartit"] = row["idPartit"]->ToString();
                d["dataHora"] = row["dataHora"]->ToString();
                partits->Add(d);
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT j.idJugador, u.nom, j.posicio, "
                "cp.convocat AS convocat, cp.confirmat AS confirmat "
                "FROM Jugador j "
                "JOIN Usuari u ON j.idJugador = u.identificador "
                "LEFT JOIN ConvocatoriaPartit cp ON j.idJugador = cp.idJugador AND cp.idPartit = @idPartit "
                "WHERE j.idEquip = @idEquip";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params2("@idPartit", idPartit, "@idEquip", idEquip));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                d["id_jugador"] = row["idJugador"]->ToString();
                d["nom"] = row["nom"]->ToString();
                d["posicio"] = row["posicio"]->ToString();
                if (row["convocat"] == DBNull::Value) {
                    d["estat_convocatoria"] = "Sense establir";
                }
                else if (row["convocat"]->ToString() == "1" || row["convocat"]->ToString() == "True") {
                    d["estat_convocatoria"] = "Convocat";
                }
                else {
                    d["estat_convocatoria"] = "No Convocat";
                }
                if (row["confirmat"] == DBNull::Value) {
                    d["confirmacio"] = "Pendent";
                }
                else if (row["confirmat"]->ToString() == "1" || row["confirmat"]->ToString() == "True") {
                    d["confirmacio"] = "Confirmat";
                }
                else {
                    d["confirmacio"] = "D'acord";
                }
                jugadors->Add(d);
            }
            return jugadors;
        }

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirAvisPendent(String^ correuJugador) {
            Dictionary<String^, String^>^ avis = nullptr;
            String^ query =
                "SELECT cp.idPartit, cp.convocat, p.dataHora, el.nom AS local, ev.nom AS visitant "
                "FROM ConvocatoriaPartit cp "
                "JOIN Partit p ON cp.idPartit = p.idPartit "
                "JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "JOIN Jugador j ON cp.idJugador = j.idJugador "
                "JOIN Usuari u ON j.idJugador = u.identificador "
                "WHERE u.correu_electronic = @correu AND cp.convocat IS NOT NULL AND cp.confirmat IS NULL LIMIT 1";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@correu", correuJugador));
            if (taula->Rows->Count > 0) {
                DataRow^ row = taula->Rows[0];
                avis = gcnew Dictionary<String^, String^>();
                avis["idPartit"] = row["idPartit"]->ToString();
                String^ estatConvocat = row["convocat"]->ToString();
                if (estatConvocat == "1" || estatConvocat == "True") {
                    avis["tipus"] = "convocat";
                    avis["missatge"] = "Has estat convocat pel partit:\n" + row["local"]->ToString() + " vs " + row["visitant"]->ToString() + "\n(" + row["dataHora"]->ToString() + ")";
                }
                else {
                    avis["tipus"] = "no_convocat";
                    avis["missatge"] = "No has estat convocat pel partit:\n" + row["local"]->ToString() + " vs " + row["visitant"]->ToString() + "\n(" + row["dataHora"]->ToString() + ")";
                }
            }
            return avis;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsPerLliga(String^ nomLliga) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT p.idPartit, p.dataHora, p.estat, p.golsLocal, p.golsVisitant, "
                "el.nom AS equipLocal, ev.nom AS equipVisitant "
                "FROM Partit p "
                "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                "INNER JOIN Lliga l ON t.idLliga = l.idLliga "
                "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "WHERE l.nom = @nomLliga "
                "ORDER BY p.dataHora DESC";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@nomLliga", nomLliga));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ p = gcnew Dictionary<String^, String^>();
                p["idPartit"] = row["idPartit"]->ToString();
                p["dataHora"] = row["dataHora"]->ToString();
                p["estat"] = row["estat"]->ToString();
                p["golsLocal"] = row["golsLocal"]->ToString();
                p["golsVisitant"] = row["golsVisitant"]->ToString();
                p["equipLocal"] = row["equipLocal"]->ToString();
                p["equipVisitant"] = row["equipVisitant"]->ToString();
                partits->Add(p);
            }
            return partits;
        }

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirDetallPartit(String^ idPartit) {
            Dictionary<String^, String^>^ detall = nullptr;
            String^ query =
                "SELECT p.idPartit, p.estat, p.golsLocal, p.golsVisitant, l.disciplina, u.correu_electronic AS correuAdmin "
                "FROM Partit p "
                "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                "INNER JOIN Lliga l ON t.idLliga = l.idLliga "
                "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                "WHERE p.idPartit = @idPartit LIMIT 1";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idPartit", idPartit));
            if (taula->Rows->Count > 0) {
                DataRow^ row = taula->Rows[0];
                detall = gcnew Dictionary<String^, String^>();
                detall["idPartit"] = row["idPartit"]->ToString();
                detall["estat"] = row["estat"]->ToString();
                detall["golsLocal"] = row["golsLocal"]->ToString();
                detall["golsVisitant"] = row["golsVisitant"]->ToString();
                detall["disciplina"] = row["disciplina"]->ToString();
                detall["correuAdmin"] = row["correuAdmin"]->ToString();
                detall["stats"] = "";
            }
            return detall;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            Dictionary<String^, String^>^ equipsPartit = ObtenirEquipsPartit(idPartit);
            if (equipsPartit == nullptr) {
                throw gcnew Exception("No s'ha trobat el partit seleccionat.");
            }
            if (!equipsPartit["correuAdmin"]->Equals(correuAdmin, StringComparison::OrdinalIgnoreCase)) {
                throw gcnew UnauthorizedAccessException("No tens permisos per editar aquest partit.");
            }
            String^ idEquipLocal = equipsPartit["idEquipLocal"];
            String^ idEquipVisitant = equipsPartit["idEquipVisitant"];
            String^ nomEquipLocal = equipsPartit["nomEquipLocal"];
            String^ nomEquipVisitant = equipsPartit["nomEquipVisitant"];
            String^ query =
                "SELECT u.nom AS nomJugador, j.idEquip, j.idJugador, "
                "IFNULL(pei.golsmarcat, 0) AS estadistica1, "
                "IFNULL(pei.asistencies, 0) AS estadistica2, "
                "IFNULL(pei.targetesgrogues, 0) AS estadistica3, "
                "IFNULL(pei.targetesvermelles, 0) AS estadistica4 "
                "FROM Jugador j "
                "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                "LEFT JOIN AssignacioJugadorPartit ajp ON j.idJugador = ajp.idJugador AND ajp.idPartit = @idPartit "
                "LEFT JOIN ConvocatoriaPartit cp ON j.idJugador = cp.idJugador AND cp.idPartit = @idPartit AND cp.convocat = 1 "
                "LEFT JOIN PartitEstadisticaIndividual pei ON j.idJugador = pei.idJugador AND pei.idPartit = @idPartit "
                "WHERE (j.idEquip = @idLocal OR j.idEquip = @idVisitant) "
                "AND (ajp.idJugador IS NOT NULL OR cp.idJugador IS NOT NULL "
                "OR (NOT EXISTS (SELECT 1 FROM AssignacioJugadorPartit ajp2 WHERE ajp2.idPartit = @idPartit) "
                "AND NOT EXISTS (SELECT 1 FROM ConvocatoriaPartit cp2 WHERE cp2.idPartit = @idPartit AND cp2.convocat = 1))) "
                "ORDER BY CASE WHEN j.idEquip = @idLocal THEN 0 ELSE 1 END, u.nom";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params3("@idPartit", idPartit, "@idLocal", idEquipLocal, "@idVisitant", idEquipVisitant));
            for each (DataRow^ row in taula->Rows) {
                String^ idEquip = row["idEquip"]->ToString();
                Dictionary<String^, String^>^ j = gcnew Dictionary<String^, String^>();
                j["idJugador"] = row["idJugador"]->ToString();
                j["nomJugador"] = row["nomJugador"]->ToString();
                j["equip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? "Local" : "Visitant";
                j["nomEquip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? nomEquipLocal : nomEquipVisitant;
                j["estadistica1"] = row["estadistica1"]->ToString();
                j["estadistica2"] = row["estadistica2"]->ToString();
                j["estadistica3"] = row["estadistica3"]->ToString();
                j["estadistica4"] = row["estadistica4"]->ToString();
                jugadors->Add(j);
            }
            return jugadors;
        }

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirEquipsPartit(String^ idPartit) {
            Dictionary<String^, String^>^ dades = nullptr;
            String^ query =
                "SELECT p.idEquipLocal, p.idEquipVisitant, el.nom AS nomEquipLocal, ev.nom AS nomEquipVisitant, "
                "u.correu_electronic AS correuAdmin "
                "FROM Partit p "
                "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                "INNER JOIN Lliga l ON t.idLliga = l.idLliga "
                "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                "WHERE p.idPartit = @idPartit LIMIT 1";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idPartit", idPartit));
            if (taula->Rows->Count > 0) {
                DataRow^ row = taula->Rows[0];
                dades = gcnew Dictionary<String^, String^>();
                dades["idEquipLocal"] = row["idEquipLocal"]->ToString();
                dades["idEquipVisitant"] = row["idEquipVisitant"]->ToString();
                dades["nomEquipLocal"] = row["nomEquipLocal"]->ToString();
                dades["nomEquipVisitant"] = row["nomEquipVisitant"]->ToString();
                dades["correuAdmin"] = row["correuAdmin"]->ToString();
            }
            return dades;
        }

        String^ CercadoraPartit::ObtenirPosicioJugador(String^ idJugador) {
            return EscalarString(connectionString,
                "SELECT posicio FROM Jugador WHERE idJugador = @idJugador LIMIT 1",
                Params1("@idJugador", idJugador));
        }

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirEstadisticaIndividual(String^ idPartit, String^ idJugador) {
            Dictionary<String^, String^>^ dades = gcnew Dictionary<String^, String^>();
            dades["existeix"] = "false";
            dades["gols"] = "0";
            dades["assistencies"] = "0";
            dades["targetesGrogues"] = "0";
            dades["targetesVermelles"] = "0";
            String^ query =
                "SELECT golsmarcat, asistencies, targetesgrogues, targetesvermelles "
                "FROM PartitEstadisticaIndividual "
                "WHERE idPartit = @idPartit AND idJugador = @idJugador LIMIT 1";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params2("@idPartit", idPartit, "@idJugador", idJugador));
            if (taula->Rows->Count > 0) {
                DataRow^ row = taula->Rows[0];
                dades["existeix"] = "true";
                dades["gols"] = row["golsmarcat"] == DBNull::Value ? "0" : row["golsmarcat"]->ToString();
                dades["assistencies"] = row["asistencies"] == DBNull::Value ? "0" : row["asistencies"]->ToString();
                dades["targetesGrogues"] = row["targetesgrogues"] == DBNull::Value ? "0" : row["targetesgrogues"]->ToString();
                dades["targetesVermelles"] = row["targetesvermelles"] == DBNull::Value ? "0" : row["targetesvermelles"]->ToString();
            }
            return dades;
        }

        DataTable^ CercadoraPartit::ObtenirProgramacioPartits() {
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

        DataTable^ CercadoraPartit::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            String^ consulta =
                "SELECT J.numero AS Jornada, "
                "EL.nom AS EquipLocal, EV.nom AS EquipVisitant, "
                "P.dataHora AS DataPartit, P.ubicacio AS Ubicacio, P.estat AS Estat, "
                "P.golsLocal AS GolsLocal, P.golsVisitant AS GolsVisitant "
                "FROM Partit P "
                "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                "INNER JOIN Equip EL ON P.idEquipLocal = EL.idEquip "
                "INNER JOIN Equip EV ON P.idEquipVisitant = EV.idEquip "
                "WHERE T.idLliga = @idLliga "
                "ORDER BY J.numero ASC, P.dataHora ASC";
            return ExecutaConsulta(connectionString, consulta, Params1("@idLliga", idLliga));
        }

        DataTable^ CercadoraPartit::ObtenirEstadistiquesPartit(String^ idPartit) {
            String^ query =
                "SELECT pei.idJugador AS IdJugador, pei.nomJugador AS NomJugador, pei.posicio AS Posicio, "
                "pei.targetesgrogues AS TargetesGrogues, pei.targetesvermelles AS TargetesVermelles, pei.golsmarcat AS GolsMarcats, "
                "pei.asistencies AS Assistencies, pei.targetesgroguesobtenides AS TargetesGroguesObtenides, "
                "pei.targetesvermelllesobtenides AS TargetesVermelllesObtenides, pei.dataActualitzacio AS DataActualitzacio, "
                "e.nom AS Equip "
                "FROM PartitEstadisticaIndividual pei "
                "INNER JOIN Jugador j ON pei.idJugador = j.idJugador "
                "INNER JOIN Equip e ON j.idEquip = e.idEquip "
                "WHERE pei.idPartit = @idPartit "
                "ORDER BY e.nom";
            return ExecutaConsulta(connectionString, query, Params1("@idPartit", idPartit));
        }

        DataTable^ CercadoraPartit::ObtenirDetallsPartitEstadistiques(String^ idPartit) {
            String^ query =
                "SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant, "
                "p.golsLocal AS GolsLocals, p.golsVisitant AS GolsVisitants "
                "FROM Partit p "
                "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "WHERE p.idPartit = @idPartit";
            return ExecutaConsulta(connectionString, query, Params1("@idPartit", idPartit));
        }

    }
}
