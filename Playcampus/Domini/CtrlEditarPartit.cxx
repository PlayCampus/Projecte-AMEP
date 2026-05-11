#include "pch.h"
#include "CtrlEditarPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {
        CtrlEditarPartit::CtrlEditarPartit() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlEditarPartit::ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin) {
            Playcampus::Dades::PassarellaUsuari^ usuari = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuAdmin);
            if (usuari == nullptr) return false;

            Playcampus::Dades::PassarellaLliga^ passLliga = gcnew Playcampus::Dades::PassarellaLliga(connectionString);

            return passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
        }

        String^ CtrlEditarPartit::ObtenirNomLligaAdmin(String^ correuAdmin) {
            if (String::IsNullOrWhiteSpace(correuAdmin)) {
                return nullptr;
            }

            String^ nomLliga = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT l.nom "
                    "FROM Lliga l "
                    "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                    "WHERE u.correu_electronic = @correuAdmin "
                    "ORDER BY l.nom "
                    "LIMIT 1";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    nomLliga = result->ToString();
                }
            }
            finally {
                conn->Close();
            }

            return nomLliga;
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirPartitsPerLliga(String^ nomLliga, String^ correuAdmin) {
            if (!ValidarAdministradorLliga(nomLliga, correuAdmin)) {
                throw gcnew UnauthorizedAccessException("No tens permisos per editar partits d'aquesta lliga.");
            }

            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
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

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                while (reader->Read()) {
                    Dictionary<String^, String^>^ p = gcnew Dictionary<String^, String^>();
                    p["idPartit"] = reader["idPartit"]->ToString();
                    p["dataHora"] = reader["dataHora"]->ToString();
                    p["estat"] = reader["estat"]->ToString();
                    p["golsLocal"] = reader["golsLocal"]->ToString();
                    p["golsVisitant"] = reader["golsVisitant"]->ToString();
                    p["equipLocal"] = reader["equipLocal"]->ToString();
                    p["equipVisitant"] = reader["equipVisitant"]->ToString();
                    partits->Add(p);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }

            return partits;
        }

        Dictionary<String^, String^>^ CtrlEditarPartit::ObtenirDetallPartit(String^ idPartit, String^ correuAdmin) {
            Dictionary<String^, String^>^ detall = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query =
                    "SELECT p.idPartit, p.estat, p.golsLocal, p.golsVisitant, l.disciplina, u.correu_electronic AS correuAdmin "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                    "INNER JOIN Lliga l ON t.idLliga = l.idLliga "
                    "INNER JOIN Usuari u ON l.idAdministrador = u.identificador "
                    "WHERE p.idPartit = @idPartit LIMIT 1";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                if (!reader->Read()) {
                    reader->Close();
                    throw gcnew Exception("No s'ha trobat el partit seleccionat.");
                }

                String^ correuAdministradorPartit = reader["correuAdmin"]->ToString();
                if (!correuAdministradorPartit->Equals(correuAdmin, StringComparison::OrdinalIgnoreCase)) {
                    reader->Close();
                    throw gcnew UnauthorizedAccessException("No tens permisos per editar aquest partit.");
                }

                detall = gcnew Dictionary<String^, String^>();
                detall["idPartit"] = reader["idPartit"]->ToString();
                detall["estat"] = reader["estat"]->ToString();
                detall["golsLocal"] = reader["golsLocal"]->ToString();
                detall["golsVisitant"] = reader["golsVisitant"]->ToString();
                detall["disciplina"] = reader["disciplina"]->ToString();
                reader->Close();

                detall["stats"] = "";
                    "dataActualitzacio DATETIME NOT NULL)";
                MySqlCommand^ cmdCreate = gcnew MySqlCommand(queryStatsTable, conn);
                cmdCreate->ExecuteNonQuery();

                String^ queryStats = "SELECT estadistiques FROM PartitEstadisticaIndividual WHERE idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdStats = gcnew MySqlCommand(queryStats, conn);
                cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                Object^ stats = cmdStats->ExecuteScalar();
                detall["stats"] = (stats == nullptr || stats == DBNull::Value) ? "" : stats->ToString();
                    "dataActualitzacio DATETIME NOT NULL)";
                MySqlCommand^ cmdCreate = gcnew MySqlCommand(queryStatsTable, conn);
                cmdCreate->ExecuteNonQuery();

                String^ queryStats = "SELECT estadistiques FROM PartitEstadisticaIndividual WHERE idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdStats = gcnew MySqlCommand(queryStats, conn);
                cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                Object^ stats = cmdStats->ExecuteScalar();
                detall["stats"] = (stats == nullptr || stats == DBNull::Value) ? "" : stats->ToString();
                    "dataActualitzacio DATETIME NOT NULL)";
                MySqlCommand^ cmdCreate = gcnew MySqlCommand(queryStatsTable, conn);
                cmdCreate->ExecuteNonQuery();

                String^ queryStats = "SELECT estadistiques FROM PartitEstadisticaIndividual WHERE idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdStats = gcnew MySqlCommand(queryStats, conn);
                cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                Object^ stats = cmdStats->ExecuteScalar();
                detall["stats"] = (stats == nullptr || stats == DBNull::Value) ? "" : stats->ToString();
            }
            finally {
                conn->Close();
            }

            return detall;
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryPartit =
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

                MySqlCommand^ cmdPartit = gcnew MySqlCommand(queryPartit, conn);
                cmdPartit->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataReader^ readerPartit = cmdPartit->ExecuteReader();

                if (!readerPartit->Read()) {
                    readerPartit->Close();
                    throw gcnew Exception("No s'ha trobat el partit seleccionat.");
                }

                String^ correuAdministradorPartit = readerPartit["correuAdmin"]->ToString();
                if (!correuAdministradorPartit->Equals(correuAdmin, StringComparison::OrdinalIgnoreCase)) {
                    readerPartit->Close();
                    throw gcnew UnauthorizedAccessException("No tens permisos per editar aquest partit.");
                }

                String^ idEquipLocal = readerPartit["idEquipLocal"]->ToString();
                String^ idEquipVisitant = readerPartit["idEquipVisitant"]->ToString();
                String^ nomEquipLocal = readerPartit["nomEquipLocal"]->ToString();
                String^ nomEquipVisitant = readerPartit["nomEquipVisitant"]->ToString();
                readerPartit->Close();

                String^ queryJugadors =
                    "SELECT u.nom AS nomJugador, j.idEquip, j.idJugador "
                    "FROM Jugador j "
                    "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                    "INNER JOIN ConvocatoriaPartit cp ON j.idJugador = cp.idJugador "
                    "WHERE cp.idPartit = @idPartit AND cp.convocat = 1 "
                    "ORDER BY CASE WHEN j.idEquip = @idLocal THEN 0 ELSE 1 END, u.nom";

                MySqlCommand^ cmdJugadors = gcnew MySqlCommand(queryJugadors, conn);
                cmdJugadors->Parameters->AddWithValue("@idPartit", idPartit);
                cmdJugadors->Parameters->AddWithValue("@idLocal", idEquipLocal);
                MySqlDataReader^ readerJugadors = cmdJugadors->ExecuteReader();

                while (readerJugadors->Read()) {
                    String^ idEquip = readerJugadors["idEquip"]->ToString();

                    Dictionary<String^, String^>^ j = gcnew Dictionary<String^, String^>();
                    j["idJugador"] = readerJugadors["idJugador"]->ToString();
                    j["nomJugador"] = readerJugadors["nomJugador"]->ToString();
                    j["equip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? "Local" : "Visitant";
                    j["nomEquip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? nomEquipLocal : nomEquipVisitant;
                    jugadors->Add(j);
                }
                readerJugadors->Close();
            }
            finally {
                conn->Close();
            }

            return jugadors;
        }

        void CtrlEditarPartit::ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit) {
            Dictionary<String^, String^>^ detall = ObtenirDetallPartit(idPartit, correuAdmin);
            String^ disciplina = detall["disciplina"];
            String^ estatAnterior = detall["estat"];

            int golsLocalAnterior = 0;
            int golsVisitantAnterior = 0;
            if (detall->ContainsKey("golsLocal") && !String::IsNullOrEmpty(detall["golsLocal"])) {
                golsLocalAnterior = Int32::Parse(detall["golsLocal"]);
            }
            if (detall->ContainsKey("golsVisitant") && !String::IsNullOrEmpty(detall["golsVisitant"])) {
                golsVisitantAnterior = Int32::Parse(detall["golsVisitant"]);
            }

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                // Obtenir idEquipLocal i idEquipVisitant per actualitzar stats de Equip
                String^ queryEquips = "SELECT idEquipLocal, idEquipVisitant FROM Partit WHERE idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdEquips = gcnew MySqlCommand(queryEquips, conn);
                cmdEquips->Parameters->AddWithValue("@idPartit", idPartit);
                // estadístiques individuals es guarden per jugador en format normalitzat
                MySqlCommand^ cmdCreate = gcnew MySqlCommand(queryStatsTable, conn);
                cmdCreate->ExecuteNonQuery();

                String^ queryUpsertStats =
                    "INSERT INTO PartitEstadisticaIndividual (idPartit, disciplina, estadistiques, dataActualitzacio) "
                    "VALUES (@idPartit, @disciplina, @estadistiques, NOW()) "
                    "ON DUPLICATE KEY UPDATE disciplina = VALUES(disciplina), estadistiques = VALUES(estadistiques), dataActualitzacio = NOW()";
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

                String^ queryStatsTable =
                    "CREATE TABLE IF NOT EXISTS PartitEstadisticaIndividual ("
                    "idPartit VARCHAR(64) NOT NULL PRIMARY KEY, "
                    "disciplina VARCHAR(30) NOT NULL, "
                    "estadistiques LONGTEXT NULL, "
                    "dataActualitzacio DATETIME NOT NULL)";
                MySqlCommand^ cmdCreate = gcnew MySqlCommand(queryStatsTable, conn);
                cmdCreate->ExecuteNonQuery();

                String^ queryUpsertStats =
                    "INSERT INTO PartitEstadisticaIndividual (idPartit, disciplina, estadistiques, dataActualitzacio) "
                    "VALUES (@idPartit, @disciplina, @estadistiques, NOW()) "
                    "ON DUPLICATE KEY UPDATE disciplina = VALUES(disciplina), estadistiques = VALUES(estadistiques), dataActualitzacio = NOW()";

                // Actualitzar Estadístiques Equip (només si l'estat és Finalitzat)
                if (nouEstat == "Finalitzat" && estatAnterior != "Finalitzat" && idEquipLocal != nullptr && idEquipVisitant != nullptr) {

                    int diffGolsLocal = resultatLocal - golsLocalAnterior;
                    int diffGolsVisitant = resultatVisitant - golsVisitantAnterior;

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

                    // Actualitzar estadístiques individuals dels jugadors segons el nou esquema
                    if (!String::IsNullOrWhiteSpace(statsJson)) {
                        cli::array<String^>^ lines = statsJson->Split(gcnew cli::array<wchar_t>{'\n'}, StringSplitOptions::RemoveEmptyEntries);
                        if (lines->Length > 1) { // Header + data
                            for (int i = 1; i < lines->Length; ++i) {
                                cli::array<String^>^ fields = lines[i]->Trim()->Split(';');
                                if (fields->Length >= 7) { // idJugador;NomJugador;equip;gols;assistencies;targetesGrogues;targetesVermelles
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
                } else if (nouEstat == "Pendent" || nouEstat == "En curs" || nouEstat == "En joc") {
                    // Update per canvis de gols mentres el partit encara NO s'ha finalitzat i s'afegeixen gols
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;

                    if(addGolsLocal != 0 || addGolsVisitant != 0) {
                        String^ queryUpdateGolsLocal = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGolsLocal, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        String^ queryUpdateGolsVisitant = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGolsVisitant, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsA", addGolsVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsC", addGolsLocal);
                        cmdUpdateGolsV->ExecuteNonQuery();
                    }
                } else if (estatAnterior == "Finalitzat" && nouEstat == "Finalitzat" && (resultatLocal != golsLocalAnterior || resultatVisitant != golsVisitantAnterior)) {
                    // Update per canvis de gols mentres el partit s'ha finalitzat prèviament. Aquí a part dels gols també s'han de canviar els partits
                    // ja que l'acumulació de gols general ja es va fer.

                    // Afegim gols només la diferència
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;

                    if(addGolsLocal != 0 || addGolsVisitant != 0) {
                        String^ queryUpdateGolsLocal = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGolsLocal, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        String^ queryUpdateGolsVisitant = "UPDATE Equip SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGolsVisitant, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsA", addGolsVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsC", addGolsLocal);
                        cmdUpdateGolsV->ExecuteNonQuery();
                    }
                        // Undo previous finish and re-do with new results

                        // Undo old results
                        int vicL_old = golsLocalAnterior > golsVisitantAnterior ? 1 : 0;
                        int derL_old = golsLocalAnterior < golsVisitantAnterior ? 1 : 0;
                        int empL_old = golsLocalAnterior == golsVisitantAnterior ? 1 : 0;
                        int puntsL_old = (vicL_old * 3) + (empL_old * 1);

                        int vicV_old = golsVisitantAnterior > golsLocalAnterior ? 1 : 0;
                        int derV_old = golsVisitantAnterior < golsLocalAnterior ? 1 : 0;
                        int empV_old = golsVisitantAnterior == golsLocalAnterior ? 1 : 0;
                        int puntsV_old = (vicV_old * 3) + (empV_old * 1);

                        // Calculate new results
                        int vicL_new = resultatLocal > resultatVisitant ? 1 : 0;
                        int derL_new = resultatLocal < resultatVisitant ? 1 : 0;
                        int empL_new = resultatLocal == resultatVisitant ? 1 : 0;
                        int puntsL_new = (vicL_new * 3) + (empL_new * 1);

                        int vicV_new = resultatVisitant > resultatLocal ? 1 : 0;
                        int derV_new = resultatVisitant < resultatLocal ? 1 : 0;
                        int empV_new = resultatVisitant == resultatLocal ? 1 : 0;
                        int puntsV_new = (vicV_new * 3) + (empV_new * 1);

                        // Update local team
                        String^ qUndoUpdateL = "UPDATE Equip SET victories = victories - @vicO + @vicN, derrotes = derrotes - @derO + @derN, empats = empats - @empO + @empN, punts = punts - @ptsO + @ptsN WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUndoL = gcnew MySqlCommand(qUndoUpdateL, conn);
                        cmdUndoL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUndoL->Parameters->AddWithValue("@vicO", vicL_old); cmdUndoL->Parameters->AddWithValue("@vicN", vicL_new);
                        cmdUndoL->Parameters->AddWithValue("@derO", derL_old); cmdUndoL->Parameters->AddWithValue("@derN", derL_new);
                        cmdUndoL->Parameters->AddWithValue("@empO", empL_old); cmdUndoL->Parameters->AddWithValue("@empN", empL_new);
                        cmdUndoL->Parameters->AddWithValue("@ptsO", puntsL_old); cmdUndoL->Parameters->AddWithValue("@ptsN", puntsL_new);
                        cmdUndoL->ExecuteNonQuery();

                        // Update visitant team
                        String^ qUndoUpdateV = "UPDATE Equip SET victories = victories - @vicO + @vicN, derrotes = derrotes - @derO + @derN, empats = empats - @empO + @empN, punts = punts - @ptsO + @ptsN WHERE idEquip = @idEquip";
                        MySqlCommand^ cmdUndoV = gcnew MySqlCommand(qUndoUpdateV, conn);
                        cmdUndoV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUndoV->Parameters->AddWithValue("@vicO", vicV_old); cmdUndoV->Parameters->AddWithValue("@vicN", vicV_new);
                        cmdUndoV->Parameters->AddWithValue("@derO", derV_old); cmdUndoV->Parameters->AddWithValue("@derN", derV_new);
                        cmdUndoV->Parameters->AddWithValue("@empO", empV_old); cmdUndoV->Parameters->AddWithValue("@empN", empV_new);
                        cmdUndoV->Parameters->AddWithValue("@ptsO", puntsV_old); cmdUndoV->Parameters->AddWithValue("@ptsN", puntsV_new);
                        cmdUndoV->ExecuteNonQuery();
                    }
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }
    }
}
