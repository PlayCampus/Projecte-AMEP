// ControladorsTests.cpp
// Google Test per als controladors de Playcampus / AMEP.
//
// Important:
//  - És un test d'integració: executa els controladors reals i escriu a MySQL.
//  - Per seguretat no s'executa si no defineixes AMEP_RUN_DB_TESTS=1.
//  - Compila aquest fitxer en un projecte C++/CLI amb /clr i Google Test.

#include <gtest/gtest.h>
#include <msclr/marshal_cppstd.h>
#include <string>

#using <System.dll>
#using <System.Data.dll>
#using <MySql.Data.dll>

#include "../Playcampus/Dades/ConnexioBD.hxx"
#include "../Playcampus/Domini/Disciplina.hxx"
#include "../Playcampus/Domini/CtrlRegistrarUsuari.hxx"
#include "../Playcampus/Domini/CtrlIniciSessio.hxx"
#include "../Playcampus/Domini/CtrlCrearLliga.hxx"
#include "../Playcampus/Domini/CtrlEnregistrarEquip.hxx"
#include "../Playcampus/Domini/CtrlCrearTemporada.hxx"
#include "../Playcampus/Domini/CtrlCrearJornada.hxx"
#include "../Playcampus/Domini/CtrlCrearPartit.hxx"
#include "../Playcampus/Domini/CtrlEsborrarPartit.hxx"
#include "../Playcampus/Domini/CtrlEsborrarJornada.hxx"
#include "../Playcampus/Domini/CtrlUnirEquipLliga.hxx"
#include "../Playcampus/Domini/CtrlAbandonarLliga.hxx"
#include "../Playcampus/Domini/CtrlAfegirJugador.hxx"
#include "../Playcampus/Domini/CtrlEditarJugador.hxx"
#include "../Playcampus/Domini/CtrlEliminarJugador.hxx"
#include "../Playcampus/Domini/CtrlAssignarJugador.hxx"
#include "../Playcampus/Domini/CtrlVeurePlantilla.hxx"
#include "../Playcampus/Domini/CtrlSeguirLliga.hxx"
#include "../Playcampus/Domini/CtrlEditarPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace System::Globalization;
using namespace MySql::Data::MySqlClient;
using namespace Playcampus::Domini;

static std::string ToStdString(String^ value) {
    if (value == nullptr) return "<null>";
    return msclr::interop::marshal_as<std::string>(value);
}

#define ASSERT_NO_MANAGED_THROW(...)                                                      \
    do {                                                                                      \
        try {                                                                                 \
            __VA_ARGS__;                                                                      \
        } catch (System::Exception^ ex) {                                                     \
            FAIL() << "Excepcio .NET inesperada: "                                           \
                   << ToStdString(ex->GetType()->FullName + ": " + ex->Message);            \
        } catch (...) {                                                                       \
            FAIL() << "Excepcio nativa inesperada";                                          \
        }                                                                                     \
    } while (0)

#define EXPECT_NO_MANAGED_THROW(...)                                                      \
    do {                                                                                      \
        try {                                                                                 \
            __VA_ARGS__;                                                                      \
        } catch (System::Exception^ ex) {                                                     \
            ADD_FAILURE() << "Excepcio .NET inesperada: "                                    \
                          << ToStdString(ex->GetType()->FullName + ": " + ex->Message);     \
        } catch (...) {                                                                       \
            ADD_FAILURE() << "Excepcio nativa inesperada";                                   \
        }                                                                                     \
    } while (0)

#define EXPECT_MANAGED_THROW(exceptionType, ...)                                          \
    do {                                                                                      \
        bool caughtExpected = false;                                                          \
        try {                                                                                 \
            __VA_ARGS__;                                                                      \
        } catch (exceptionType^) {                                                            \
            caughtExpected = true;                                                            \
        } catch (System::Exception^ ex) {                                                     \
            ADD_FAILURE() << "S'esperava " #exceptionType ", pero s'ha capturat: "           \
                          << ToStdString(ex->GetType()->FullName + ": " + ex->Message);     \
            caughtExpected = true;                                                            \
        } catch (...) {                                                                       \
            ADD_FAILURE() << "S'esperava " #exceptionType ", pero s'ha capturat excepcio nativa"; \
            caughtExpected = true;                                                            \
        }                                                                                     \
        if (!caughtExpected) {                                                                \
            ADD_FAILURE() << "S'esperava excepcio " #exceptionType ", pero no s'ha llencat cap excepcio"; \
        }                                                                                     \
    } while (0)

public ref class SqlTest abstract sealed {
public:
    static String^ ConnStr() {
        return Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
    }

    static String^ Q(String^ value) {
        if (value == nullptr) return "NULL";
        return "'" + value->Replace("\\", "\\\\")->Replace("'", "''") + "'";
    }

    static String^ D(DateTime value) {
        return Q(value.ToString("yyyy-MM-dd HH:mm:ss", CultureInfo::InvariantCulture));
    }

    static void Exec(String^ sql) {
        MySqlConnection^ conn = gcnew MySqlConnection(ConnStr());
        try {
            conn->Open();
            MySqlCommand^ cmd = gcnew MySqlCommand(sql, conn);
            cmd->ExecuteNonQuery();
        }
        finally {
            if (conn != nullptr) conn->Close();
        }
    }

    static void TryExec(String^ sql) {
        try { Exec(sql); }
        catch (Exception^) {}
    }

    static Object^ Scalar(String^ sql) {
        MySqlConnection^ conn = gcnew MySqlConnection(ConnStr());
        try {
            conn->Open();
            MySqlCommand^ cmd = gcnew MySqlCommand(sql, conn);
            return cmd->ExecuteScalar();
        }
        finally {
            if (conn != nullptr) conn->Close();
        }
    }

    static int ScalarInt(String^ sql) {
        Object^ value = Scalar(sql);
        if (value == nullptr || value == DBNull::Value) return 0;
        return Convert::ToInt32(value);
    }

    static String^ ScalarString(String^ sql) {
        Object^ value = Scalar(sql);
        if (value == nullptr || value == DBNull::Value) return nullptr;
        return value->ToString();
    }
};

static String^ NewId(String^ prefix) {
    return prefix + "-" + Guid::NewGuid().ToString("N")->Substring(0, 8);
}

static String^ NewName(String^ prefix) {
    return prefix + "_" + Guid::NewGuid().ToString("N")->Substring(0, 8);
}

static String^ NewMail(String^ prefix) {
    return prefix + "." + Guid::NewGuid().ToString("N")->Substring(0, 8) + "@gtest.amep";
}

static String^ I(int value) {
    return Convert::ToString(value, CultureInfo::InvariantCulture);
}

static int IdUsuari(String^ correu) {
    return SqlTest::ScalarInt(
        "SELECT identificador FROM Usuari WHERE correu_electronic = " + SqlTest::Q(correu) + " LIMIT 1");
}

static void CrearUsuari(String^ nom, String^ pass, String^ correu, String^ tipus) {
    CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
    ctrl->CrearUsuari(nom, pass, DateTime::Now, correu, tipus, "600000000");
}

static void InsertLliga(String^ idLliga, String^ nom, String^ pass, String^ correuAdmin) {
    String^ idAdminSql = "NULL";
    if (!String::IsNullOrWhiteSpace(correuAdmin)) {
        idAdminSql = I(IdUsuari(correuAdmin));
    }

    SqlTest::Exec(
        "INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, contrasenya, idAdministrador) VALUES (" +
        SqlTest::Q(idLliga) + "," + SqlTest::Q(nom) + ",'Futbol','Lliga Google Test'," +
        SqlTest::Q(pass) + "," + idAdminSql + ")");
}

static void InsertTemporada(String^ idTemporada, String^ idLliga, DateTime inici, DateTime fi, String^ estat) {
    SqlTest::Exec(
        "INSERT INTO Temporada (idTemporada, idLliga, dataInici, dataFi, estat) VALUES (" +
        SqlTest::Q(idTemporada) + "," + SqlTest::Q(idLliga) + "," + SqlTest::D(inici) + "," +
        SqlTest::D(fi) + "," + SqlTest::Q(estat) + ")");
}

static void InsertJornada(String^ idJornada, String^ idTemporada, int numero, DateTime inici, DateTime fi, String^ estat) {
    SqlTest::Exec(
        "INSERT INTO Jornada (idJornada, idTemporada, numero, dataInici, dataFi, estat) VALUES (" +
        SqlTest::Q(idJornada) + "," + SqlTest::Q(idTemporada) + "," +
        I(numero) + "," + SqlTest::D(inici) + "," + SqlTest::D(fi) + "," +
        SqlTest::Q(estat) + ")");
}

static void InsertEquip(String^ idEquip, String^ nom, String^ esport, String^ idTemporada) {
    SqlTest::Exec(
        "INSERT INTO Equip (idEquip, nom, dataFundacio, esport, idTemporada) VALUES (" +
        SqlTest::Q(idEquip) + "," + SqlTest::Q(nom) + "," + SqlTest::D(DateTime::Now.AddYears(-1)) + "," +
        SqlTest::Q(esport) + "," + SqlTest::Q(idTemporada) + ")");
}

static void AssignarEquipACapita(String^ correuCapita, String^ idEquip) {
    SqlTest::Exec(
        "UPDATE Capita SET idEquip = " + SqlTest::Q(idEquip) +
        " WHERE identificador = " + I(IdUsuari(correuCapita)));
}

static void InsertPartit(String^ idPartit, String^ idJornada, String^ idLocal, String^ idVisitant, String^ estat) {
    SqlTest::Exec(
        "INSERT INTO Partit (idPartit, idJornada, idEquipLocal, idEquipVisitant, dataHora, ubicacio, estat, golsLocal, golsVisitant) VALUES (" +
        SqlTest::Q(idPartit) + "," + SqlTest::Q(idJornada) + "," + SqlTest::Q(idLocal) + "," +
        SqlTest::Q(idVisitant) + "," + SqlTest::D(DateTime::Now.AddDays(5)) + ",'Pista GT'," +
        SqlTest::Q(estat) + ",0,0)");
}

static void CleanupTestData() {
    // El prefix GT- i el domini @gtest.amep eviten tocar dades manuals.
    // També netegem registres generats pels controladors sota una lliga GT-.
    String^ partitsDeTest =
        "SELECT p.idPartit FROM Partit p "
        "LEFT JOIN Jornada j ON p.idJornada = j.idJornada "
        "LEFT JOIN Temporada t ON j.idTemporada = t.idTemporada "
        "WHERE p.idPartit LIKE 'GT-%' OR p.idJornada LIKE 'GT-%' OR t.idTemporada LIKE 'GT-%' OR t.idLliga LIKE 'GT-%'";

    SqlTest::TryExec("DELETE FROM PartitEstadisticaIndividual WHERE idPartit LIKE 'GT-%' OR idPartit IN (" + partitsDeTest + ")");
    SqlTest::TryExec("DELETE FROM AssignacioJugadorPartit WHERE idPartit LIKE 'GT-%' OR idPartit IN (" + partitsDeTest + ") OR idJugador IN (SELECT identificador FROM Usuari WHERE correu_electronic LIKE '%@gtest.amep')");
    SqlTest::TryExec("DELETE FROM ConvocatoriaPartit WHERE idPartit LIKE 'GT-%' OR idPartit IN (" + partitsDeTest + ") OR idJugador IN (SELECT identificador FROM Usuari WHERE correu_electronic LIKE '%@gtest.amep')");
    SqlTest::TryExec("DELETE p FROM Partit p LEFT JOIN Jornada j ON p.idJornada = j.idJornada LEFT JOIN Temporada t ON j.idTemporada = t.idTemporada WHERE p.idPartit LIKE 'GT-%' OR p.idJornada LIKE 'GT-%' OR t.idTemporada LIKE 'GT-%' OR t.idLliga LIKE 'GT-%'");
    SqlTest::TryExec("DELETE FROM Jornada WHERE idJornada LIKE 'GT-%' OR idTemporada LIKE 'GT-%' OR idTemporada IN (SELECT idTemporada FROM Temporada WHERE idLliga LIKE 'GT-%')");
    SqlTest::TryExec("UPDATE Equip SET idTemporada = NULL WHERE idEquip LIKE 'GT-%' OR idTemporada LIKE 'GT-%' OR idTemporada IN (SELECT idTemporada FROM Temporada WHERE idLliga LIKE 'GT-%')");
    SqlTest::TryExec("DELETE FROM Equip WHERE idEquip LIKE 'GT-%'");
    SqlTest::TryExec("DELETE FROM Temporada WHERE idTemporada LIKE 'GT-%' OR idLliga LIKE 'GT-%'");
    SqlTest::TryExec("DELETE FROM UsuariSegueixLliga WHERE idLliga LIKE 'GT-%' OR idUsuari IN (SELECT identificador FROM Usuari WHERE correu_electronic LIKE '%@gtest.amep')");
    SqlTest::TryExec("DELETE FROM Lliga WHERE idLliga LIKE 'GT-%'");
    SqlTest::TryExec("DELETE FROM Usuari WHERE correu_electronic LIKE '%@gtest.amep'");
}

class ControladorsDbTest : public ::testing::Test {
protected:
    void SetUp() override {
        String^ enabled = Environment::GetEnvironmentVariable("AMEP_RUN_DB_TESTS");
        if (enabled == nullptr || enabled != "1") {
            GTEST_SKIP() << "Defineix AMEP_RUN_DB_TESTS=1 per executar tests que escriuen a la base de dades.";
        }
        CleanupTestData();
    }

    void TearDown() override {
        String^ enabled = Environment::GetEnvironmentVariable("AMEP_RUN_DB_TESTS");
        if (enabled != nullptr && enabled == "1") {
            CleanupTestData();
        }
    }
};

TEST_F(ControladorsDbTest, RegistrarUsuariIIniciarSessio) {
    String^ correu = NewMail("estudiant");

    ASSERT_NO_MANAGED_THROW(CrearUsuari("Estudiant GT", "pwd123", correu, "Estudiant"));

    CtrlIniciSessio^ inici = gcnew CtrlIniciSessio();
    EXPECT_TRUE(inici->IniciarSessio(correu, "pwd123"));
    EXPECT_FALSE(inici->IniciarSessio(correu, "pwd-malament"));
    EXPECT_TRUE(inici->ObtenirTipusUsuari(correu)->Equals("Estudiant"));
}

TEST_F(ControladorsDbTest, CrearLliga_NomesAdministrador) {
    String^ admin = NewMail("admin");
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    CrearUsuari("Admin GT", "pwd", admin, "Administrador");

    CtrlCrearLliga^ ctrl = gcnew CtrlCrearLliga();
    ASSERT_NO_MANAGED_THROW(ctrl->CrearLliga(idLliga, nomLliga, Disciplina::Futbol, "desc", "secret", "Administrador", admin));

    EXPECT_TRUE(ctrl->ExisteixLliga(nomLliga));
    EXPECT_TRUE(ctrl->TeLligaActiva(admin));

    EXPECT_MANAGED_THROW(System::UnauthorizedAccessException,
        ctrl->CrearLliga(NewId("GT-LLIGA"), NewName("GT_Lliga"), Disciplina::Futbol, "desc", "secret", "Estudiant", admin));
}

TEST_F(ControladorsDbTest, EnregistrarEquip_AssignaEquipAlCapita) {
    String^ capita = NewMail("capita");
    String^ idEquip = NewId("GT-EQUIP");
    String^ nomEquip = NewName("GT_Equip");
    CrearUsuari("Capita GT", "pwd", capita, "Capita");

    CtrlEnregistrarEquip^ ctrl = gcnew CtrlEnregistrarEquip();
    ASSERT_NO_MANAGED_THROW(ctrl->EnregistrarEquip(idEquip, nomEquip, DateTime::Now.AddYears(-2), "Futbol", "Capita", capita));

    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Equip WHERE idEquip = " + SqlTest::Q(idEquip)));
    EXPECT_TRUE(SqlTest::ScalarString("SELECT idEquip FROM Capita WHERE identificador = " + I(IdUsuari(capita)))->Equals(idEquip));

    EXPECT_MANAGED_THROW(System::UnauthorizedAccessException,
        ctrl->EnregistrarEquip(NewId("GT-EQUIP"), NewName("GT_Equip"), DateTime::Now, "Futbol", "Estudiant", capita));
}

TEST_F(ControladorsDbTest, CrearTemporadaICrearJornada) {
    String^ admin = NewMail("admin");
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    CrearUsuari("Admin GT", "pwd", admin, "Administrador");
    InsertLliga(idLliga, nomLliga, "secret", admin);

    CtrlCrearTemporada^ ctrlTemp = gcnew CtrlCrearTemporada();
    ASSERT_NO_MANAGED_THROW(ctrlTemp->CrearTemporada(DateTime::Now.AddDays(10), DateTime::Now.AddDays(80), admin, nomLliga));

    String^ idTemporada = SqlTest::ScalarString(
        "SELECT idTemporada FROM Temporada WHERE idLliga = " + SqlTest::Q(idLliga) + " ORDER BY dataInici DESC LIMIT 1");
    ASSERT_TRUE(idTemporada != nullptr);

    CtrlCrearJornada^ ctrlJornada = gcnew CtrlCrearJornada();
    EXPECT_TRUE(ctrlJornada->ValidarAdministradorLliga(nomLliga, admin));
    ASSERT_NO_MANAGED_THROW(ctrlJornada->CrearJornada(idTemporada, 1, DateTime::Now.AddDays(11), DateTime::Now.AddDays(18), "Pròxim"));

    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jornada WHERE idTemporada = " + SqlTest::Q(idTemporada) + " AND numero = 1"));
}

TEST_F(ControladorsDbTest, CrearPartit_ValidaEquipsDiferentsICreaPartit) {
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idLocal = NewId("GT-EQUIP");
    String^ idVisitant = NewId("GT-EQUIP");
    String^ nomLocal = NewName("GT_Local");
    String^ nomVisitant = NewName("GT_Visitant");

    InsertLliga(idLliga, nomLliga, "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idLocal, nomLocal, "Futbol", idTemp);
    InsertEquip(idVisitant, nomVisitant, "Futbol", idTemp);

    CtrlCrearPartit^ ctrl = gcnew CtrlCrearPartit();
    EXPECT_MANAGED_THROW(System::ArgumentException,
        ctrl->CrearPartit(DateTime::Now.AddDays(3), "Pista 1", nomLocal, nomLocal, idJornada, "Administrador"));

    ASSERT_NO_MANAGED_THROW(ctrl->CrearPartit(DateTime::Now.AddDays(3), "Pista 1", nomLocal, nomVisitant, idJornada, "Administrador"));
    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Partit WHERE idJornada = " + SqlTest::Q(idJornada) + " AND ubicacio = 'Pista 1'"));
}

TEST_F(ControladorsDbTest, EsborrarPartit_EliminaElPartitSeleccionat) {
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idLocal = NewId("GT-EQUIP");
    String^ idVisitant = NewId("GT-EQUIP");
    String^ idPartit = NewId("GT-PARTIT");

    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idLocal, NewName("GT_Local"), "Futbol", idTemp);
    InsertEquip(idVisitant, NewName("GT_Visitant"), "Futbol", idTemp);
    InsertPartit(idPartit, idJornada, idLocal, idVisitant, "Pendent");

    CtrlEsborrarPartit^ ctrl = gcnew CtrlEsborrarPartit();
    ASSERT_NO_MANAGED_THROW(ctrl->EsborrarPartit(idPartit));

    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT COUNT(*) FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit)));
}

TEST_F(ControladorsDbTest, EsborrarJornada_SensePartits_EliminaLaJornada) {
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");

    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");

    CtrlEsborrarJornada^ ctrl = gcnew CtrlEsborrarJornada();
    ASSERT_NO_MANAGED_THROW(ctrl->EsborrarJornada(idJornada));

    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jornada WHERE idJornada = " + SqlTest::Q(idJornada)));
}

TEST_F(ControladorsDbTest, EsborrarJornada_AmbPartitPendent_EliminaPartitsIJornada) {
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idLocal = NewId("GT-EQUIP");
    String^ idVisitant = NewId("GT-EQUIP");
    String^ idPartit = NewId("GT-PARTIT");

    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idLocal, NewName("GT_Local"), "Futbol", idTemp);
    InsertEquip(idVisitant, NewName("GT_Visitant"), "Futbol", idTemp);
    InsertPartit(idPartit, idJornada, idLocal, idVisitant, "Pendent");

    CtrlEsborrarJornada^ ctrl = gcnew CtrlEsborrarJornada();
    ASSERT_NO_MANAGED_THROW(ctrl->EsborrarJornada(idJornada));

    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT COUNT(*) FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit)));
    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jornada WHERE idJornada = " + SqlTest::Q(idJornada)));
}

TEST_F(ControladorsDbTest, EsborrarJornada_AmbPartitFinalitzat_NoEliminaRes) {
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idLocal = NewId("GT-EQUIP");
    String^ idVisitant = NewId("GT-EQUIP");
    String^ idPartit = NewId("GT-PARTIT");

    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idLocal, NewName("GT_Local"), "Futbol", idTemp);
    InsertEquip(idVisitant, NewName("GT_Visitant"), "Futbol", idTemp);
    InsertPartit(idPartit, idJornada, idLocal, idVisitant, "Finalitzat");

    CtrlEsborrarJornada^ ctrl = gcnew CtrlEsborrarJornada();
    EXPECT_MANAGED_THROW(System::InvalidOperationException, ctrl->EsborrarJornada(idJornada));

    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit)));
    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jornada WHERE idJornada = " + SqlTest::Q(idJornada)));
}

TEST_F(ControladorsDbTest, SeguirLligaIDeixarDeSeguir) {
    String^ estudiant = NewMail("estudiant");
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    CrearUsuari("Estudiant GT", "pwd", estudiant, "Estudiant");
    InsertLliga(idLliga, nomLliga, "secret", nullptr);

    CtrlSeguirLliga^ ctrl = gcnew CtrlSeguirLliga();
    ASSERT_NO_MANAGED_THROW(ctrl->SeguirLliga(estudiant, nomLliga));

    EXPECT_TRUE(ctrl->TeLligaSeguida(estudiant));
    EXPECT_TRUE(ctrl->ObtenirIdLligaSeguida(estudiant)->Equals(idLliga));
    EXPECT_TRUE(ctrl->ObtenirNomLligaPerId(idLliga)->Equals(nomLliga));

    ASSERT_NO_MANAGED_THROW(ctrl->DeixarDeSeguir(estudiant));
    EXPECT_FALSE(ctrl->TeLligaSeguida(estudiant));
}

TEST_F(ControladorsDbTest, UnirEquipLliga_VinculaEquipALaTemporadaMesRecent) {
    String^ capita = NewMail("capita");
    String^ idEquip = NewId("GT-EQUIP");
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    String^ idTemp = NewId("GT-TEMP");

    CrearUsuari("Capita GT", "pwd", capita, "Capita");
    InsertEquip(idEquip, NewName("GT_Equip"), "Futbol", nullptr);
    AssignarEquipACapita(capita, idEquip);
    InsertLliga(idLliga, nomLliga, "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");

    CtrlUnirEquipLliga^ ctrl = gcnew CtrlUnirEquipLliga();
    EXPECT_TRUE(ctrl->ComprovarSiLligaExisteix(nomLliga)->Equals(idLliga));
    EXPECT_TRUE(ctrl->ValidarContrasenyaLliga(nomLliga, "secret"));
    ASSERT_NO_MANAGED_THROW(ctrl->VincularEquip(capita, nomLliga));

    EXPECT_TRUE(SqlTest::ScalarString("SELECT idTemporada FROM Equip WHERE idEquip = " + SqlTest::Q(idEquip))->Equals(idTemp));
}

TEST_F(ControladorsDbTest, AbandonarLliga_ReiniciaEstadistiquesIDesvinculaEquip) {
    String^ capita = NewMail("capita");
    String^ idEquip = NewId("GT-EQUIP");
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");

    CrearUsuari("Capita GT", "pwd", capita, "Capita");
    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertEquip(idEquip, NewName("GT_Equip"), "Futbol", idTemp);
    AssignarEquipACapita(capita, idEquip);
    SqlTest::Exec("UPDATE Equip SET partitsJugats=5, victories=3, punts=9 WHERE idEquip = " + SqlTest::Q(idEquip));

    CtrlAbandonarLliga^ ctrl = gcnew CtrlAbandonarLliga();
    ASSERT_NO_MANAGED_THROW(ctrl->AbandonarLliga(capita));

    EXPECT_TRUE(SqlTest::ScalarString("SELECT idTemporada FROM Equip WHERE idEquip = " + SqlTest::Q(idEquip)) == nullptr);
    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT punts FROM Equip WHERE idEquip = " + SqlTest::Q(idEquip)));
    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT victories FROM Equip WHERE idEquip = " + SqlTest::Q(idEquip)));
}

TEST_F(ControladorsDbTest, AfegirEditarEliminarJugadorIConsultarPlantilla) {
    String^ capita = NewMail("capita");
    String^ jugador = NewMail("jugador");
    String^ idEquip = NewId("GT-EQUIP");

    CrearUsuari("Capita GT", "pwd", capita, "Capita");
    CrearUsuari("Jugador GT", "pwd", jugador, "Estudiant");
    InsertEquip(idEquip, NewName("GT_Equip"), "Futbol", nullptr);
    AssignarEquipACapita(capita, idEquip);

    CtrlAfegirJugador^ afegir = gcnew CtrlAfegirJugador();
    ASSERT_NO_MANAGED_THROW(afegir->AfegirJugador(jugador, 9, "Davanter", capita));

    String^ idJugador = I(IdUsuari(jugador));
    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + idJugador + " AND idEquip = " + SqlTest::Q(idEquip)));
    EXPECT_TRUE(SqlTest::ScalarString("SELECT Tipus FROM Usuari WHERE identificador = " + idJugador)->Equals("Jugador"));

    CtrlVeurePlantilla^ plantilla = gcnew CtrlVeurePlantilla();
    DataTable^ dtPlantilla = plantilla->ObtenirPlantillaEquip(capita);
    EXPECT_EQ(1, dtPlantilla->Rows->Count);

    CtrlEditarJugador^ editar = gcnew CtrlEditarJugador();
    ASSERT_NO_MANAGED_THROW(editar->EditarJugador(capita, idJugador));
    ASSERT_NO_MANAGED_THROW(editar->ActualitzarJugador(capita, idJugador, 10, "Migcampista"));
    EXPECT_EQ(10, SqlTest::ScalarInt("SELECT dorsal FROM Jugador WHERE idJugador = " + idJugador));
    EXPECT_TRUE(SqlTest::ScalarString("SELECT posicio FROM Jugador WHERE idJugador = " + idJugador)->Equals("Migcampista"));

    String^ altre = NewMail("altre");
    CrearUsuari("Altre GT", "pwd", altre, "Estudiant");
    EXPECT_MANAGED_THROW(System::Exception, afegir->AfegirJugador(altre, 10, "Porter", capita));

    CtrlEliminarJugador^ eliminar = gcnew CtrlEliminarJugador();
    ASSERT_NO_MANAGED_THROW(eliminar->EliminarJugador(capita, idJugador));
    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + idJugador));
    EXPECT_TRUE(SqlTest::ScalarString("SELECT Tipus FROM Usuari WHERE identificador = " + idJugador)->Equals("Estudiant"));
}

TEST_F(ControladorsDbTest, AssignarJugadorAPartit_ControlaDuplicats) {
    String^ capita = NewMail("capita");
    String^ jugador = NewMail("jugador");
    String^ idLliga = NewId("GT-LLIGA");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idEquipCapita = NewId("GT-EQUIP");
    String^ idEquipRival = NewId("GT-EQUIP");
    String^ idPartit = NewId("GT-PARTIT");

    CrearUsuari("Capita GT", "pwd", capita, "Capita");
    CrearUsuari("Jugador GT", "pwd", jugador, "Estudiant");
    InsertLliga(idLliga, NewName("GT_Lliga"), "secret", nullptr);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idEquipCapita, NewName("GT_EquipCapita"), "Futbol", idTemp);
    InsertEquip(idEquipRival, NewName("GT_EquipRival"), "Futbol", idTemp);
    AssignarEquipACapita(capita, idEquipCapita);
    InsertPartit(idPartit, idJornada, idEquipCapita, idEquipRival, "Pendent");

    CtrlAfegirJugador^ afegir = gcnew CtrlAfegirJugador();
    afegir->AfegirJugador(jugador, 7, "Davanter", capita);
    String^ idJugador = I(IdUsuari(jugador));

    CtrlAssignarJugador^ assignar = gcnew CtrlAssignarJugador();
    ASSERT_NO_MANAGED_THROW(assignar->AssignarJugador(capita, idPartit, idJugador));
    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = " + SqlTest::Q(idPartit) + " AND idJugador = " + idJugador));

    EXPECT_MANAGED_THROW(System::Exception, assignar->AssignarJugador(capita, idPartit, idJugador));
}

TEST_F(ControladorsDbTest, EditarPartit_FinalitzatActualitzaMarcadorIEstadistiquesEquip) {
    String^ admin = NewMail("admin");
    String^ idLliga = NewId("GT-LLIGA");
    String^ nomLliga = NewName("GT_Lliga");
    String^ idTemp = NewId("GT-TEMP");
    String^ idJornada = NewId("GT-JORN");
    String^ idLocal = NewId("GT-EQUIP");
    String^ idVisitant = NewId("GT-EQUIP");
    String^ idPartit = NewId("GT-PARTIT");

    CrearUsuari("Admin GT", "pwd", admin, "Administrador");
    InsertLliga(idLliga, nomLliga, "secret", admin);
    InsertTemporada(idTemp, idLliga, DateTime::Now.AddDays(1), DateTime::Now.AddDays(90), "Pròxim");
    InsertJornada(idJornada, idTemp, 1, DateTime::Now.AddDays(2), DateTime::Now.AddDays(8), "Pròxim");
    InsertEquip(idLocal, NewName("GT_Local"), "Futbol", idTemp);
    InsertEquip(idVisitant, NewName("GT_Visitant"), "Futbol", idTemp);
    InsertPartit(idPartit, idJornada, idLocal, idVisitant, "Pendent");

    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();
    EXPECT_TRUE(ctrl->ValidarAdministradorLliga(nomLliga, admin));
    EXPECT_TRUE(ctrl->ObtenirNomLligaAdmin(admin)->Equals(nomLliga));
    EXPECT_EQ(1, ctrl->ObtenirPartitsPerLliga(nomLliga, admin)->Count);
    EXPECT_TRUE(ctrl->ObtenirDetallPartit(idPartit, admin)["estat"]->Equals("Pendent"));

    Nullable<DateTime> senseNovaData;
    ASSERT_NO_MANAGED_THROW(ctrl->ActualitzarPartitIStats(idPartit, "Finalitzat", 2, 1, "", admin, senseNovaData));

    EXPECT_TRUE(SqlTest::ScalarString("SELECT estat FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit))->Equals("Finalitzat"));
    EXPECT_EQ(2, SqlTest::ScalarInt("SELECT golsLocal FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit)));
    EXPECT_EQ(1, SqlTest::ScalarInt("SELECT golsVisitant FROM Partit WHERE idPartit = " + SqlTest::Q(idPartit)));
    EXPECT_EQ(3, SqlTest::ScalarInt("SELECT punts FROM Equip WHERE idEquip = " + SqlTest::Q(idLocal)));
    EXPECT_EQ(0, SqlTest::ScalarInt("SELECT punts FROM Equip WHERE idEquip = " + SqlTest::Q(idVisitant)));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
