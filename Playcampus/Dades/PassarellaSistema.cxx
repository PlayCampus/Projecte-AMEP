#include "pch.h"
#include "PassarellaSistema.hxx"
#include "CercadoraSistema.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        static void AfegeixParametresNoQuery(MySqlCommand^ cmd, Dictionary<String^, Object^>^ parametres) {
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

        static Dictionary<String^, Object^>^ Params1W(String^ k1, Object^ v1) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p[k1] = v1;
            return p;
        }

        static Dictionary<String^, Object^>^ Params2W(String^ k1, Object^ v1, String^ k2, Object^ v2) {
            Dictionary<String^, Object^>^ p = Params1W(k1, v1);
            p[k2] = v2;
            return p;
        }

        static int ExecutaNoQuery(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            int files = 0;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                AfegeixParametresNoQuery(cmd, parametres);
                files = cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return files;
        }

        static Object^ ExecutaEscalarW(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                AfegeixParametresNoQuery(cmd, parametres);
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

        PassarellaSistema::PassarellaSistema(String^ connStr) {
            connectionString = connStr;
        }

        void PassarellaSistema::InserirAssignacioJugadorPartit(String^ idPartit, String^ idJugador) {
            String^ query = "INSERT INTO AssignacioJugadorPartit (idPartit, idJugador, dataAssignacio) VALUES (@idPartit, @idJugador, NOW())";
            ExecutaNoQuery(connectionString, query, Params2W("@idPartit", idPartit, "@idJugador", idJugador));
        }

        void PassarellaSistema::ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat) {
            String^ query;
            if (!convocat.HasValue) {
                query = "INSERT INTO ConvocatoriaPartit (idPartit, idJugador, convocat, confirmat) "
                    "VALUES (@idP, @idJ, NULL, NULL) "
                    "ON DUPLICATE KEY UPDATE convocat = NULL, confirmat = NULL";
            }
            else if (convocat.Value == true) {
                query = "INSERT INTO ConvocatoriaPartit (idPartit, idJugador, convocat, confirmat) "
                    "VALUES (@idP, @idJ, 1, NULL) "
                    "ON DUPLICATE KEY UPDATE convocat = 1, confirmat = NULL";
            }
            else {
                query = "INSERT INTO ConvocatoriaPartit (idPartit, idJugador, convocat, confirmat) "
                    "VALUES (@idP, @idJ, 0, NULL) "
                    "ON DUPLICATE KEY UPDATE convocat = 0, confirmat = NULL";
            }
            ExecutaNoQuery(connectionString, query, Params2W("@idP", idPartit, "@idJ", idJugador));
        }

        void PassarellaSistema::ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p["@idP"] = idPartit;
            p["@idJ"] = idJugador;
            p["@conf"] = assisteix ? 1 : 0;
            ExecutaNoQuery(connectionString,
                "UPDATE ConvocatoriaPartit SET confirmat = @conf WHERE idPartit = @idP AND idJugador = @idJ",
                p);
        }

        void PassarellaSistema::ActualitzarJugador(String^ idJugador, int dorsal, String^ posicio) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p["@idJugador"] = idJugador;
            p["@dorsal"] = dorsal;
            p["@posicio"] = posicio;
            ExecutaNoQuery(connectionString,
                "UPDATE Jugador SET dorsal = @dorsal, posicio = @posicio WHERE idJugador = @idJugador",
                p);
        }

        void PassarellaSistema::ExpulsarJugador(String^ idJugador, String^ idEquip) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p["@idJugador"] = idJugador;
            p["@idEquip"] = idEquip;
            int files = ExecutaNoQuery(connectionString,
                "UPDATE Jugador SET idEquip = NULL WHERE idJugador = @idJugador AND idEquip = @idEquip",
                p);
            if (files != 1) {
                throw gcnew Exception("No s'ha pogut expulsar el jugador de l'equip.");
            }
            ExecutaNoQuery(connectionString,
                "UPDATE Usuari SET Tipus = 'Estudiant' WHERE identificador = @idJugador",
                Params1W("@idJugador", idJugador));
            ExecutaNoQuery(connectionString,
                "DELETE FROM Jugador WHERE idJugador = @idJugador AND idEquip IS NULL",
                Params1W("@idJugador", idJugador));
        }

        void PassarellaSistema::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
            p["@idEquip"] = idEquip;
            p["@correuAdmin"] = correuAdmin;
            String^ consulta =
                "UPDATE Equip E "
                "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                "INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
                "SET E.idTemporada = NULL "
                "WHERE E.idEquip = @idEquip AND U.correu_electronic = @correuAdmin";
            int filesAfectades = ExecutaNoQuery(connectionString, consulta, p);
            if (filesAfectades == 0) {
                throw gcnew Exception("No s'ha trobat l'equip dins d'una lliga administrada per aquest usuari.");
            }
        }

        void PassarellaSistema::SeguirLliga(int idUsuari, String^ idLliga) {
            ExecutaNoQuery(connectionString,
                "DELETE FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari",
                Params1W("@idUsuari", idUsuari));
            Dictionary<String^, Object^>^ p = Params2W("@idUsuari", idUsuari, "@idLliga", idLliga);
            ExecutaNoQuery(connectionString,
                "INSERT INTO UsuariSegueixLliga (idUsuari, idLliga, dataSeguiment) VALUES (@idUsuari, @idLliga, NOW())",
                p);
        }

        void PassarellaSistema::DeixarDeSeguir(int idUsuari) {
            ExecutaNoQuery(connectionString,
                "DELETE FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari",
                Params1W("@idUsuari", idUsuari));
        }


        void PassarellaSistema::AssignarEquipACapita(String^ idCapita, String^ idEquip) {
            Dictionary<String^, Object^>^ p = Params2W("@idCapita", idCapita, "@idEquip", idEquip);
            int filesAfectades = ExecutaNoQuery(connectionString,
                "UPDATE Capita SET idEquip = @idEquip WHERE identificador = @idCapita",
                p);
            if (filesAfectades != 1) {
                throw gcnew Exception("No s'ha pogut actualitzar el capita amb l'equip creat.");
            }
            Object^ files = ExecutaEscalarW(connectionString,
                "SELECT COUNT(*) FROM Capita WHERE identificador = @idCapita AND idEquip = @idEquip",
                p);
            if (files == nullptr || files == DBNull::Value || Convert::ToInt32(files) != 1) {
                throw gcnew Exception("La base de dades no ha confirmat l'assignacio de l'equip al capita.");
            }
        }

        void PassarellaSistema::DesassignarEquipCapitaPerCorreu(String^ correuCapita) {
            int filesAfectades = ExecutaNoQuery(connectionString,
                "UPDATE Capita C JOIN Usuari U ON C.identificador = U.identificador SET C.idEquip = NULL WHERE U.correu_electronic = @correu",
                Params1W("@correu", correuCapita));
            if (filesAfectades != 1) {
                throw gcnew Exception("No s'ha pogut desvincular l'equip del capita.");
            }
            Object^ files = ExecutaEscalarW(connectionString,
                "SELECT COUNT(*) FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu AND C.idEquip IS NULL",
                Params1W("@correu", correuCapita));
            if (files == nullptr || files == DBNull::Value || Convert::ToInt32(files) != 1) {
                throw gcnew Exception("La base de dades no ha confirmat que el capita hagi quedat sense equip.");
            }
        }

        void PassarellaSistema::TancarPools() {
            MySqlConnection::ClearAllPools();
        }

        void PassarellaSistema::ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ disciplina, String^ estatAnterior, int golsLocalAnterior, int golsVisitantAnterior, Nullable<DateTime> novaDataPartit) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryEquips = "SELECT idEquipLocal, idEquipVisitant FROM Partit WHERE idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdEquips = gcnew MySqlCommand(queryEquips, conn);
                cmdEquips->Parameters->AddWithValue("@idPartit", idPartit);
                String^ idEquipLocal = nullptr;
                String^ idEquipVisitant = nullptr;
                MySqlDataReader^ readerEquips = cmdEquips->ExecuteReader();
                if (readerEquips->Read()) {
                    idEquipLocal = readerEquips["idEquipLocal"]->ToString();
                    idEquipVisitant = readerEquips["idEquipVisitant"]->ToString();
                }
                readerEquips->Close();

                String^ queryUpdatePartit;
                if (nouEstat == "Aplaçat" && novaDataPartit.HasValue) {
                    queryUpdatePartit = "UPDATE Partit SET estat = @estat, golsLocal = @golsLocal, golsVisitant = @golsVisitant, dataHora = @dataHora WHERE idPartit = @idPartit";
                }
                else {
                    queryUpdatePartit = "UPDATE Partit SET estat = @estat, golsLocal = @golsLocal, golsVisitant = @golsVisitant WHERE idPartit = @idPartit";
                }

                MySqlCommand^ cmdPartit = gcnew MySqlCommand(queryUpdatePartit, conn);
                cmdPartit->Parameters->AddWithValue("@estat", nouEstat);
                cmdPartit->Parameters->AddWithValue("@golsLocal", resultatLocal);
                cmdPartit->Parameters->AddWithValue("@golsVisitant", resultatVisitant);
                cmdPartit->Parameters->AddWithValue("@idPartit", idPartit);
                if (nouEstat == "Aplaçat" && novaDataPartit.HasValue) {
                    cmdPartit->Parameters->AddWithValue("@dataHora", novaDataPartit.Value);
                }
                cmdPartit->ExecuteNonQuery();

                int diffGolsLocal = resultatLocal;
                int diffGolsVisitant = resultatVisitant;

                if (nouEstat == "Finalitzat" && estatAnterior != "Finalitzat") {
                    String^ queryUpdateEquipLocal =
                        "UPDATE Equip SET "
                        "partitsJugats = partitsJugats + 1, "
                        "golsAFavor = golsAFavor + @golsA, "
                        "golsEnContra = golsEnContra + @golsC, "
                        "diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC), "
                        "victories = victories + @victories, "
                        "derrotes = derrotes + @derrotes, "
                        "empats = empats + @empats, "
                        "punts = punts + @punts "
                        "WHERE idEquip = @idEquip";

                    MySqlCommand^ cmdUpdateLocal = gcnew MySqlCommand(queryUpdateEquipLocal, conn);
                    cmdUpdateLocal->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    cmdUpdateLocal->Parameters->AddWithValue("@golsA", diffGolsLocal);
                    cmdUpdateLocal->Parameters->AddWithValue("@golsC", diffGolsVisitant);
                    int vicL = resultatLocal > resultatVisitant ? 1 : 0;
                    int derL = resultatLocal < resultatVisitant ? 1 : 0;
                    int empL = resultatLocal == resultatVisitant ? 1 : 0;
                    int puntsL = (vicL * 3) + (empL * 1);
                    cmdUpdateLocal->Parameters->AddWithValue("@victories", vicL);
                    cmdUpdateLocal->Parameters->AddWithValue("@derrotes", derL);
                    cmdUpdateLocal->Parameters->AddWithValue("@empats", empL);
                    cmdUpdateLocal->Parameters->AddWithValue("@punts", puntsL);
                    cmdUpdateLocal->ExecuteNonQuery();

                    String^ queryUpdateEquipVisitant =
                        "UPDATE Equip SET "
                        "partitsJugats = partitsJugats + 1, "
                        "golsAFavor = golsAFavor + @golsA, "
                        "golsEnContra = golsEnContra + @golsC, "
                        "diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC), "
                        "victories = victories + @victories, "
                        "derrotes = derrotes + @derrotes, "
                        "empats = empats + @empats, "
                        "punts = punts + @punts "
                        "WHERE idEquip = @idEquip";

                    MySqlCommand^ cmdUpdateVisitant = gcnew MySqlCommand(queryUpdateEquipVisitant, conn);
                    cmdUpdateVisitant->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    cmdUpdateVisitant->Parameters->AddWithValue("@golsA", diffGolsVisitant);
                    cmdUpdateVisitant->Parameters->AddWithValue("@golsC", diffGolsLocal);
                    int vicV = resultatVisitant > resultatLocal ? 1 : 0;
                    int derV = resultatVisitant < resultatLocal ? 1 : 0;
                    int empV = resultatVisitant == resultatLocal ? 1 : 0;
                    int puntsV = (vicV * 3) + (empV * 1);
                    cmdUpdateVisitant->Parameters->AddWithValue("@victories", vicV);
                    cmdUpdateVisitant->Parameters->AddWithValue("@derrotes", derV);
                    cmdUpdateVisitant->Parameters->AddWithValue("@empats", empV);
                    cmdUpdateVisitant->Parameters->AddWithValue("@punts", puntsV);
                    cmdUpdateVisitant->ExecuteNonQuery();

                    if (!String::IsNullOrWhiteSpace(statsJson)) {
                        cli::array<String^>^ lines = statsJson->Split(gcnew cli::array<wchar_t>{'\n'}, StringSplitOptions::RemoveEmptyEntries);
                        if (lines->Length > 1) {
                            for (int i = 1; i < lines->Length; ++i) {
                                cli::array<String^>^ fields = lines[i]->Trim()->Split(';');
                                if (fields->Length >= 7) {
                                    int idJugador = Int32::Parse(fields[0]);
                                    String^ nomJugador = fields[1];
                                    int gols = Int32::Parse(fields[3]);
                                    int assistencies = Int32::Parse(fields[4]);
                                    int targetesGrogues = Int32::Parse(fields[5]);
                                    int targetesVermelles = Int32::Parse(fields[6]);

                                    String^ queryPosicio = "SELECT posicio FROM Jugador WHERE idJugador = @idJugador LIMIT 1";
                                    MySqlCommand^ cmdPosicio = gcnew MySqlCommand(queryPosicio, conn);
                                    cmdPosicio->Parameters->AddWithValue("@idJugador", idJugador);
                                    Object^ posicioObj = cmdPosicio->ExecuteScalar();
                                    String^ posicio = (posicioObj == nullptr || posicioObj == DBNull::Value) ? "" : posicioObj->ToString();

                                    String^ queryUpsertStats =
                                        "INSERT INTO PartitEstadisticaIndividual (idPartit, disciplina, idJugador, nomJugador, posicio, "
                                        "targetesgrogues, targetesvermelles, golsmarcat, asistencies, "
                                        "targetesgroguesobtenides, targetesvermelllesobtenides, dataActualitzacio) "
                                        "VALUES (@idPartit, @disciplina, @idJugador, @nomJugador, @posicio, "
                                        "@targetesGrogues, @targetesVermelles, @gols, @assistencies, "
                                        "@targetesGrogues, @targetesVermelles, NOW()) "
                                        "ON DUPLICATE KEY UPDATE disciplina = VALUES(disciplina), nomJugador = VALUES(nomJugador), posicio = VALUES(posicio), "
                                        "targetesgrogues = VALUES(targetesgrogues), targetesvermelles = VALUES(targetesvermelles), "
                                        "golsmarcat = VALUES(golsmarcat), asistencies = VALUES(asistencies), "
                                        "targetesgroguesobtenides = VALUES(targetesgroguesobtenides), targetesvermelllesobtenides = VALUES(targetesvermelllesobtenides), "
                                        "dataActualitzacio = NOW()";

                                    MySqlCommand^ cmdStats = gcnew MySqlCommand(queryUpsertStats, conn);
                                    cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                                    cmdStats->Parameters->AddWithValue("@disciplina", disciplina);
                                    cmdStats->Parameters->AddWithValue("@idJugador", idJugador);
                                    cmdStats->Parameters->AddWithValue("@nomJugador", nomJugador);
                                    cmdStats->Parameters->AddWithValue("@posicio", posicio);
                                    cmdStats->Parameters->AddWithValue("@targetesGrogues", targetesGrogues);
                                    cmdStats->Parameters->AddWithValue("@targetesVermelles", targetesVermelles);
                                    cmdStats->Parameters->AddWithValue("@gols", gols);
                                    cmdStats->Parameters->AddWithValue("@assistencies", assistencies);
                                    cmdStats->ExecuteNonQuery();

                                    String^ queryUpdateJugador =
                                        "UPDATE Jugador SET "
                                        "partitsJugats = partitsJugats + 1, "
                                        "anotacions = anotacions + @gols, "
                                        "assistencies = assistencies + @assistencies, "
                                        "faltesLleus = faltesLleus + @targetesGrogues, "
                                        "faltesGreus = faltesGreus + @targetesVermelles "
                                        "WHERE idJugador = @idJugador";

                                    MySqlCommand^ cmdUpdateJugador = gcnew MySqlCommand(queryUpdateJugador, conn);
                                    cmdUpdateJugador->Parameters->AddWithValue("@idJugador", idJugador);
                                    cmdUpdateJugador->Parameters->AddWithValue("@gols", gols);
                                    cmdUpdateJugador->Parameters->AddWithValue("@assistencies", assistencies);
                                    cmdUpdateJugador->Parameters->AddWithValue("@targetesGrogues", targetesGrogues);
                                    cmdUpdateJugador->Parameters->AddWithValue("@targetesVermelles", targetesVermelles);
                                    cmdUpdateJugador->ExecuteNonQuery();
                                }
                            }
                        }
                    }
                }
                else if (nouEstat == "Pendent" || nouEstat == "En curs" || nouEstat == "En joc") {
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;
                    if (addGolsLocal != 0 || addGolsVisitant != 0) {
                        String^ queryUpdateGols = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGols, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGols, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsA", addGolsVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsC", addGolsLocal);
                        cmdUpdateGolsV->ExecuteNonQuery();
                    }
                }
                else if (estatAnterior == "Finalitzat" && nouEstat == "Finalitzat" && (resultatLocal != golsLocalAnterior || resultatVisitant != golsVisitantAnterior)) {
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;
                    if (addGolsLocal != 0 || addGolsVisitant != 0) {
                        String^ queryUpdateGols = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGols, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGols, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsA", addGolsVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsC", addGolsLocal);
                        cmdUpdateGolsV->ExecuteNonQuery();
                    }
                    int vicL_old = golsLocalAnterior > golsVisitantAnterior ? 1 : 0;
                    int derL_old = golsLocalAnterior < golsVisitantAnterior ? 1 : 0;
                    int empL_old = golsLocalAnterior == golsVisitantAnterior ? 1 : 0;
                    int puntsL_old = (vicL_old * 3) + (empL_old * 1);
                    int vicV_old = golsVisitantAnterior > golsLocalAnterior ? 1 : 0;
                    int derV_old = golsVisitantAnterior < golsLocalAnterior ? 1 : 0;
                    int empV_old = golsVisitantAnterior == golsLocalAnterior ? 1 : 0;
                    int puntsV_old = (vicV_old * 3) + (empV_old * 1);
                    int vicL_new = resultatLocal > resultatVisitant ? 1 : 0;
                    int derL_new = resultatLocal < resultatVisitant ? 1 : 0;
                    int empL_new = resultatLocal == resultatVisitant ? 1 : 0;
                    int puntsL_new = (vicL_new * 3) + (empL_new * 1);
                    int vicV_new = resultatVisitant > resultatLocal ? 1 : 0;
                    int derV_new = resultatVisitant < resultatLocal ? 1 : 0;
                    int empV_new = resultatVisitant == resultatLocal ? 1 : 0;
                    int puntsV_new = (vicV_new * 3) + (empV_new * 1);

                    String^ qUndoUpdate = "UPDATE Equip SET victories = victories - @vicO + @vicN, derrotes = derrotes - @derO + @derN, empats = empats - @empO + @empN, punts = punts - @ptsO + @ptsN WHERE idEquip = @idEquip";
                    MySqlCommand^ cmdUndoL = gcnew MySqlCommand(qUndoUpdate, conn);
                    cmdUndoL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    cmdUndoL->Parameters->AddWithValue("@vicO", vicL_old); cmdUndoL->Parameters->AddWithValue("@vicN", vicL_new);
                    cmdUndoL->Parameters->AddWithValue("@derO", derL_old); cmdUndoL->Parameters->AddWithValue("@derN", derL_new);
                    cmdUndoL->Parameters->AddWithValue("@empO", empL_old); cmdUndoL->Parameters->AddWithValue("@empN", empL_new);
                    cmdUndoL->Parameters->AddWithValue("@ptsO", puntsL_old); cmdUndoL->Parameters->AddWithValue("@ptsN", puntsL_new);
                    cmdUndoL->ExecuteNonQuery();

                    MySqlCommand^ cmdUndoV = gcnew MySqlCommand(qUndoUpdate, conn);
                    cmdUndoV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    cmdUndoV->Parameters->AddWithValue("@vicO", vicV_old); cmdUndoV->Parameters->AddWithValue("@vicN", vicV_new);
                    cmdUndoV->Parameters->AddWithValue("@derO", derV_old); cmdUndoV->Parameters->AddWithValue("@derN", derV_new);
                    cmdUndoV->Parameters->AddWithValue("@empO", empV_old); cmdUndoV->Parameters->AddWithValue("@empN", empV_new);
                    cmdUndoV->Parameters->AddWithValue("@ptsO", puntsV_old); cmdUndoV->Parameters->AddWithValue("@ptsN", puntsV_new);
                    cmdUndoV->ExecuteNonQuery();
                }

                if (!(nouEstat == "Finalitzat" && estatAnterior != "Finalitzat") && !String::IsNullOrWhiteSpace(statsJson)) {
                    cli::array<String^>^ lines = statsJson->Split(gcnew cli::array<wchar_t>{'\n'}, StringSplitOptions::RemoveEmptyEntries);
                    if (lines->Length > 1) {
                        for (int i = 1; i < lines->Length; ++i) {
                            cli::array<String^>^ fields = lines[i]->Trim()->Split(';');
                            if (fields->Length >= 7) {
                                int idJugador = Int32::Parse(fields[0]);
                                String^ nomJugador = fields[1];
                                int gols = Int32::Parse(fields[3]);
                                int assistencies = Int32::Parse(fields[4]);
                                int targetesGrogues = Int32::Parse(fields[5]);
                                int targetesVermelles = Int32::Parse(fields[6]);

                                int golsAnteriors = 0;
                                int assistenciesAnteriors = 0;
                                int targetesGroguesAnteriors = 0;
                                int targetesVermellesAnteriors = 0;
                                bool estadisticaJaExistia = false;

                                String^ queryStatsAnteriors =
                                    "SELECT golsmarcat, asistencies, targetesgrogues, targetesvermelles "
                                    "FROM PartitEstadisticaIndividual "
                                    "WHERE idPartit = @idPartit AND idJugador = @idJugador LIMIT 1";
                                MySqlCommand^ cmdStatsAnteriors = gcnew MySqlCommand(queryStatsAnteriors, conn);
                                cmdStatsAnteriors->Parameters->AddWithValue("@idPartit", idPartit);
                                cmdStatsAnteriors->Parameters->AddWithValue("@idJugador", idJugador);
                                MySqlDataReader^ readerStatsAnteriors = cmdStatsAnteriors->ExecuteReader();
                                if (readerStatsAnteriors->Read()) {
                                    estadisticaJaExistia = true;
                                    golsAnteriors = readerStatsAnteriors->IsDBNull(readerStatsAnteriors->GetOrdinal("golsmarcat")) ? 0 : Convert::ToInt32(readerStatsAnteriors["golsmarcat"]);
                                    assistenciesAnteriors = readerStatsAnteriors->IsDBNull(readerStatsAnteriors->GetOrdinal("asistencies")) ? 0 : Convert::ToInt32(readerStatsAnteriors["asistencies"]);
                                    targetesGroguesAnteriors = readerStatsAnteriors->IsDBNull(readerStatsAnteriors->GetOrdinal("targetesgrogues")) ? 0 : Convert::ToInt32(readerStatsAnteriors["targetesgrogues"]);
                                    targetesVermellesAnteriors = readerStatsAnteriors->IsDBNull(readerStatsAnteriors->GetOrdinal("targetesvermelles")) ? 0 : Convert::ToInt32(readerStatsAnteriors["targetesvermelles"]);
                                }
                                readerStatsAnteriors->Close();

                                String^ queryPosicio = "SELECT posicio FROM Jugador WHERE idJugador = @idJugador LIMIT 1";
                                MySqlCommand^ cmdPosicio = gcnew MySqlCommand(queryPosicio, conn);
                                cmdPosicio->Parameters->AddWithValue("@idJugador", idJugador);
                                Object^ posicioObj = cmdPosicio->ExecuteScalar();
                                String^ posicio = (posicioObj == nullptr || posicioObj == DBNull::Value) ? "" : posicioObj->ToString();

                                String^ queryUpsertStats =
                                    "INSERT INTO PartitEstadisticaIndividual (idPartit, disciplina, idJugador, nomJugador, posicio, "
                                    "targetesgrogues, targetesvermelles, golsmarcat, asistencies, "
                                    "targetesgroguesobtenides, targetesvermelllesobtenides, dataActualitzacio) "
                                    "VALUES (@idPartit, @disciplina, @idJugador, @nomJugador, @posicio, "
                                    "@targetesGrogues, @targetesVermelles, @gols, @assistencies, "
                                    "@targetesGrogues, @targetesVermelles, NOW()) "
                                    "ON DUPLICATE KEY UPDATE disciplina = VALUES(disciplina), nomJugador = VALUES(nomJugador), posicio = VALUES(posicio), "
                                    "targetesgrogues = VALUES(targetesgrogues), targetesvermelles = VALUES(targetesvermelles), "
                                    "golsmarcat = VALUES(golsmarcat), asistencies = VALUES(asistencies), "
                                    "targetesgroguesobtenides = VALUES(targetesgroguesobtenides), targetesvermelllesobtenides = VALUES(targetesvermelllesobtenides), "
                                    "dataActualitzacio = NOW()";

                                MySqlCommand^ cmdStats = gcnew MySqlCommand(queryUpsertStats, conn);
                                cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                                cmdStats->Parameters->AddWithValue("@disciplina", disciplina);
                                cmdStats->Parameters->AddWithValue("@idJugador", idJugador);
                                cmdStats->Parameters->AddWithValue("@nomJugador", nomJugador);
                                cmdStats->Parameters->AddWithValue("@posicio", posicio);
                                cmdStats->Parameters->AddWithValue("@targetesGrogues", targetesGrogues);
                                cmdStats->Parameters->AddWithValue("@targetesVermelles", targetesVermelles);
                                cmdStats->Parameters->AddWithValue("@gols", gols);
                                cmdStats->Parameters->AddWithValue("@assistencies", assistencies);
                                cmdStats->ExecuteNonQuery();

                                String^ queryUpdateJugador =
                                    "UPDATE Jugador SET "
                                    "partitsJugats = partitsJugats + @partitJugatDelta, "
                                    "anotacions = anotacions + @golsDelta, "
                                    "assistencies = assistencies + @assistenciesDelta, "
                                    "faltesLleus = faltesLleus + @targetesGroguesDelta, "
                                    "faltesGreus = faltesGreus + @targetesVermellesDelta "
                                    "WHERE idJugador = @idJugador";
                                int partitJugatDelta = 0;
                                int golsDelta = 0;
                                int assistenciesDelta = 0;
                                int targetesGroguesDelta = 0;
                                int targetesVermellesDelta = 0;
                                if (nouEstat == "Finalitzat") {
                                    partitJugatDelta = estadisticaJaExistia ? 0 : 1;
                                    golsDelta = gols - golsAnteriors;
                                    assistenciesDelta = assistencies - assistenciesAnteriors;
                                    targetesGroguesDelta = targetesGrogues - targetesGroguesAnteriors;
                                    targetesVermellesDelta = targetesVermelles - targetesVermellesAnteriors;
                                }
                                MySqlCommand^ cmdUpdateJugador = gcnew MySqlCommand(queryUpdateJugador, conn);
                                cmdUpdateJugador->Parameters->AddWithValue("@idJugador", idJugador);
                                cmdUpdateJugador->Parameters->AddWithValue("@partitJugatDelta", partitJugatDelta);
                                cmdUpdateJugador->Parameters->AddWithValue("@golsDelta", golsDelta);
                                cmdUpdateJugador->Parameters->AddWithValue("@assistenciesDelta", assistenciesDelta);
                                cmdUpdateJugador->Parameters->AddWithValue("@targetesGroguesDelta", targetesGroguesDelta);
                                cmdUpdateJugador->Parameters->AddWithValue("@targetesVermellesDelta", targetesVermellesDelta);
                                cmdUpdateJugador->ExecuteNonQuery();
                            }
                        }
                    }
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
