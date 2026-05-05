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
    List<Dictionary<String^, String^>^>^ jornades = gcnew List<Dictionary<String^, String^>^>();
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    try {
        conn->Open();
        String^ query = "SELECT idJornada, numero, dataInici, dataFi FROM Jornada WHERE idTemporada = @idTemp";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@idTemp", idTemporada);
        MySqlDataReader^ reader = cmd->ExecuteReader();

        while (reader->Read()) {
            Dictionary<String^, String^>^ dict = gcnew Dictionary<String^, String^>();
            dict["idJornada"] = reader["idJornada"]->ToString();
            dict["numero"] = reader["numero"]->ToString();
            dict["dataInici"] = reader["dataInici"]->ToString();
            jornades->Add(dict);
        }
        reader->Close();
    }
    finally {
        conn->Close();
    }
    return jornades;
}