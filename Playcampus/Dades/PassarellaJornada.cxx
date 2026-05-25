#include "pch.h"
#include "PassarellaJornada.hxx"
#include "ConnexioBD.hxx"

using namespace System::Collections::Generic;
using namespace Playcampus::Dades;
using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;


PassarellaJornada::PassarellaJornada(String^ connString) {
    connectionString = connString;
}
// Constructor con todos los atributos
PassarellaJornada::PassarellaJornada(String^ connStr, String^ idJornada, String^ idTemporada, int numero, DateTime dataInici, DateTime dataFi, String^ estat) {
    this->connectionString = connStr;
    this->idJornada = idJornada;
    this->idTemporada = idTemporada;
    this->numero = numero;
    this->dataInici = dataInici;
    this->dataFi = dataFi;
    this->estat = estat;
}

// Getters
String^ PassarellaJornada::GetIdJornada() { return idJornada; }
String^ PassarellaJornada::GetIdTemporada() { return idTemporada; }
DateTime PassarellaJornada::GetDataInici() { return dataInici; }
DateTime PassarellaJornada::GetDataFi() { return dataFi; }
String^ PassarellaJornada::GetEstat() { return estat; }
int PassarellaJornada::GetNumero() { return numero; }



void PassarellaJornada::Insereix() {
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

    try {
        conn->Open();
        String^ query = "INSERT INTO Jornada (idJornada, idTemporada,numero, dataInici, dataFi, estat) VALUES (@idJ, @idT,@num, @dInici, @dFi, @estat)";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@idJ", this->idJornada);
        cmd->Parameters->AddWithValue("@idT", this->idTemporada);
        cmd->Parameters->AddWithValue("@num", this->numero);
        cmd->Parameters->AddWithValue("@dInici", this->dataInici);
        cmd->Parameters->AddWithValue("@dFi", this->dataFi);
        cmd->Parameters->AddWithValue("@estat", this->estat);

        cmd->ExecuteNonQuery();
    }
    finally {
        if(conn != nullptr) {
            conn->Close();
            delete conn;
        }
    }
}

void PassarellaJornada::ActualitzarEstats(String^ connStr) {
    MySqlConnection^ conn = gcnew MySqlConnection(connStr);
    try {
        conn->Open();
        String^ queryJ = "UPDATE Jornada SET estat = CASE "
            "WHEN NOW() >= dataInici AND NOW() <= dataFi  AND estat != 'Finalitzat' THEN 'EnCurs' "
            "WHEN NOW() > dataFi THEN 'Finalitzat' "
            "ELSE estat END "
            "WHERE (NOW() >= dataInici AND NOW() <= dataFi AND estat != 'EnCurs') "
            "OR (NOW() > dataFi AND estat != 'Finalitzat')";

        MySqlCommand^ cmd = gcnew MySqlCommand(queryJ, conn);
        cmd->ExecuteNonQuery();
    }
    finally {
        if(conn != nullptr) {
            conn->Close();
            delete conn;
        }
    }
}

void PassarellaJornada::RetirarJornadesTemporada(String^ idTemp) {
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    try {
        conn->Open();
        // Actualizamos a 'Retirada' solo las jornadas que esten 'EnCurs' para esta temporada
        String^ query = "UPDATE Jornada SET estat = 'Finalitzat' WHERE idTemporada = @idTemporada AND estat = 'EnCurs'";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@idTemporada", idTemp);

        int filesInfectades = cmd->ExecuteNonQuery();
        if (filesInfectades == 0) {
            throw gcnew Exception("No s'ha trobat cap jornada en curs per a aquesta temporada.");
        }
    }
    finally {
        conn->Close();
    }
}

void PassarellaJornada::EsborrarJornada(String^ idJornada) {
    if (String::IsNullOrWhiteSpace(idJornada)) {
        throw gcnew ArgumentException("Has de seleccionar una jornada per poder esborrar-la.");
    }

    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    bool transaccioIniciada = false;

    try {
        conn->Open();

        // Fem servir sentències SQL de transacció en lloc de MySqlTransaction.
        // Això evita errors de dependències externes del connector MySQL en temps d'execució
        // i manté igualment el procés atòmic: o s'esborra tot, o no s'esborra res.
        MySqlCommand^ cmdIniciarTransaccio = gcnew MySqlCommand("START TRANSACTION", conn);
        cmdIniciarTransaccio->ExecuteNonQuery();
        transaccioIniciada = true;

        String^ queryFinalitzats =
            "SELECT COUNT(*) FROM Partit "
            "WHERE idJornada = @idJornada AND LOWER(estat) = 'finalitzat'";
        MySqlCommand^ cmdFinalitzats = gcnew MySqlCommand(queryFinalitzats, conn);
        cmdFinalitzats->Parameters->AddWithValue("@idJornada", idJornada);

        int partitsFinalitzats = Convert::ToInt32(cmdFinalitzats->ExecuteScalar());
        if (partitsFinalitzats > 0) {
            throw gcnew InvalidOperationException("No es pot borrar una jornada amb partits finalitzats");
        }

        String^ queryEsborrarPartits =
            "DELETE FROM Partit "
            "WHERE idJornada = @idJornada AND (estat IS NULL OR LOWER(estat) <> 'finalitzat')";
        MySqlCommand^ cmdEsborrarPartits = gcnew MySqlCommand(queryEsborrarPartits, conn);
        cmdEsborrarPartits->Parameters->AddWithValue("@idJornada", idJornada);
        cmdEsborrarPartits->ExecuteNonQuery();

        String^ queryEsborrarJornada = "DELETE FROM Jornada WHERE idJornada = @idJornada";
        MySqlCommand^ cmdEsborrarJornada = gcnew MySqlCommand(queryEsborrarJornada, conn);
        cmdEsborrarJornada->Parameters->AddWithValue("@idJornada", idJornada);

        int jornadesEsborrades = cmdEsborrarJornada->ExecuteNonQuery();
        if (jornadesEsborrades == 0) {
            throw gcnew Exception("No s'ha trobat la jornada seleccionada.");
        }

        MySqlCommand^ cmdCommit = gcnew MySqlCommand("COMMIT", conn);
        cmdCommit->ExecuteNonQuery();
        transaccioIniciada = false;
    }
    catch (Exception^) {
        if (transaccioIniciada && conn != nullptr && conn->State == ConnectionState::Open) {
            try {
                MySqlCommand^ cmdRollback = gcnew MySqlCommand("ROLLBACK", conn);
                cmdRollback->ExecuteNonQuery();
            }
            catch (Exception^) {
                // Si el rollback falla, conservem l'error original.
            }
        }
        throw;
    }
    finally {
        if (conn != nullptr) {
            conn->Close();
            delete conn;
        }
    }
}

