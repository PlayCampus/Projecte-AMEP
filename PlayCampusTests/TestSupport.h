#pragma once

#include "pch.h"
#include "gtest/gtest.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/gcroot.h>
#include <string>

#include "../Playcampus/Dades/ConnexioBD.hxx"
#include "../Playcampus/Domini/CtrlRegistrarUsuari.hxx"
#include "../Playcampus/Domini/CtrlIniciSessio.hxx"
#include "../Playcampus/Domini/CtrlEnregistrarEquip.hxx"
#include "../Playcampus/Domini/CtrlCrearLliga.hxx"
#include "../Playcampus/Domini/CtrlCrearTemporada.hxx"
#include "../Playcampus/Domini/CtrlCrearJornada.hxx"
#include "../Playcampus/Domini/CtrlCrearPartit.hxx"
#include "../Playcampus/Domini/CtrlAfegirJugador.hxx"
#include "../Playcampus/Domini/CtrlVeurePlantilla.hxx"
#include "../Playcampus/Domini/CtrlEditarJugador.hxx"
#include "../Playcampus/Domini/CtrlEliminarJugador.hxx"
#include "../Playcampus/Domini/CtrlAssignarJugador.hxx"
#include "../Playcampus/Domini/CtlrConvocarJugadors.hxx"
#include "../Playcampus/Domini/CtrlEditarPartit.hxx"
#include "../Playcampus/Domini/CtrlEsborrarPartit.hxx"
#include "../Playcampus/Domini/CtrlUnirEquipLliga.hxx"
#include "../Playcampus/Domini/CtrlConsultes.hxx"
#include "../Playcampus/Domini/CtrlVeureEstadistiquesLliga.hxx"
#include "../Playcampus/Domini/CtrlVeureEstadistiquesEquip.hxx"
#include "../Playcampus/Domini/CtrlVeureEstadistiquesJugadors.hxx"
#include "../Playcampus/Domini/CtrlEstadistiquesPartit.hxx"
#include "../Playcampus/Domini/CtrlTancarSessio.hxx"
#include "../Playcampus/Domini/CtrlRetirarTemporada.hxx"
#include "../Playcampus/Domini/CtrlConsultaFitxatges.hxx"
#include "../Playcampus/Domini/CtrlConsultaLligues.hxx"
#include "../Playcampus/Domini/CtrlConsultaPartits.hxx"
#include "../Playcampus/Domini/CtrlConsultaTelefons.hxx"

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Domini;
using namespace Playcampus::Dades;

#define EXPECT_MANAGED_EXCEPTION(statement) \
    do { \
        bool gtestHaLlencat = false; \
        try { \
            statement; \
        } \
        catch (System::Exception^) { \
            gtestHaLlencat = true; \
        } \
        EXPECT_TRUE(gtestHaLlencat); \
    } while (false)

#define EXPECT_MANAGED_EXCEPTION_TYPE(statement, exceptionType) \
    do { \
        bool gtestHaLlencat = false; \
        try { \
            statement; \
        } \
        catch (exceptionType^) { \
            gtestHaLlencat = true; \
        } \
        catch (System::Exception^ ex) { \
            ADD_FAILURE() << "S'esperava una excepcio d'un altre tipus. Rebuda: " \
                          << msclr::interop::marshal_as<std::string>(ex->GetType()->FullName); \
            gtestHaLlencat = true; \
        } \
        EXPECT_TRUE(gtestHaLlencat); \
    } while (false)

namespace PlayCampusTests {

    static std::string ToStd(String^ text) {
        std::string resultat = "";
        if (text != nullptr) {
            resultat = msclr::interop::marshal_as<std::string>(text);
        }
        return resultat;
    }

    static String^ EscaparSql(String^ valor) {
        String^ resultat = "";
        if (valor != nullptr) {
            resultat = valor->Replace("'", "''");
        }
        return resultat;
    }

    static String^ Connexio() {
        return ConnexioBD::ObtenirConnectionString();
    }

    static void ExecutarSql(String^ sql) {
        MySqlConnection^ conn = gcnew MySqlConnection(Connexio());
        try {
            conn->Open();
            MySqlCommand^ cmd = gcnew MySqlCommand(sql, conn);
            cmd->ExecuteNonQuery();
        }
        finally {
            if (conn != nullptr) {
                conn->Close();
                delete conn;
            }
        }
    }

    static Object^ EscalarSql(String^ sql) {
        Object^ resultat = nullptr;
        MySqlConnection^ conn = gcnew MySqlConnection(Connexio());
        try {
            conn->Open();
            MySqlCommand^ cmd = gcnew MySqlCommand(sql, conn);
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

    static int EscalarInt(String^ sql) {
        int resultat = 0;
        Object^ valor = EscalarSql(sql);
        if (valor != nullptr && valor != DBNull::Value) {
            resultat = Convert::ToInt32(valor);
        }
        return resultat;
    }

    static String^ EscalarString(String^ sql) {
        String^ resultat = nullptr;
        Object^ valor = EscalarSql(sql);
        if (valor != nullptr && valor != DBNull::Value) {
            resultat = valor->ToString();
        }
        return resultat;
    }

    static DataTable^ ConsultaSql(String^ sql) {
        DataTable^ taula = gcnew DataTable();
        MySqlConnection^ conn = gcnew MySqlConnection(Connexio());
        try {
            conn->Open();
            MySqlCommand^ cmd = gcnew MySqlCommand(sql, conn);
            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(taula);
        }
        finally {
            if (conn != nullptr) {
                conn->Close();
                delete conn;
            }
        }
        return taula;
    }

    static String^ NouCodi(String^ prefix) {
        return prefix + "-" + Guid::NewGuid().ToString("N")->Substring(0, 8);
    }

    static String^ NouCorreu(String^ prefix, String^ tag) {
        return prefix + "_" + tag + "@playcampus.test";
    }

    static int IdUsuariPerCorreu(String^ correu) {
        String^ sql = "SELECT identificador FROM Usuari WHERE correu_electronic = '" + EscaparSql(correu) + "' LIMIT 1";
        return EscalarInt(sql);
    }

    static void NetejarUsuariPerCorreu(String^ correu) {
        if (!String::IsNullOrWhiteSpace(correu)) {
            String^ correuSql = EscaparSql(correu);
            ExecutarSql("DELETE FROM UsuariSegueixLliga WHERE idUsuari IN (SELECT identificador FROM Usuari WHERE correu_electronic = '" + correuSql + "')");
            ExecutarSql("DELETE FROM Jugador WHERE idJugador IN (SELECT identificador FROM Usuari WHERE correu_electronic = '" + correuSql + "')");
            ExecutarSql("DELETE FROM Usuari WHERE correu_electronic = '" + correuSql + "'");
        }
    }

    public ref class EscenariProves {
    public:
        String^ tag;
        String^ adminEmail;
        String^ adminAltEmail;
        String^ capitaEmail;
        String^ capitaVisitantEmail;
        String^ estudiantEmail;
        String^ estudiant2Email;
        String^ estudiantVisitantEmail;
        String^ extraEmail;

        String^ lligaId;
        String^ lligaNom;
        String^ temporadaId;
        String^ jornadaId;
        String^ partitId;

        String^ equipLocalId;
        String^ equipLocalNom;
        String^ equipVisitantId;
        String^ equipVisitantNom;

        String^ jugadorId;
        String^ jugador2Id;
        String^ jugadorVisitantId;

        EscenariProves() {
            tag = Guid::NewGuid().ToString("N")->Substring(0, 8);
            adminEmail = NouCorreu("gtest_admin", tag);
            adminAltEmail = NouCorreu("gtest_admin_alt", tag);
            capitaEmail = NouCorreu("gtest_capita", tag);
            capitaVisitantEmail = NouCorreu("gtest_capita_visitant", tag);
            estudiantEmail = NouCorreu("gtest_estudiant", tag);
            estudiant2Email = NouCorreu("gtest_estudiant2", tag);
            estudiantVisitantEmail = NouCorreu("gtest_estudiant_visitant", tag);
            extraEmail = nullptr;

            lligaId = NouCodi("GTL");
            lligaNom = "GTest Lliga " + tag;
            temporadaId = nullptr;
            jornadaId = nullptr;
            partitId = nullptr;

            equipLocalId = NouCodi("GTEQL");
            equipLocalNom = "GTest Equip Local " + tag;
            equipVisitantId = NouCodi("GTEQV");
            equipVisitantNom = "GTest Equip Visitant " + tag;

            jugadorId = nullptr;
            jugador2Id = nullptr;
            jugadorVisitantId = nullptr;
        }

        void Cleanup() {
            try {
                if (!String::IsNullOrWhiteSpace(partitId)) {
                    String^ idPartitSql = EscaparSql(partitId);
                    ExecutarSql("DELETE FROM PartitEstadisticaIndividual WHERE idPartit = '" + idPartitSql + "'");
                    ExecutarSql("DELETE FROM AssignacioJugadorPartit WHERE idPartit = '" + idPartitSql + "'");
                    ExecutarSql("DELETE FROM ConvocatoriaPartit WHERE idPartit = '" + idPartitSql + "'");
                    ExecutarSql("DELETE FROM Partit WHERE idPartit = '" + idPartitSql + "'");
                }

                if (!String::IsNullOrWhiteSpace(jornadaId)) {
                    ExecutarSql("DELETE FROM Partit WHERE idJornada = '" + EscaparSql(jornadaId) + "'");
                    ExecutarSql("DELETE FROM Jornada WHERE idJornada = '" + EscaparSql(jornadaId) + "'");
                }

                if (!String::IsNullOrWhiteSpace(equipLocalId)) {
                    ExecutarSql("DELETE FROM EquipTemporada WHERE idEquip = '" + EscaparSql(equipLocalId) + "'");
                    ExecutarSql("DELETE FROM Equip WHERE idEquip = '" + EscaparSql(equipLocalId) + "'");
                }
                if (!String::IsNullOrWhiteSpace(equipVisitantId)) {
                    ExecutarSql("DELETE FROM EquipTemporada WHERE idEquip = '" + EscaparSql(equipVisitantId) + "'");
                    ExecutarSql("DELETE FROM Equip WHERE idEquip = '" + EscaparSql(equipVisitantId) + "'");
                }

                if (!String::IsNullOrWhiteSpace(temporadaId)) {
                    ExecutarSql("DELETE FROM Temporada WHERE idTemporada = '" + EscaparSql(temporadaId) + "'");
                }
                if (!String::IsNullOrWhiteSpace(lligaId)) {
                    ExecutarSql("DELETE FROM UsuariSegueixLliga WHERE idLliga = '" + EscaparSql(lligaId) + "'");
                    ExecutarSql("DELETE FROM Lliga WHERE idLliga = '" + EscaparSql(lligaId) + "'");
                }

                NetejarUsuariPerCorreu(extraEmail);
                NetejarUsuariPerCorreu(estudiantVisitantEmail);
                NetejarUsuariPerCorreu(estudiant2Email);
                NetejarUsuariPerCorreu(estudiantEmail);
                NetejarUsuariPerCorreu(capitaVisitantEmail);
                NetejarUsuariPerCorreu(capitaEmail);
                NetejarUsuariPerCorreu(adminAltEmail);
                NetejarUsuariPerCorreu(adminEmail);
            }
            catch (Exception^ ex) {
                Console::WriteLine("No s'ha pogut netejar completament l'escenari de proves: " + ex->Message);
            }
        }
    };

    static void RegistrarUsuarisBase(EscenariProves^ escenari) {
        CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
        DateTime dataRegistre = DateTime::Now.AddDays(-1);

        ctrl->CrearUsuari("GTest Admin", "pwd-admin", dataRegistre, escenari->adminEmail, "Administrador", "600000001");
        ctrl->CrearUsuari("GTest Admin Alt", "pwd-admin-alt", dataRegistre, escenari->adminAltEmail, "Administrador", "600000002");
        ctrl->CrearUsuari("GTest Capita", "pwd-capita", dataRegistre, escenari->capitaEmail, "Capita", "600000003");
        ctrl->CrearUsuari("GTest Capita Visitant", "pwd-capita-visitant", dataRegistre, escenari->capitaVisitantEmail, "Capita", "600000004");
        ctrl->CrearUsuari("GTest Estudiant", "pwd-estudiant", dataRegistre, escenari->estudiantEmail, "Estudiant", "");
        ctrl->CrearUsuari("GTest Estudiant 2", "pwd-estudiant2", dataRegistre, escenari->estudiant2Email, "Estudiant", "");
        ctrl->CrearUsuari("GTest Estudiant Visitant", "pwd-estudiant-visitant", dataRegistre, escenari->estudiantVisitantEmail, "Estudiant", "");
    }

    static EscenariProves^ CrearEscenariComplet() {
        EscenariProves^ escenari = gcnew EscenariProves();
        try {
            RegistrarUsuarisBase(escenari);

            CtrlCrearLliga^ ctrlLliga = gcnew CtrlCrearLliga();
            ctrlLliga->CrearLliga(escenari->lligaId, escenari->lligaNom, Disciplina::Futbol, "Lliga de proves GoogleTest", "secret", "Administrador", escenari->adminEmail);

            CtrlEnregistrarEquip^ ctrlEquip = gcnew CtrlEnregistrarEquip();
            ctrlEquip->EnregistrarEquip(escenari->equipLocalId, escenari->equipLocalNom, DateTime::Now.AddYears(-1), "Futbol", "Capita", escenari->capitaEmail);
            ctrlEquip->EnregistrarEquip(escenari->equipVisitantId, escenari->equipVisitantNom, DateTime::Now.AddYears(-1), "Futbol", "Capita", escenari->capitaVisitantEmail);

            CtrlCrearTemporada^ ctrlTemporada = gcnew CtrlCrearTemporada();
            ctrlTemporada->CrearTemporada(DateTime::Now.AddDays(-2), DateTime::Now.AddDays(60), escenari->adminEmail);
            escenari->temporadaId = EscalarString("SELECT idTemporada FROM Temporada WHERE idLliga = '" + EscaparSql(escenari->lligaId) + "' ORDER BY dataInici DESC LIMIT 1");

            ExecutarSql("INSERT INTO EquipTemporada (idEquip, idTemporada) VALUES ('" + EscaparSql(escenari->equipLocalId) + "', '" + EscaparSql(escenari->temporadaId) + "') ON DUPLICATE KEY UPDATE idEquip = idEquip");
            ExecutarSql("INSERT INTO EquipTemporada (idEquip, idTemporada) VALUES ('" + EscaparSql(escenari->equipVisitantId) + "', '" + EscaparSql(escenari->temporadaId) + "') ON DUPLICATE KEY UPDATE idEquip = idEquip");

            CtrlCrearJornada^ ctrlJornada = gcnew CtrlCrearJornada();
            ctrlJornada->CrearJornada(escenari->temporadaId, 1, DateTime::Now.AddDays(-1), DateTime::Now.AddDays(30), "Proxim");
            escenari->jornadaId = EscalarString("SELECT idJornada FROM Jornada WHERE idTemporada = '" + EscaparSql(escenari->temporadaId) + "' AND numero = 1 ORDER BY dataInici DESC LIMIT 1");

            CtrlAfegirJugador^ ctrlAfegir = gcnew CtrlAfegirJugador();
            ctrlAfegir->AfegirJugador(escenari->estudiantEmail, 10, "Davanter", escenari->capitaEmail, System::DateTime(2004, 1, 1));
            ctrlAfegir->AfegirJugador(escenari->estudiant2Email, 20, "Mig", escenari->capitaEmail, System::DateTime(2004, 1, 1));
            ctrlAfegir->AfegirJugador(escenari->estudiantVisitantEmail, 30, "Defensa", escenari->capitaVisitantEmail, System::DateTime(2004, 1, 1));

            escenari->jugadorId = Convert::ToString(IdUsuariPerCorreu(escenari->estudiantEmail));
            escenari->jugador2Id = Convert::ToString(IdUsuariPerCorreu(escenari->estudiant2Email));
            escenari->jugadorVisitantId = Convert::ToString(IdUsuariPerCorreu(escenari->estudiantVisitantEmail));

            CtrlCrearPartit^ ctrlPartit = gcnew CtrlCrearPartit();
            ctrlPartit->CrearPartit(DateTime::Now.AddDays(2), "Pista GoogleTest", escenari->equipLocalNom, escenari->equipVisitantNom, escenari->jornadaId, "Administrador");
            escenari->partitId = EscalarString("SELECT idPartit FROM Partit WHERE idJornada = '" + EscaparSql(escenari->jornadaId) + "' AND idEquipLocal = '" + EscaparSql(escenari->equipLocalId) + "' AND idEquipVisitant = '" + EscaparSql(escenari->equipVisitantId) + "' ORDER BY dataHora DESC LIMIT 1");
        }
        catch (Exception^) {
            escenari->Cleanup();
            throw;
        }
        return escenari;
    }

    static String^ RegistrarEstudiantExtra(EscenariProves^ escenari) {
        escenari->extraEmail = NouCorreu("gtest_extra", escenari->tag);
        CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
        ctrl->CrearUsuari("GTest Extra", "pwd-extra", DateTime::Now.AddDays(-1), escenari->extraEmail, "Estudiant", "");
        return escenari->extraEmail;
    }

    class FixtureControladors : public ::testing::Test {
    protected:
        msclr::gcroot<EscenariProves^> escenari;

        void SetUp() override {
            escenari = CrearEscenariComplet();
        }

        void TearDown() override {
            EscenariProves^ escenariActual = escenari;
            if (escenariActual != nullptr) {
                escenariActual->Cleanup();
                escenari = nullptr;
            }
        }
    };
}
