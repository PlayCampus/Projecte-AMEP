#include "CtrlVeureEstadistiquesLliga.hxx"
#include <vcclr.h>
#include <pch.h>
using namespace Playcampus::Domini;
using namespace MySql::Data::MySqlClient;

CtrlVeureEstadistiquesLliga::CtrlVeureEstadistiquesLliga() {
}

String^ CtrlVeureEstadistiquesLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
    String^ connectionString = "Server=ubiwan.epsevg.upc.edu;Database=amep06;Uid=TU_USUARIO;Pwd=TU_PASS;"; // Ajusta amb la teva connexio
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    String^ idLliga = nullptr;
    try {
        conn->Open();
        String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nomLliga";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@nomLliga", nomLliga);

        Object^ result = cmd->ExecuteScalar();
        if (result != nullptr) {
            idLliga = result->ToString();
        }
    }
    finally {
        conn->Close();
    }
    return idLliga;
}

DataTable^ CtrlVeureEstadistiquesLliga::ObtenirTemporadesLliga(String^ idLliga) {
    String^ connectionString = "Server=ubiwan.epsevg.upc.edu;Database=amep06;Uid=TU_USUARIO;Pwd=TU_PASS;";
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    DataTable^ dt = gcnew DataTable();
    try {
        conn->Open();
        // Ordenem per dataInici DESC per tenir la més recent primera
        String^ query = "SELECT idTemporada, CONCAT('Temporada ', DATE_FORMAT(dataInici, '%Y'), '-', DATE_FORMAT(dataFi, '%Y')) AS NomTemporada FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
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

DataTable^ CtrlVeureEstadistiquesLliga::ObtenirClassificacioLliga(String^ idLliga) {
    String^ connectionString = "Server=ubiwan.epsevg.upc.edu;Database=amep06;Uid=TU_USUARIO;Pwd=TU_PASS;";
    MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
    DataTable^ dt = gcnew DataTable();
    try {
        conn->Open();
        String^ query = "SELECT nom AS Equip, partitsJugats AS PJ, victories AS V, empats AS E, derrotes AS D, golsAFavor AS GF, golsEnContra AS GC, diferenciaGols AS DG, punts AS Punts FROM Equip WHERE idLliga = @idLliga ORDER BY punts DESC, diferenciaGols DESC";
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