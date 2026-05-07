#include "pch.h"
#include "PassarellaJornada.hxx"
#include "ConnexioBD.hxx"

using namespace System::Collections::Generic;
using namespace Playcampus::Dades;
using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

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
        conn->Close();
    }
}

void PassarellaJornada::ActualitzarEstats(String^ connStr) {
    MySqlConnection^ conn = gcnew MySqlConnection(connStr);
    try {
        conn->Open();
        String^ queryJ = "UPDATE Jornada SET estat = CASE "
            "WHEN NOW() >= dataInici AND NOW() <= dataFi THEN 'EnCurs' "
            "WHEN NOW() > dataFi THEN 'Finalitzat' "
            "ELSE estat END "
            "WHERE (NOW() >= dataInici AND NOW() <= dataFi AND estat != 'EnCurs') "
            "OR (NOW() > dataFi AND estat != 'Finalitzat')";

        MySqlCommand^ cmd = gcnew MySqlCommand(queryJ, conn);
        cmd->ExecuteNonQuery();
    }
    finally {
        conn->Close();
    }
}

