#include "pch.h"
#include "CercadoraPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
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
                // Hacemos JOIN con Jornada para filtrar por temporada, y con Equip para sacar los nombres. Filtramos por estado 'Finalitzat'
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


        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsCapita(String^ correuCapita) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
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
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuCapita);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["id_partit"] = reader["idPartit"]->ToString();
                    d["equip_local"] = reader["local"]->ToString();
                    d["equip_visitant"] = reader["visitant"]->ToString();
                    d["data"] = reader["dataHora"]->ToString();
                    d["nomMostrar"] = d["equip_local"] + " vs " + d["equip_visitant"];
                    partits->Add(d);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsDeLEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idPartit, dataHora FROM Partit WHERE idEquipLocal = @id OR idEquipVisitant = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["idPartit"] = reader["idPartit"]->ToString();
                    d["dataHora"] = reader["dataHora"]->ToString();
                    partits->Add(d);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT j.idJugador, u.nom, j.posicio, "
                    "cp.convocat AS convocat, cp.confirmat AS confirmat "
                    "FROM Jugador j "
                    "JOIN Usuari u ON j.idJugador = u.identificador "
                    "LEFT JOIN ConvocatoriaPartit cp ON j.idJugador = cp.idJugador AND cp.idPartit = @idPartit "
                    "WHERE j.idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ d = gcnew Dictionary<String^, String^>();
                    d["id_jugador"] = reader["idJugador"]->ToString();
                    d["nom"] = reader["nom"]->ToString();
                    d["posicio"] = reader["posicio"]->ToString();

                    if (reader["convocat"] == DBNull::Value) {
                        d["estat_convocatoria"] = "Sense establir";
                    }
                    else if (reader["convocat"]->ToString() == "1" || reader["convocat"]->ToString() == "True") {
                        d["estat_convocatoria"] = "Convocat";
                    }
                    else {
                        d["estat_convocatoria"] = "No Convocat";
                    }

                    if (reader["confirmat"] == DBNull::Value) {
                        d["confirmacio"] = "Pendent";
                    }
                    else if (reader["confirmat"]->ToString() == "1" || reader["confirmat"]->ToString() == "True") {
                        d["confirmacio"] = "Confirmat";
                    }
                    else {
                        d["confirmacio"] = "D'acord";
                    }
                    jugadors->Add(d);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return jugadors;
        }

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirAvisPendent(String^ correuJugador) {
            Dictionary<String^, String^>^ avis = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT cp.idPartit, cp.convocat, p.dataHora, el.nom AS local, ev.nom AS visitant "
                    "FROM ConvocatoriaPartit cp "
                    "JOIN Partit p ON cp.idPartit = p.idPartit "
                    "JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "JOIN Jugador j ON cp.idJugador = j.idJugador "
                    "JOIN Usuari u ON j.idJugador = u.identificador "
                    "WHERE u.correu_electronic = @correu AND cp.convocat IS NOT NULL AND cp.confirmat IS NULL LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuJugador);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    avis = gcnew Dictionary<String^, String^>();
                    avis["idPartit"] = reader["idPartit"]->ToString();
                    String^ estatConvocat = reader["convocat"]->ToString();
                    if (estatConvocat == "1" || estatConvocat == "True") {
                        avis["tipus"] = "convocat";
                        avis["missatge"] = "Has estat convocat pel partit:\n" + reader["local"]->ToString() + " vs " + reader["visitant"]->ToString() + "\n(" + reader["dataHora"]->ToString() + ")";
                    }
                    else {
                        avis["tipus"] = "no_convocat";
                        avis["missatge"] = "No has estat convocat pel partit:\n" + reader["local"]->ToString() + " vs " + reader["visitant"]->ToString() + "\n(" + reader["dataHora"]->ToString() + ")";
                    }
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return avis;
        }

        bool CercadoraPartit::PartitDisponiblePerEquip(String^ idPartit, String^ idEquip) {
            bool disponible = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT COUNT(*) FROM Partit "
                    "WHERE idPartit = @idPartit "
                    "AND (idEquipLocal = @idEquip OR idEquipVisitant = @idEquip) "
                    "AND (estat IS NULL OR LOWER(estat) <> 'finalitzat')";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                disponible = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return disponible;
        }

        bool CercadoraPartit::AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = @idPartit AND idJugador = @idJugador";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                existeix = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return existeix;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsDisponiblesPerEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
                    "el.nom AS equipLocal, ev.nom AS equipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE (p.idEquipLocal = @idEquip OR p.idEquipVisitant = @idEquip) "
                    "AND (p.estat IS NULL OR LOWER(p.estat) <> 'finalitzat') "
                    "ORDER BY p.dataHora ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                    partit["idPartit"] = reader["idPartit"]->ToString();
                    partit["dataHora"] = reader["dataHora"]->ToString();
                    partit["ubicacio"] = reader->IsDBNull(reader->GetOrdinal("ubicacio")) ? "" : reader["ubicacio"]->ToString();
                    partit["estat"] = reader->IsDBNull(reader->GetOrdinal("estat")) ? "" : reader["estat"]->ToString();
                    partit["equipLocal"] = reader["equipLocal"]->ToString();
                    partit["equipVisitant"] = reader["equipVisitant"]->ToString();
                    partits->Add(partit);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return partits;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsPerLliga(String^ nomLliga) {
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

        Dictionary<String^, String^>^ CercadoraPartit::ObtenirDetallPartit(String^ idPartit, String^ correuAdmin) {
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
            }
            finally {
                conn->Close();
            }
            return detall;
        }

        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
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
                    "SELECT u.identificador AS idJugador, u.nom AS nomJugador, j.idEquip, "
                    "IFNULL(pei.targetesgrogues, 0) AS estadistica1, "
                    "IFNULL(pei.targetesvermelles, 0) AS estadistica2, "
                    "IFNULL(pei.golsmarcat, 0) AS estadistica3, "
                    "IFNULL(pei.asistencies, 0) AS estadistica4 "
                    "FROM Jugador j "
                    "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                    "LEFT JOIN PartitEstadisticaIndividual pei ON pei.idJugador = j.idJugador AND pei.idPartit = @idPartit "
                    "WHERE j.idEquip IN (@idEquipLocal, @idEquipVisitant) "
                    "ORDER BY j.idEquip, u.nom";
                MySqlCommand^ cmdJugadors = gcnew MySqlCommand(queryJugadors, conn);
                cmdJugadors->Parameters->AddWithValue("@idPartit", idPartit);
                cmdJugadors->Parameters->AddWithValue("@idEquipLocal", idEquipLocal);
                cmdJugadors->Parameters->AddWithValue("@idEquipVisitant", idEquipVisitant);
                MySqlDataReader^ readerJugadors = cmdJugadors->ExecuteReader();
                while (readerJugadors->Read()) {
                    String^ idEquip = readerJugadors["idEquip"]->ToString();
                    Dictionary<String^, String^>^ j = gcnew Dictionary<String^, String^>();
                    j["idJugador"] = readerJugadors["idJugador"]->ToString();
                    j["nomJugador"] = readerJugadors["nomJugador"]->ToString();
                    j["equip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? "Local" : "Visitant";
                    j["nomEquip"] = idEquip->Equals(idEquipLocal, StringComparison::OrdinalIgnoreCase) ? nomEquipLocal : nomEquipVisitant;
                    j["estadistica1"] = readerJugadors["estadistica1"]->ToString();
                    j["estadistica2"] = readerJugadors["estadistica2"]->ToString();
                    j["estadistica3"] = readerJugadors["estadistica3"]->ToString();
                    j["estadistica4"] = readerJugadors["estadistica4"]->ToString();
                    jugadors->Add(j);
                }
                readerJugadors->Close();
            }
            finally {
                conn->Close();
            }
            return jugadors;
        }

        DataTable^ CercadoraPartit::ObtenirProgramacioPartits() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
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
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        
        DataTable^ CercadoraPartit::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryDisciplina = "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga";
                MySqlCommand^ cmdDisciplina = gcnew MySqlCommand(queryDisciplina, conn);
                cmdDisciplina->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ disciplinaResult = cmdDisciplina->ExecuteScalar();
                String^ disciplina = (disciplinaResult == nullptr || disciplinaResult == DBNull::Value) ? nullptr : disciplinaResult->ToString();
                bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
                String^ labelLocal = esFutbol ? "Gols locals" : "Punts locals";
                String^ labelVisitant = esFutbol ? "Gols visitant" : "Punts visitant";

                String^ query =
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
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        
        DataTable^ CercadoraPartit::ObtenirUltimsResultats(String^ idLliga, String^ idTemporada, int limit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryDisciplina = "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga";
                MySqlCommand^ cmdDisciplina = gcnew MySqlCommand(queryDisciplina, conn);
                cmdDisciplina->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ disciplinaResult = cmdDisciplina->ExecuteScalar();
                String^ disciplina = (disciplinaResult == nullptr || disciplinaResult == DBNull::Value) ? nullptr : disciplinaResult->ToString();
                bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
                String^ labelLocal = esFutbol ? "Gols locals" : "Punts locals";
                String^ labelVisitant = esFutbol ? "Gols visitant" : "Punts visitant";

                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                    "COALESCE(el.nom, '(TBD)') AS Local, COALESCE(ev.nom, '(TBD)') AS Visitant, "
                    "p.golsLocal AS `" + labelLocal + "`, p.golsVisitant AS `" + labelVisitant + "` "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                    "LEFT JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "LEFT JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE t.idLliga = @idLliga AND p.estat = 'Finalitzat' "
                    "ORDER BY p.dataHora DESC "
                    "LIMIT " + limit.ToString();

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraPartit::ObtenirProximsPartits(String^ idLliga, String^ idTemporada, int limit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                    "COALESCE(el.nom, '(TBD)') AS Local, COALESCE(ev.nom, '(TBD)') AS Visitant, "
                    "p.ubicacio AS Ubicacio, p.estat AS Estat "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                    "LEFT JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "LEFT JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE t.idLliga = @idLliga AND p.estat = 'Pendent' "
                    "ORDER BY p.dataHora ASC "
                    "LIMIT " + limit.ToString();

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraPartit::ObtenirDetallsPartitEstadistiques(String^ idPartit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant, "
                    "p.golsLocal AS GolsLocals, p.golsVisitant AS GolsVisitants "
                    "FROM Partit p "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE p.idPartit = @idPartit";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraPartit::ObtenirEstadistiquesPartit(String^ idPartit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
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
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

    }
}
