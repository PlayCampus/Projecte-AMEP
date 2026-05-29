#include "pch.h"
#include "PassarellaPartit.hxx"
#include "CercadoraPartit.hxx"
#include "../Domini/EtiquetesEditarPartit.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        PassarellaPartit::PassarellaPartit(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaPartit::PassarellaPartit(String^ connStr, String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada, String^ idEquipLocal, String^ idEquipVisitant) {
            connectionString = connStr;
            this->idPartit = idPartit;
            this->dataHora = dataHora;
            this->ubicacio = ubicacio;
            this->estat = estat;
            this->golsLocal = golsLocal;
            this->golsVisitant = golsVisitant;
            this->idJornada = idJornada;
            this->idEquipLocal = idEquipLocal;
            this->idEquipVisitant = idEquipVisitant;
        }

        String^ PassarellaPartit::GetIdPartit() { return idPartit; }
        DateTime PassarellaPartit::GetDataHora() { return dataHora; }
        String^ PassarellaPartit::GetUbicacio() { return ubicacio; }
        String^ PassarellaPartit::GetEstat() { return estat; }
        int PassarellaPartit::GetGolsLocal() { return golsLocal; }
        int PassarellaPartit::GetGolsVisitant() { return golsVisitant; }
        String^ PassarellaPartit::GetIdJornada() { return idJornada; }
        String^ PassarellaPartit::GetIdEquipLocal() { return idEquipLocal; }
        String^ PassarellaPartit::GetIdEquipVisitant() { return idEquipVisitant; }

        void PassarellaPartit::InsereixPartit() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idPartit)) {
                    idPartit = Guid::NewGuid().ToString();
                }

                // RIT33: equip local i visitant han de ser diferents
                if (!String::IsNullOrEmpty(idEquipLocal) && idEquipLocal == idEquipVisitant) {
                    throw gcnew ArgumentException("L'equip local i el visitant han de ser diferents.");
                }

                // RIT34: la dataHora ha d'estar dins l'interval de la jornada
                {
                    String^ qJornada = "SELECT dataInici, dataFi FROM Jornada WHERE idJornada = @idJornada LIMIT 1";
                    MySqlCommand^ cmdJornada = gcnew MySqlCommand(qJornada, conn);
                    cmdJornada->Parameters->AddWithValue("@idJornada", idJornada);
                    MySqlDataReader^ rJornada = cmdJornada->ExecuteReader();
                    DateTime dataInici;
                    DateTime dataFi;
                    bool trobada = false;
                    if (rJornada->Read()) {
                        trobada = true;
                        dataInici = Convert::ToDateTime(rJornada["dataInici"]);
                        dataFi = Convert::ToDateTime(rJornada["dataFi"]);
                    }
                    rJornada->Close();
                    if (!trobada) {
                        throw gcnew Exception("La jornada no existeix o no és vàlida.");
                    }
                    if (dataHora < dataInici || dataHora > dataFi) {
                        throw gcnew ArgumentException("La data i hora del partit ha d'estar dins de les dates de la jornada.");
                    }
                }

                // RIT35: els dos equips han de pertànyer a la temporada de la jornada
                {
                    String^ qEquipTemporada =
                        "SELECT COUNT(*) "
                        "FROM Jornada j "
                        "INNER JOIN EquipTemporada et ON et.idTemporada = j.idTemporada "
                        "WHERE j.idJornada = @idJornada AND et.idEquip = @idEquip";
                    MySqlCommand^ cmdLocal = gcnew MySqlCommand(qEquipTemporada, conn);
                    cmdLocal->Parameters->AddWithValue("@idJornada", idJornada);
                    cmdLocal->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    int okLocal = Convert::ToInt32(cmdLocal->ExecuteScalar());
                    if (okLocal <= 0) {
                        throw gcnew ArgumentException("L'equip local no participa a la temporada d'aquesta jornada.");
                    }

                    MySqlCommand^ cmdVisitant = gcnew MySqlCommand(qEquipTemporada, conn);
                    cmdVisitant->Parameters->AddWithValue("@idJornada", idJornada);
                    cmdVisitant->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    int okVisitant = Convert::ToInt32(cmdVisitant->ExecuteScalar());
                    if (okVisitant <= 0) {
                        throw gcnew ArgumentException("L'equip visitant no participa a la temporada d'aquesta jornada.");
                    }
                }

                // RIT36: un equip no pot jugar dos partits diferents a la mateixa dataHora
                {
                    String^ qSolapament =
                        "SELECT COUNT(*) FROM Partit "
                        "WHERE dataHora = @dataHora AND "
                        "(idEquipLocal = @eLocal OR idEquipVisitant = @eLocal OR idEquipLocal = @eVisitant OR idEquipVisitant = @eVisitant)";
                    MySqlCommand^ cmdSolapament = gcnew MySqlCommand(qSolapament, conn);
                    cmdSolapament->Parameters->AddWithValue("@dataHora", dataHora);
                    cmdSolapament->Parameters->AddWithValue("@eLocal", idEquipLocal);
                    cmdSolapament->Parameters->AddWithValue("@eVisitant", idEquipVisitant);
                    int countSolapament = Convert::ToInt32(cmdSolapament->ExecuteScalar());
                    if (countSolapament > 0) {
                        throw gcnew ArgumentException("Un dels equips ja té un partit programat a la mateixa data i hora.");
                    }
                }

                // RIT37: dins d'una mateixa jornada no es pot repetir el mateix enfrontament
                {
                    String^ qEnfrontament =
                        "SELECT COUNT(*) FROM Partit "
                        "WHERE idJornada = @idJornada AND "
                        "((idEquipLocal = @eLocal AND idEquipVisitant = @eVisitant) OR (idEquipLocal = @eVisitant AND idEquipVisitant = @eLocal))";
                    MySqlCommand^ cmdEnfrontament = gcnew MySqlCommand(qEnfrontament, conn);
                    cmdEnfrontament->Parameters->AddWithValue("@idJornada", idJornada);
                    cmdEnfrontament->Parameters->AddWithValue("@eLocal", idEquipLocal);
                    cmdEnfrontament->Parameters->AddWithValue("@eVisitant", idEquipVisitant);
                    int countEnfrontament = Convert::ToInt32(cmdEnfrontament->ExecuteScalar());
                    if (countEnfrontament > 0) {
                        throw gcnew ArgumentException("Dins d'aquesta jornada ja existeix un partit entre aquests dos equips.");
                    }
                }

                String^ query = "INSERT INTO Partit (idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada, idEquipLocal, idEquipVisitant) VALUES (@idPartit, @dataHora, @ubicacio, @estat, @golsLocal, @golsVisitant, @idJornada, @idEquipLocal, @idEquipVisitant)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@dataHora", dataHora);
                cmd->Parameters->AddWithValue("@ubicacio", ubicacio);
                cmd->Parameters->AddWithValue("@estat", estat);
                cmd->Parameters->AddWithValue("@golsLocal", golsLocal);
                cmd->Parameters->AddWithValue("@golsVisitant", golsVisitant);
                cmd->Parameters->AddWithValue("@idJornada", idJornada);
                cmd->Parameters->AddWithValue("@idEquipLocal", idEquipLocal);
                cmd->Parameters->AddWithValue("@idEquipVisitant", idEquipVisitant);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
        void PassarellaPartit::EsborrarPartit(String^ idPartit) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ idEquipLocal = nullptr;
                String^ idEquipVisitant = nullptr;
                String^ idTemporadaPartit = nullptr;
                String^ estatPartit = nullptr;
                int golsLocal = 0;
                int golsVisitant = 0;
                bool partitTrobat = false;

                String^ queryDetallPartit =
                    "SELECT P.idEquipLocal, P.idEquipVisitant, P.estat, P.golsLocal, P.golsVisitant, J.idTemporada "
                    "FROM Partit P "
                    "INNER JOIN Jornada J ON J.idJornada = P.idJornada "
                    "WHERE P.idPartit = @idPartit "
                    "LIMIT 1";
                MySqlCommand^ cmdDetallPartit = gcnew MySqlCommand(queryDetallPartit, conn);
                cmdDetallPartit->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataReader^ readerDetallPartit = cmdDetallPartit->ExecuteReader();
                if (readerDetallPartit->Read()) {
                    partitTrobat = true;
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("idEquipLocal"))) {
                        idEquipLocal = readerDetallPartit["idEquipLocal"]->ToString();
                    }
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("idEquipVisitant"))) {
                        idEquipVisitant = readerDetallPartit["idEquipVisitant"]->ToString();
                    }
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("estat"))) {
                        estatPartit = readerDetallPartit["estat"]->ToString();
                    }
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("idTemporada"))) {
                        idTemporadaPartit = readerDetallPartit["idTemporada"]->ToString();
                    }
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("golsLocal"))) {
                        golsLocal = Convert::ToInt32(readerDetallPartit["golsLocal"]);
                    }
                    if (!readerDetallPartit->IsDBNull(readerDetallPartit->GetOrdinal("golsVisitant"))) {
                        golsVisitant = Convert::ToInt32(readerDetallPartit["golsVisitant"]);
                    }
                }
                readerDetallPartit->Close();

                if (!partitTrobat) {
                    throw gcnew Exception("No s'ha trobat el partit que es vol esborrar.");
                }

                bool partitFinalitzat = false;
                if (estatPartit != nullptr) {
                    partitFinalitzat = estatPartit->Equals("Finalitzat", StringComparison::OrdinalIgnoreCase);
                }

                if (idEquipLocal != nullptr && idEquipVisitant != nullptr && idTemporadaPartit != nullptr) {
                    int victoriaLocal = golsLocal > golsVisitant ? 1 : 0;
                    int derrotaLocal = golsLocal < golsVisitant ? 1 : 0;
                    int empatLocal = golsLocal == golsVisitant ? 1 : 0;
                    int puntsLocal = (victoriaLocal * 3) + empatLocal;

                    int victoriaVisitant = golsVisitant > golsLocal ? 1 : 0;
                    int derrotaVisitant = golsVisitant < golsLocal ? 1 : 0;
                    int empatVisitant = golsVisitant == golsLocal ? 1 : 0;
                    int puntsVisitant = (victoriaVisitant * 3) + empatVisitant;

                    String^ queryDesferEquipFinalitzat =
                        "UPDATE EquipTemporada SET "
                        "partitsJugats = GREATEST(partitsJugats - 1, 0), "
                        "golsAFavor = GREATEST(golsAFavor - @golsA, 0), "
                        "golsEnContra = GREATEST(golsEnContra - @golsC, 0), "
                        "diferenciaGols = golsAFavor - golsEnContra, "
                        "victories = GREATEST(victories - @victories, 0), "
                        "derrotes = GREATEST(derrotes - @derrotes, 0), "
                        "empats = GREATEST(empats - @empats, 0), "
                        "punts = GREATEST(punts - @punts, 0) "
                        "WHERE idEquip = @idEquip AND idTemporada = @idTemporada";

                    String^ queryDesferEquipNoFinalitzat =
                        "UPDATE EquipTemporada SET "
                        "golsAFavor = GREATEST(golsAFavor - @golsA, 0), "
                        "golsEnContra = GREATEST(golsEnContra - @golsC, 0), "
                        "diferenciaGols = golsAFavor - golsEnContra "
                        "WHERE idEquip = @idEquip AND idTemporada = @idTemporada";

                    String^ queryEquip = partitFinalitzat ? queryDesferEquipFinalitzat : queryDesferEquipNoFinalitzat;

                    MySqlCommand^ cmdEquipLocal = gcnew MySqlCommand(queryEquip, conn);
                    cmdEquipLocal->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    cmdEquipLocal->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                    cmdEquipLocal->Parameters->AddWithValue("@golsA", golsLocal);
                    cmdEquipLocal->Parameters->AddWithValue("@golsC", golsVisitant);
                    if (partitFinalitzat) {
                        cmdEquipLocal->Parameters->AddWithValue("@victories", victoriaLocal);
                        cmdEquipLocal->Parameters->AddWithValue("@derrotes", derrotaLocal);
                        cmdEquipLocal->Parameters->AddWithValue("@empats", empatLocal);
                        cmdEquipLocal->Parameters->AddWithValue("@punts", puntsLocal);
                    }
                    cmdEquipLocal->ExecuteNonQuery();

                    MySqlCommand^ cmdEquipVisitant = gcnew MySqlCommand(queryEquip, conn);
                    cmdEquipVisitant->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    cmdEquipVisitant->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                    cmdEquipVisitant->Parameters->AddWithValue("@golsA", golsVisitant);
                    cmdEquipVisitant->Parameters->AddWithValue("@golsC", golsLocal);
                    if (partitFinalitzat) {
                        cmdEquipVisitant->Parameters->AddWithValue("@victories", victoriaVisitant);
                        cmdEquipVisitant->Parameters->AddWithValue("@derrotes", derrotaVisitant);
                        cmdEquipVisitant->Parameters->AddWithValue("@empats", empatVisitant);
                        cmdEquipVisitant->Parameters->AddWithValue("@punts", puntsVisitant);
                    }
                    cmdEquipVisitant->ExecuteNonQuery();
                }

                List<Dictionary<String^, int>^>^ estadistiquesJugadors = gcnew List<Dictionary<String^, int>^>();
                String^ queryEstadistiquesJugadors =
                    "SELECT idJugador, "
                    "IFNULL(golsmarcat, 0) AS golsmarcat, "
                    "IFNULL(asistencies, 0) AS asistencies, "
                    "IFNULL(targetesgrogues, 0) AS targetesgrogues, "
                    "IFNULL(targetesvermelles, 0) AS targetesvermelles "
                    "FROM PartitEstadisticaIndividual "
                    "WHERE idPartit = @idPartit";
                MySqlCommand^ cmdEstadistiquesJugadors = gcnew MySqlCommand(queryEstadistiquesJugadors, conn);
                cmdEstadistiquesJugadors->Parameters->AddWithValue("@idPartit", idPartit);
                MySqlDataReader^ readerEstadistiques = cmdEstadistiquesJugadors->ExecuteReader();
                while (readerEstadistiques->Read()) {
                    Dictionary<String^, int>^ fila = gcnew Dictionary<String^, int>();
                    fila["idJugador"] = Convert::ToInt32(readerEstadistiques["idJugador"]);
                    fila["golsmarcat"] = Convert::ToInt32(readerEstadistiques["golsmarcat"]);
                    fila["asistencies"] = Convert::ToInt32(readerEstadistiques["asistencies"]);
                    fila["targetesgrogues"] = Convert::ToInt32(readerEstadistiques["targetesgrogues"]);
                    fila["targetesvermelles"] = Convert::ToInt32(readerEstadistiques["targetesvermelles"]);
                    estadistiquesJugadors->Add(fila);
                }
                readerEstadistiques->Close();

                if (partitFinalitzat) {
                    for each(Dictionary<String^, int> ^ fila in estadistiquesJugadors) {
                        String^ queryDesferJugador =
                            "UPDATE Jugador SET "
                            "partitsJugats = GREATEST(partitsJugats - 1, 0), "
                            "anotacions = GREATEST(anotacions - @gols, 0), "
                            "assistencies = GREATEST(assistencies - @assistencies, 0), "
                            "faltesLleus = GREATEST(faltesLleus - @targetesGrogues, 0), "
                            "faltesGreus = GREATEST(faltesGreus - @targetesVermelles, 0) "
                            "WHERE idJugador = @idJugador";
                        MySqlCommand^ cmdDesferJugador = gcnew MySqlCommand(queryDesferJugador, conn);
                        cmdDesferJugador->Parameters->AddWithValue("@idJugador", fila["idJugador"]);
                        cmdDesferJugador->Parameters->AddWithValue("@gols", fila["golsmarcat"]);
                        cmdDesferJugador->Parameters->AddWithValue("@assistencies", fila["asistencies"]);
                        cmdDesferJugador->Parameters->AddWithValue("@targetesGrogues", fila["targetesgrogues"]);
                        cmdDesferJugador->Parameters->AddWithValue("@targetesVermelles", fila["targetesvermelles"]);
                        cmdDesferJugador->ExecuteNonQuery();
                    }
                }

                String^ queryDeleteEstadistiques = "DELETE FROM PartitEstadisticaIndividual WHERE idPartit = @idPartit";
                MySqlCommand^ cmdDeleteEstadistiques = gcnew MySqlCommand(queryDeleteEstadistiques, conn);
                cmdDeleteEstadistiques->Parameters->AddWithValue("@idPartit", idPartit);
                cmdDeleteEstadistiques->ExecuteNonQuery();

                String^ queryDeleteConvocatoria = "DELETE FROM ConvocatoriaPartit WHERE idPartit = @idPartit";
                MySqlCommand^ cmdDeleteConvocatoria = gcnew MySqlCommand(queryDeleteConvocatoria, conn);
                cmdDeleteConvocatoria->Parameters->AddWithValue("@idPartit", idPartit);
                cmdDeleteConvocatoria->ExecuteNonQuery();

                String^ queryDeletePartit = "DELETE FROM Partit WHERE idPartit = @idPartit";
                MySqlCommand^ cmdDeletePartit = gcnew MySqlCommand(queryDeletePartit, conn);
                cmdDeletePartit->Parameters->AddWithValue("@idPartit", idPartit);
                cmdDeletePartit->ExecuteNonQuery();

            }
            catch (Exception^) {
                throw;
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                }
            }
        }

        void PassarellaPartit::ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
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
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idP", idPartit);
                cmd->Parameters->AddWithValue("@idJ", idJugador);
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaPartit::ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE ConvocatoriaPartit SET confirmat = @conf WHERE idPartit = @idP AND idJugador = @idJ";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idP", idPartit);
                cmd->Parameters->AddWithValue("@idJ", idJugador);
                cmd->Parameters->AddWithValue("@conf", assisteix ? 1 : 0);
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaPartit::AssignarJugadorAPartit(String^ idPartit, String^ idJugador) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO AssignacioJugadorPartit (idPartit, idJugador, dataAssignacio) VALUES (@idPartit, @idJugador, NOW())";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }


        void PassarellaPartit::ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit) {
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            Dictionary<String^, String^>^ detall = cercadoraPartit->ObtenirDetallPartit(idPartit, correuAdmin);
            String^ disciplina = detall["disciplina"];
            String^ estatAnterior = detall["estat"];

            if (String::IsNullOrWhiteSpace(nouEstat)) {
                throw gcnew ArgumentException("L'estat del partit és obligatori.");
            }

            Dictionary<String^, String^>^ etiquetes = Playcampus::Domini::EtiquetesEditarPartit::ObtenirEtiquetesEditarPartit(disciplina);
            if (resultatLocal < 0) {
                String^ campLocal = etiquetes["marcadorLocal"]->Replace(":", "")->Trim();
                throw gcnew ArgumentException("El camp '" + campLocal + "' no pot ser negatiu.");
            }
            if (resultatVisitant < 0) {
                String^ campVisitant = etiquetes["marcadorVisitant"]->Replace(":", "")->Trim();
                throw gcnew ArgumentException("El camp '" + campVisitant + "' no pot ser negatiu.");
            }

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

                // Obtenir equips i temporada del partit per actualitzar stats de EquipTemporada
                String^ queryEquips =
                    "SELECT P.idEquipLocal, P.idEquipVisitant, J.idTemporada "
                    "FROM Partit P "
                    "INNER JOIN Jornada J ON J.idJornada = P.idJornada "
                    "WHERE P.idPartit = @idPartit LIMIT 1";
                MySqlCommand^ cmdEquips = gcnew MySqlCommand(queryEquips, conn);
                cmdEquips->Parameters->AddWithValue("@idPartit", idPartit);
                String^ idEquipLocal = nullptr;
                String^ idEquipVisitant = nullptr;
                String^ idTemporadaPartit = nullptr;
                MySqlDataReader^ readerEquips = cmdEquips->ExecuteReader();
                if (readerEquips->Read()) {
                    idEquipLocal = readerEquips["idEquipLocal"]->ToString();
                    idEquipVisitant = readerEquips["idEquipVisitant"]->ToString();
                    idTemporadaPartit = readerEquips["idTemporada"]->ToString();
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

                // estadístiques individuals es guarden per jugador en format normalitzat

                // Actualitzar Estadístiques Equip (només si l'estat és Finalitzat)
                if (nouEstat == "Finalitzat" && estatAnterior != "Finalitzat" && idEquipLocal != nullptr && idEquipVisitant != nullptr && idTemporadaPartit != nullptr) {

                    int diffGolsLocal = resultatLocal - golsLocalAnterior;
                    int diffGolsVisitant = resultatVisitant - golsVisitantAnterior;

                    String^ queryUpdateEquipLocal =
                        "UPDATE EquipTemporada SET "
                        "partitsJugats = partitsJugats + 1, "
                        "golsAFavor = golsAFavor + @golsA, "
                        "golsEnContra = golsEnContra + @golsC, "
                        "diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC), "
                        "victories = victories + @victories, "
                        "derrotes = derrotes + @derrotes, "
                        "empats = empats + @empats, "
                        "punts = punts + @punts "
                        "WHERE idEquip = @idEquip AND idTemporada = @idTemporada";

                    MySqlCommand^ cmdUpdateLocal = gcnew MySqlCommand(queryUpdateEquipLocal, conn);
                    cmdUpdateLocal->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    cmdUpdateLocal->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
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
                        "UPDATE EquipTemporada SET "
                        "partitsJugats = partitsJugats + 1, "
                        "golsAFavor = golsAFavor + @golsA, "
                        "golsEnContra = golsEnContra + @golsC, "
                        "diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC), "
                        "victories = victories + @victories, "
                        "derrotes = derrotes + @derrotes, "
                        "empats = empats + @empats, "
                        "punts = punts + @punts "
                        "WHERE idEquip = @idEquip AND idTemporada = @idTemporada";

                    MySqlCommand^ cmdUpdateVisitant = gcnew MySqlCommand(queryUpdateEquipVisitant, conn);
                    cmdUpdateVisitant->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    cmdUpdateVisitant->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
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
                }
                else if (nouEstat == "Pendent" || nouEstat == "En curs" || nouEstat == "En joc") {
                    // Update per canvis de gols mentres el partit encara NO s'ha finalitzat i s'afegeixen gols
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;

                    if ((addGolsLocal != 0 || addGolsVisitant != 0) && idTemporadaPartit != nullptr) {
                        String^ queryUpdateGolsLocal = "UPDATE EquipTemporada SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGolsLocal, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        String^ queryUpdateGolsVisitant = "UPDATE EquipTemporada SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGolsVisitant, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsA", addGolsVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@golsC", addGolsLocal);
                        cmdUpdateGolsV->ExecuteNonQuery();
                    }
                }
                else if (estatAnterior == "Finalitzat" && nouEstat == "Finalitzat" && idTemporadaPartit != nullptr && (resultatLocal != golsLocalAnterior || resultatVisitant != golsVisitantAnterior)) {
                    // Update per canvis de gols mentres el partit s'ha finalitzat prèviament. Aquí a part dels gols també s'han de canviar els partits
                    // ja que l'acumulació de gols general ja es va fer.

                    // Afegim gols només la diferència
                    int addGolsLocal = resultatLocal - golsLocalAnterior;
                    int addGolsVisitant = resultatVisitant - golsVisitantAnterior;

                    if ((addGolsLocal != 0 || addGolsVisitant != 0) && idTemporadaPartit != nullptr) {
                        String^ queryUpdateGolsLocal = "UPDATE EquipTemporada SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                        MySqlCommand^ cmdUpdateGolsL = gcnew MySqlCommand(queryUpdateGolsLocal, conn);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsA", addGolsLocal);
                        cmdUpdateGolsL->Parameters->AddWithValue("@golsC", addGolsVisitant);
                        cmdUpdateGolsL->ExecuteNonQuery();

                        String^ queryUpdateGolsVisitant = "UPDATE EquipTemporada SET golsAFavor = golsAFavor + @golsA, golsEnContra = golsEnContra + @golsC, diferenciaGols = (golsAFavor + @golsA) - (golsEnContra + @golsC) WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                        MySqlCommand^ cmdUpdateGolsV = gcnew MySqlCommand(queryUpdateGolsVisitant, conn);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                        cmdUpdateGolsV->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
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
                    String^ qUndoUpdateL = "UPDATE EquipTemporada SET victories = victories - @vicO + @vicN, derrotes = derrotes - @derO + @derN, empats = empats - @empO + @empN, punts = punts - @ptsO + @ptsN WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                    MySqlCommand^ cmdUndoL = gcnew MySqlCommand(qUndoUpdateL, conn);
                    cmdUndoL->Parameters->AddWithValue("@idEquip", idEquipLocal);
                    cmdUndoL->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
                    cmdUndoL->Parameters->AddWithValue("@vicO", vicL_old); cmdUndoL->Parameters->AddWithValue("@vicN", vicL_new);
                    cmdUndoL->Parameters->AddWithValue("@derO", derL_old); cmdUndoL->Parameters->AddWithValue("@derN", derL_new);
                    cmdUndoL->Parameters->AddWithValue("@empO", empL_old); cmdUndoL->Parameters->AddWithValue("@empN", empL_new);
                    cmdUndoL->Parameters->AddWithValue("@ptsO", puntsL_old); cmdUndoL->Parameters->AddWithValue("@ptsN", puntsL_new);
                    cmdUndoL->ExecuteNonQuery();

                    // Update visitant team
                    String^ qUndoUpdateV = "UPDATE EquipTemporada SET victories = victories - @vicO + @vicN, derrotes = derrotes - @derO + @derN, empats = empats - @empO + @empN, punts = punts - @ptsO + @ptsN WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                    MySqlCommand^ cmdUndoV = gcnew MySqlCommand(qUndoUpdateV, conn);
                    cmdUndoV->Parameters->AddWithValue("@idEquip", idEquipVisitant);
                    cmdUndoV->Parameters->AddWithValue("@idTemporada", idTemporadaPartit);
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
