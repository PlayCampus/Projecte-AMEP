#include "pch.h"
#include "CercadoraJornada.hxx"

using namespace System::Collections::Generic;
using namespace Playcampus::Dades;
using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

CercadoraJornada::CercadoraJornada(String^ connStr) {
    this->connectionString = connStr;
}

List<Dictionary<String^, String^>^>^ CercadoraJornada::ObtenirDictJornadesPerTemporada(String^ idTemporada) {

    //ACTUALITZEM ESTATS ABANS DE CONSULTAR
    PassarellaJornada::ActualitzarEstats(connectionString);

    List<Dictionary<String^, String^>^>^ jornades = gcnew List<Dictionary<String^, String^>^>();
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    try {
        conn->Open();
        String^ query = "SELECT idJornada, numero, dataInici, dataFi, estat FROM Jornada WHERE idTemporada = @idTemp";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@idTemp", idTemporada);
        MySqlDataReader^ reader = cmd->ExecuteReader();

        while (reader->Read()) {
            Dictionary<String^, String^>^ dict = gcnew Dictionary<String^, String^>();
            dict["idJornada"] = reader["idJornada"]->ToString();
            dict["numero"] = reader["numero"]->ToString();
            dict["dataInici"] = reader["dataInici"]->ToString();
            dict["dataFi"] = Convert::ToDateTime(reader["dataFi"]).ToString("dd/MM/yyyy HH:mm");
            dict["estat"] = reader["estat"]->ToString();

            jornades->Add(dict);
        }
        reader->Close();
    }
    finally {
        conn->Close();
    }
    return jornades;
}

String^ CercadoraJornada::ObtenirIdTemporadaPerJornada(String^ idJornada) {
    String^ idTemporada = nullptr;
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    try {
        conn->Open();
        String^ query = "SELECT idTemporada FROM Jornada WHERE idJornada = @idJornada LIMIT 1";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@idJornada", idJornada);
        Object^ result = cmd->ExecuteScalar();
        if (result != nullptr) {
            idTemporada = result->ToString();
        }
    }
    finally {
        if (conn != nullptr) {
            conn->Close();
            delete conn;
        }
    }
    return idTemporada;
}
