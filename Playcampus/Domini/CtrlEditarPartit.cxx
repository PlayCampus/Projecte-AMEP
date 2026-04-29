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
                    "ORDER BY CASE WHEN l.estat = 'en_curs' THEN 0 ELSE 1 END, l.nom "
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

                String^ queryStatsTable =
                    "CREATE TABLE IF NOT EXISTS PartitEstadisticaIndividual ("
                    "idPartit VARCHAR(64) NOT NULL PRIMARY KEY, "
                    "disciplina VARCHAR(30) NOT NULL, "
                    "estadistiques LONGTEXT NULL, "
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

                String^ queryCols =
                    "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS "
                    "WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Jugador'";
                MySqlCommand^ cmdCols = gcnew MySqlCommand(queryCols, conn);
                MySqlDataReader^ readerCols = cmdCols->ExecuteReader();

                String^ colNom = nullptr;
                String^ colEquip = nullptr;
                while (readerCols->Read()) {
                    String^ col = readerCols["COLUMN_NAME"]->ToString();
                    String^ colLower = col->ToLowerInvariant();

                    if (colNom == nullptr && (colLower == "nom" || colLower == "nomjugador" || colLower == "nom_jugador")) {
                        colNom = col;
                    }
                    if (colEquip == nullptr && (colLower == "idequip" || colLower == "id_equip")) {
                        colEquip = col;
                    }
                }
                readerCols->Close();

                if (String::IsNullOrEmpty(colNom) || String::IsNullOrEmpty(colEquip)) {
                    return jugadors;
                }

                String^ queryJugadors =
                    "SELECT " + colNom + " AS nomJugador, " + colEquip + " AS idEquip "
                    "FROM Jugador "
                    "WHERE " + colEquip + " IN (@idLocal, @idVisit) "
                    "ORDER BY CASE WHEN " + colEquip + " = @idLocal THEN 0 ELSE 1 END, " + colNom;

                MySqlCommand^ cmdJugadors = gcnew MySqlCommand(queryJugadors, conn);
                cmdJugadors->Parameters->AddWithValue("@idLocal", idEquipLocal);
                cmdJugadors->Parameters->AddWithValue("@idVisit", idEquipVisitant);
                MySqlDataReader^ readerJugadors = cmdJugadors->ExecuteReader();

                while (readerJugadors->Read()) {
                    String^ idEquip = readerJugadors["idEquip"]->ToString();

                    Dictionary<String^, String^>^ j = gcnew Dictionary<String^, String^>();
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

            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

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

                MySqlCommand^ cmdStats = gcnew MySqlCommand(queryUpsertStats, conn);
                cmdStats->Parameters->AddWithValue("@idPartit", idPartit);
                cmdStats->Parameters->AddWithValue("@disciplina", disciplina);
                cmdStats->Parameters->AddWithValue("@estadistiques", String::IsNullOrWhiteSpace(statsJson) ? "" : statsJson);
                cmdStats->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }
    }
}
