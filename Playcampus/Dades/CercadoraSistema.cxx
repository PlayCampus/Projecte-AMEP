#include "pch.h"
#include "CercadoraSistema.hxx"

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

        CercadoraSistema::CercadoraSistema(String^ connStr) {
            connectionString = connStr;
        }

        String^ CercadoraSistema::ObtenirIdEquipCapitaPerCorreu(String^ correu) {
            return EscalarString(connectionString,
                "SELECT C.idEquip FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu LIMIT 1",
                Params1("@correu", correu));
        }

        String^ CercadoraSistema::ObtenirIdEquipCapitaPerIdentificador(String^ identificador) {
            return EscalarString(connectionString,
                "SELECT idEquip FROM Capita WHERE identificador = @identificador LIMIT 1",
                Params1("@identificador", identificador));
        }

        bool CercadoraSistema::ExisteixEquip(String^ idEquip) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip",
                Params1("@idEquip", idEquip));
        }

        bool CercadoraSistema::JugadorPertanyAEquip(String^ idJugador, String^ idEquip) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip",
                Params2("@idJugador", idJugador, "@idEquip", idEquip));
        }

        bool CercadoraSistema::PartitDisponiblePerEquip(String^ idPartit, String^ idEquip) {
            String^ query =
                "SELECT COUNT(*) FROM Partit "
                "WHERE idPartit = @idPartit "
                "AND (idEquipLocal = @idEquip OR idEquipVisitant = @idEquip) "
                "AND (estat IS NULL OR LOWER(estat) <> 'finalitzat')";
            return EscalarBoolCount(connectionString, query, Params2("@idPartit", idPartit, "@idEquip", idEquip));
        }

        bool CercadoraSistema::AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = @idPartit AND idJugador = @idJugador",
                Params2("@idPartit", idPartit, "@idJugador", idJugador));
        }

        String^ CercadoraSistema::ObtenirNomUsuariPerIdentificador(String^ identificador) {
            return EscalarString(connectionString,
                "SELECT nom FROM Usuari WHERE identificador = @id",
                Params1("@id", identificador));
        }

        String^ CercadoraSistema::ObtenirIdEquipPerNomExacte(String^ nomEquip) {
            return EscalarString(connectionString,
                "SELECT idEquip FROM Equip WHERE nom COLLATE utf8mb4_bin = @nom LIMIT 1",
                Params1("@nom", nomEquip));
        }

        List<String^>^ CercadoraSistema::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
            List<String^>^ equips = gcnew List<String^>();
            DataTable^ taula = ExecutaConsulta(connectionString,
                "SELECT e.nom FROM Equip e INNER JOIN Temporada t ON e.idTemporada = t.idTemporada INNER JOIN Lliga l ON t.idLliga = l.idLliga WHERE l.nom = @nomLliga",
                Params1("@nomLliga", nomLliga));
            for each (DataRow^ fila in taula->Rows) {
                equips->Add(fila["nom"]->ToString());
            }
            return equips;
        }

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirPartitsDisponiblesEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
                "el.nom AS equipLocal, ev.nom AS equipVisitant "
                "FROM Partit p "
                "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "WHERE (p.idEquipLocal = @idEquip OR p.idEquipVisitant = @idEquip) "
                "AND (p.estat IS NULL OR LOWER(p.estat) <> 'finalitzat') "
                "ORDER BY p.dataHora ASC";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                partit["idPartit"] = row["idPartit"]->ToString();
                partit["dataHora"] = row["dataHora"]->ToString();
                partit["ubicacio"] = row["ubicacio"]->ToString();
                partit["estat"] = row["estat"]->ToString();
                partit["equipLocal"] = row["equipLocal"]->ToString();
                partit["equipVisitant"] = row["equipVisitant"]->ToString();
                partits->Add(partit);
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirJugadorsEquipPerAssignacio(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT J.idJugador, U.nom, J.dorsal, J.posicio "
                "FROM Jugador J "
                "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                "WHERE J.idEquip = @idEquip "
                "ORDER BY J.dorsal ASC, U.nom ASC";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
                jugador["idJugador"] = row["idJugador"]->ToString();
                jugador["nom"] = row["nom"]->ToString();
                jugador["dorsal"] = row["dorsal"]->ToString();
                jugador["posicio"] = row["posicio"]->ToString();
                jugadors->Add(jugador);
            }
            return jugadors;
        }

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirPlantillaPerEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            String^ query =
                "SELECT j.idJugador, u.nom, j.dorsal, j.posicio "
                "FROM Jugador j "
                "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                "WHERE j.idEquip = @idEquip "
                "ORDER BY j.dorsal ASC";
            DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
            for each (DataRow^ row in taula->Rows) {
                Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
                jugador["idJugador"] = row["idJugador"]->ToString();
                jugador["nom"] = row["nom"]->ToString();
                jugador["dorsal"] = row["dorsal"]->ToString();
                jugador["posicio"] = row["posicio"]->ToString();
                jugadors->Add(jugador);
            }
            return jugadors;
        }

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirPartitsCapita(String^ correuCapita) {
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

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirPartitsDeLEquip(String^ idEquip) {
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

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
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

        Dictionary<String^, String^>^ CercadoraSistema::ObtenirAvisPendent(String^ correuJugador) {
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

        String^ CercadoraSistema::ObtenirNomLligaAdmin(String^ correuAdmin) {
            String^ query =
                "SELECT l.nom "
                "FROM Lliga l "
                "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                "WHERE u.correu_electronic = @correuAdmin "
                "ORDER BY l.nom "
                "LIMIT 1";
            return EscalarString(connectionString, query, Params1("@correuAdmin", correuAdmin));
        }

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirPartitsPerLliga(String^ nomLliga) {
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

        Dictionary<String^, String^>^ CercadoraSistema::ObtenirDetallPartit(String^ idPartit) {
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

        List<Dictionary<String^, String^>^>^ CercadoraSistema::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
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

        Dictionary<String^, String^>^ CercadoraSistema::ObtenirEquipsPartit(String^ idPartit) {
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

        String^ CercadoraSistema::ObtenirPosicioJugador(String^ idJugador) {
            return EscalarString(connectionString,
                "SELECT posicio FROM Jugador WHERE idJugador = @idJugador LIMIT 1",
                Params1("@idJugador", idJugador));
        }

        Dictionary<String^, String^>^ CercadoraSistema::ObtenirEstadisticaIndividual(String^ idPartit, String^ idJugador) {
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

        String^ CercadoraSistema::ObtenirIdUsuariPerCorreuString(String^ correu) {
            return EscalarString(connectionString,
                "SELECT identificador FROM Usuari WHERE correu_electronic = @correu LIMIT 1",
                Params1("@correu", correu));
        }

        int CercadoraSistema::ObtenirIdUsuariPerCorreuInt(String^ correu) {
            int idUsuari = -1;
            Object^ resultat = ExecutaEscalar(connectionString,
                "SELECT identificador FROM Usuari WHERE correu_electronic = @correu",
                Params1("@correu", correu));
            if (resultat != nullptr && resultat != DBNull::Value) {
                idUsuari = Convert::ToInt32(resultat);
            }
            return idUsuari;
        }

        String^ CercadoraSistema::ObtenirTipusUsuariPerCorreu(String^ correu) {
            return EscalarString(connectionString,
                "SELECT Tipus FROM Usuari WHERE correu_electronic = @correu LIMIT 1",
                Params1("@correu", correu));
        }

        bool CercadoraSistema::CapitaTeEquip(String^ correu) {
            bool teEquip = false;
            String^ idEquip = ObtenirIdEquipCapitaPerCorreu(correu);
            if (!String::IsNullOrWhiteSpace(idEquip)) {
                teEquip = true;
            }
            return teEquip;
        }

        bool CercadoraSistema::EquipEstaEnLliga(String^ correu) {
            bool esta = false;
            Object^ result = ExecutaEscalar(connectionString,
                "SELECT E.idTemporada FROM Equip E JOIN Capita C ON E.idEquip = C.idEquip JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu",
                Params1("@correu", correu));
            if (result != nullptr && result != DBNull::Value) {
                String^ idTemporada = result->ToString();
                if (!String::IsNullOrWhiteSpace(idTemporada)) {
                    esta = true;
                }
            }
            return esta;
        }

        String^ CercadoraSistema::ObtenirIdLligaPerNom(String^ nomLliga) {
            return EscalarString(connectionString,
                "SELECT idLliga FROM Lliga WHERE nom = @nomLliga",
                Params1("@nomLliga", nomLliga));
        }

        String^ CercadoraSistema::ObtenirNomLligaPerId(String^ idLliga) {
            return EscalarString(connectionString,
                "SELECT nom FROM Lliga WHERE idLliga = @idLliga",
                Params1("@idLliga", idLliga));
        }

        String^ CercadoraSistema::ObtenirContrasenyaLligaPerNom(String^ nomLliga) {
            return EscalarString(connectionString,
                "SELECT contrasenya FROM Lliga WHERE nom = @nomLliga",
                Params1("@nomLliga", nomLliga));
        }

        String^ CercadoraSistema::ObtenirIdLligaSeguida(int idUsuari) {
            return EscalarString(connectionString,
                "SELECT idLliga FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari LIMIT 1",
                Params1("@idUsuari", idUsuari));
        }

        String^ CercadoraSistema::ObtenirIdTemporadaRellevant(String^ idLliga) {
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

        String^ CercadoraSistema::ObtenirDisciplinaLliga(String^ idLliga) {
            return EscalarString(connectionString,
                "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga",
                Params1("@idLliga", idLliga));
        }

        DataTable^ CercadoraSistema::ObtenirProgramacioPartits() {
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

        DataTable^ CercadoraSistema::ObtenirEstatLligues() {
            String^ consulta =
                "SELECT L.nom AS Lliga, L.disciplina AS Esport, "
                "T.dataInici AS DataInici, T.dataFi AS DataFi, T.estat AS EstatTemporada "
                "FROM Lliga L "
                "LEFT JOIN Temporada T ON L.idLliga = T.idLliga "
                "ORDER BY L.nom, T.dataInici DESC";
            return ExecutaConsulta(connectionString, consulta, nullptr);
        }

        DataTable^ CercadoraSistema::ObtenirEstadistiquesEquipsGenerals() {
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

        DataTable^ CercadoraSistema::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
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

        DataTable^ CercadoraSistema::ObtenirUltimsFitxatges(int limit) {
            String^ consulta =
                "SELECT DATE_FORMAT(J.data_naixement, '%d/%m/%Y') AS Data, "
                "U.nom AS Jugador, E.nom AS Equip, J.dorsal AS Dorsal, J.posicio AS Posicio "
                "FROM Jugador J "
                "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                "LEFT JOIN Equip E ON J.idEquip = E.idEquip "
                "ORDER BY U.data_registre DESC "
                "LIMIT @limit";
            return ExecutaConsulta(connectionString, consulta, Params1("@limit", limit));
        }

        DataTable^ CercadoraSistema::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            String^ consulta =
                "SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
                "E.partitsJugats AS Partits, E.victories AS Victories, E.punts AS Punts "
                "FROM Equip E "
                "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                "WHERE U.correu_electronic = @correuAdmin "
                "ORDER BY E.nom";
            return ExecutaConsulta(connectionString, consulta, Params1("@correuAdmin", correuAdmin));
        }

        String^ CercadoraSistema::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            String^ consulta =
                "SELECT L.nom FROM Lliga L "
                "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                "WHERE U.correu_electronic = @correuAdmin "
                "ORDER BY L.nom LIMIT 1";
            return EscalarString(connectionString, consulta, Params1("@correuAdmin", correuAdmin));
        }

        static bool EquipTeColumnaSistema(String^ connectionString, String^ nomColumna) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna",
                Params1("@nomColumna", nomColumna));
        }

        DataTable^ CercadoraSistema::ObtenirTelefonsAdministradorPerCapita(String^ correuCapita) {
            bool equipTeIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                : "INNER JOIN Lliga L ON L.idLliga = E.idLliga ";
            String^ consulta =
                "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                "COALESCE(A.telefonContacte, '') AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                "FROM Usuari UC "
                "INNER JOIN Capita C ON C.identificador = UC.identificador "
                "INNER JOIN Equip E ON E.idEquip = C.idEquip " +
                relacioLliga +
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UC.correu_electronic = @correuUsuari "
                "ORDER BY L.nom ASC, UA.nom ASC";
            return ExecutaConsulta(connectionString, consulta, Params1("@correuUsuari", correuCapita));
        }

        DataTable^ CercadoraSistema::ObtenirTelefonsContactePerJugador(String^ correuJugador) {
            bool equipTeIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                : "INNER JOIN Lliga L ON L.idLliga = E.idLliga ";
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
                "INNER JOIN Equip E ON E.idEquip = J.idEquip " +
                relacioLliga +
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UJ.correu_electronic = @correuUsuari "
                "ORDER BY Rol ASC, Nom ASC";
            return ExecutaConsulta(connectionString, consulta, Params1("@correuUsuari", correuJugador));
        }

        DataTable^ CercadoraSistema::ObtenirTelefonsCapitansPerAdministrador(String^ correuAdministrador) {
            bool equipTeIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Lliga L ON L.idAdministrador = ALogin.identificador INNER JOIN Temporada T ON T.idLliga = L.idLliga INNER JOIN Equip E ON E.idTemporada = T.idTemporada "
                : "INNER JOIN Lliga L ON L.idAdministrador = ALogin.identificador INNER JOIN Equip E ON E.idLliga = L.idLliga ";
            String^ consulta =
                "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                "COALESCE(C.telefonContacte, '') AS Telefon, COALESCE(E.nom, '') AS Equip, "
                "COALESCE(L.nom, '') AS Lliga "
                "FROM Usuari UA "
                "INNER JOIN Administrador ALogin ON ALogin.identificador = UA.identificador " +
                relacioLliga +
                "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                "WHERE UA.correu_electronic = @correuUsuari "
                "ORDER BY L.nom ASC, E.nom ASC, UC.nom ASC";
            return ExecutaConsulta(connectionString, consulta, Params1("@correuUsuari", correuAdministrador));
        }

        DataTable^ CercadoraSistema::ObtenirClassificacioLliga(String^ idLliga) {
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

        DataTable^ CercadoraSistema::ObtenirProximsPartits(String^ idLliga, int limit) {
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

        DataTable^ CercadoraSistema::ObtenirUltimsResultats(String^ idLliga, int limit) {
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

        bool CercadoraSistema::ExisteixEquipPerNom(String^ nomEquip) {
            return EscalarBoolCount(connectionString,
                "SELECT COUNT(*) FROM Equip WHERE nom = @nomEquip",
                Params1("@nomEquip", nomEquip));
        }

        DataTable^ CercadoraSistema::ObtenirLliguesEquip(String^ nomEquip) {
            String^ consulta = nullptr;
            bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
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
            return ExecutaConsulta(connectionString, consulta, Params1("@nomEquip", nomEquip));
        }

        DataTable^ CercadoraSistema::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            String^ consulta = nullptr;
            bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
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
            return ExecutaConsulta(connectionString, consulta, Params2("@nomEquip", nomEquip, "@idLliga", idLliga));
        }

        DataTable^ CercadoraSistema::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            String^ condicioAssociacio = "P.idPartit IS NOT NULL";
            bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
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
            return ExecutaConsulta(connectionString, consultaBase + condicioAssociacio + consultaFinal,
                Params3("@nomEquip", nomEquip, "@idLliga", idLliga, "@idTemporada", idTemporada));
        }

        DataTable^ CercadoraSistema::ObtenirTotesEstadistiquesJugadors() {
            String^ query =
                "SELECT u.identificador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS Posicio, "
                "j.partitsJugats AS PartitsJugats, j.anotacions AS Anotacions, j.assistencies AS Assistencies, "
                "j.faltesLleus AS FaltesLleus, j.faltesGreus AS FaltesGreus, j.minutsJugats AS MinutsJugats "
                "FROM Jugador j INNER JOIN Usuari u ON j.idJugador = u.identificador "
                "ORDER BY u.nom ASC";
            return ExecutaConsulta(connectionString, query, nullptr);
        }

        DataTable^ CercadoraSistema::ObtenirEstadistiquesJugador(String^ idJugador) {
            String^ query =
                "SELECT u.identificador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS Posicio, "
                "j.partitsJugats AS PartitsJugats, j.anotacions AS Anotacions, j.assistencies AS Assistencies, "
                "j.faltesLleus AS FaltesLleus, j.faltesGreus AS FaltesGreus, j.minutsJugats AS MinutsJugats, j.idEquip AS IdEquip "
                "FROM Jugador j INNER JOIN Usuari u ON j.idJugador = u.identificador "
                "WHERE j.idJugador = @idJugador";
            return ExecutaConsulta(connectionString, query, Params1("@idJugador", idJugador));
        }

        DataTable^ CercadoraSistema::ObtenirDetallsPartitEstadistiques(String^ idPartit) {
            String^ query =
                "SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant, "
                "p.golsLocal AS GolsLocals, p.golsVisitant AS GolsVisitants "
                "FROM Partit p "
                "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                "WHERE p.idPartit = @idPartit";
            return ExecutaConsulta(connectionString, query, Params1("@idPartit", idPartit));
        }

        DataTable^ CercadoraSistema::ObtenirEstadistiquesPartit(String^ idPartit) {
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

        String^ CercadoraSistema::ObtenirIdLligaAdminPerCorreu(String^ correuAdmin) {
            String^ query =
                "SELECT L.idLliga FROM Lliga L "
                "INNER JOIN Administrador A ON L.idAdministrador = A.identificador "
                "INNER JOIN Usuari U ON A.identificador = U.identificador "
                "WHERE U.correu_electronic = @correu";
            return EscalarString(connectionString, query, Params1("@correu", correuAdmin));
        }

        String^ CercadoraSistema::ObtenirIdLligaCapitaPerCorreu(String^ correuCapita) {
            String^ query =
                "SELECT T.idLliga FROM Temporada T "
                "INNER JOIN Equip E ON T.idTemporada = E.idTemporada "
                "INNER JOIN Capita C ON E.idEquip = C.idEquip "
                "INNER JOIN Usuari U ON C.identificador = U.identificador "
                "WHERE U.correu_electronic = @correu";
            return EscalarString(connectionString, query, Params1("@correu", correuCapita));
        }

        DataTable^ CercadoraSistema::ObtenirTemporadesLligaEstadistiques(String^ idLliga) {
            String^ query =
                "SELECT idTemporada, CONCAT('Temporada ', DATE_FORMAT(dataInici, '%Y'), '-', DATE_FORMAT(dataFi, '%Y')) AS NomTemporada "
                "FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
            return ExecutaConsulta(connectionString, query, Params1("@idLliga", idLliga));
        }

        DataTable^ CercadoraSistema::ObtenirClassificacioLligaEstadistiques(String^ idLliga) {
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
