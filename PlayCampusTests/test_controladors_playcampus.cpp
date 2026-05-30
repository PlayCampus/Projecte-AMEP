#include "pch.h"
#include "TestSupport.h"

using namespace PlayCampusTests;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace Playcampus::Domini;

TEST(ControladorRegistrarUsuari, RebutjaCorreuInvalid) {
    CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
    EXPECT_MANAGED_EXCEPTION(ctrl->CrearUsuari("Usuari Invalid", "1234", DateTime::Now, "correu-invalid", "Estudiant", ""));
}

TEST(ControladorRegistrarUsuari, RebutjaDataFutura) {
    CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
    String^ correu = "gtest_data_futura_" + Guid::NewGuid().ToString("N")->Substring(0, 8) + "@playcampus.test";
    try {
        EXPECT_MANAGED_EXCEPTION(ctrl->CrearUsuari("Usuari Data Futura", "1234", DateTime::Now.AddDays(3), correu, "Estudiant", ""));
    }
    finally {
        NetejarUsuariPerCorreu(correu);
    }
}

TEST(ControladorRegistrarUsuari, CreaUsuariIRebutjaDuplicat) {
    CtrlRegistrarUsuari^ ctrl = gcnew CtrlRegistrarUsuari();
    String^ correu = "gtest_duplicat_" + Guid::NewGuid().ToString("N")->Substring(0, 8) + "@playcampus.test";
    try {
        ctrl->CrearUsuari("Usuari Duplicat", "1234", DateTime::Now.AddDays(-1), correu, "Estudiant", "");
        EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Usuari WHERE correu_electronic = '" + EscaparSql(correu) + "'"));
        EXPECT_MANAGED_EXCEPTION(ctrl->CrearUsuari("Usuari Duplicat 2", "1234", DateTime::Now.AddDays(-1), correu, "Estudiant", ""));
    }
    finally {
        NetejarUsuariPerCorreu(correu);
    }
}

TEST_F(FixtureControladors, IniciSessioCorrecteIRolCorrecte) {
    CtrlIniciSessio^ ctrl = gcnew CtrlIniciSessio();

    EXPECT_TRUE(ctrl->IniciarSessio(escenari->adminEmail, "pwd-admin"));
    EXPECT_EQ("Administrador", ToStd(ctrl->ObtenirTipusUsuari(escenari->adminEmail)));
}

TEST_F(FixtureControladors, IniciSessioIncorrecteAmbContrasenyaIncorrecta) {
    CtrlIniciSessio^ ctrl = gcnew CtrlIniciSessio();

    EXPECT_FALSE(ctrl->IniciarSessio(escenari->adminEmail, "contrasenya-malament"));
}

TEST_F(FixtureControladors, IniciSessioDetectaCapitaAmbEquip) {
    CtrlIniciSessio^ ctrl = gcnew CtrlIniciSessio();

    EXPECT_TRUE(ctrl->CapitaTeEquip(escenari->capitaEmail));
    EXPECT_EQ(ToStd(escenari->equipLocalId), ToStd(ctrl->ObtenirIdEquipDeCapita(escenari->capitaEmail)));
}

TEST_F(FixtureControladors, TancarSessioNoFaPeta) {
    CtrlTancarSessio^ ctrl = gcnew CtrlTancarSessio();

    ctrl->TancarSessio();
    SUCCEED();
}

TEST_F(FixtureControladors, EnregistrarEquipRebutjaUsuariNoCapita) {
    CtrlEnregistrarEquip^ ctrl = gcnew CtrlEnregistrarEquip();
    String^ idEquip = NouCodi("GTEQNO");

    EXPECT_MANAGED_EXCEPTION_TYPE(
        ctrl->EnregistrarEquip(idEquip, "Equip No Permes", DateTime::Now.AddYears(-1), "Futbol", "Estudiant", escenari->estudiantEmail),
        UnauthorizedAccessException
    );
}

TEST_F(FixtureControladors, EnregistrarEquipAssignaEquipAlCapita) {
    int count = EscalarInt("SELECT COUNT(*) FROM Capita WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND identificador = " + Convert::ToString(IdUsuariPerCorreu(escenari->capitaEmail)));

    EXPECT_EQ(1, count);
}

TEST_F(FixtureControladors, EnregistrarEquipRebutjaSegonEquipDelMateixCapita) {
    CtrlEnregistrarEquip^ ctrl = gcnew CtrlEnregistrarEquip();
    String^ segonEquipId = NouCodi("GTEQ2");

    try {
        EXPECT_MANAGED_EXCEPTION(
            ctrl->EnregistrarEquip(segonEquipId, "GTest Segon Equip " + escenari->tag, DateTime::Now.AddYears(-1), "Futbol", "Capita", escenari->capitaEmail)
        );
        EXPECT_EQ(0, EscalarInt("SELECT COUNT(*) FROM Equip WHERE idEquip = '" + EscaparSql(segonEquipId) + "'"));
        EXPECT_EQ(ToStd(escenari->equipLocalId), ToStd(EscalarString("SELECT idEquip FROM Capita WHERE identificador = " + Convert::ToString(IdUsuariPerCorreu(escenari->capitaEmail)))));
    }
    finally {
        ExecutarSql("UPDATE Capita SET idEquip = '" + EscaparSql(escenari->equipLocalId) + "' WHERE identificador = " + Convert::ToString(IdUsuariPerCorreu(escenari->capitaEmail)));
        ExecutarSql("DELETE FROM Equip WHERE idEquip = '" + EscaparSql(segonEquipId) + "'");
    }
}

TEST_F(FixtureControladors, CrearLligaAdministradorCorrecte) {
    CtrlCrearLliga^ ctrl = gcnew CtrlCrearLliga();

    EXPECT_TRUE(ctrl->ExisteixLliga(escenari->lligaNom));
    EXPECT_TRUE(ctrl->TeLligaActiva(escenari->adminEmail));
}

TEST_F(FixtureControladors, CrearLligaRebutjaNoAdministrador) {
    CtrlCrearLliga^ ctrl = gcnew CtrlCrearLliga();
    String^ idLliga = NouCodi("GTLNO");

    EXPECT_MANAGED_EXCEPTION_TYPE(
        ctrl->CrearLliga(idLliga, "Lliga No Permesa " + escenari->tag, Disciplina::Futbol, "desc", "secret", "Capita", escenari->capitaEmail),
        UnauthorizedAccessException
    );
}

TEST_F(FixtureControladors, CrearTemporadaAssociadaALliga) {
    EXPECT_FALSE(String::IsNullOrWhiteSpace(escenari->temporadaId));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Temporada WHERE idTemporada = '" + EscaparSql(escenari->temporadaId) + "' AND idLliga = '" + EscaparSql(escenari->lligaId) + "'"));
}

TEST_F(FixtureControladors, CrearTemporadaRebutjaAdminIncorrecte) {
    CtrlCrearTemporada^ ctrl = gcnew CtrlCrearTemporada();

    EXPECT_MANAGED_EXCEPTION(ctrl->CrearTemporada(DateTime::Now, DateTime::Now.AddDays(10), escenari->adminAltEmail));
}

TEST_F(FixtureControladors, CrearTemporadaSolapadaAmbTemporadaFinalitzadaCopiaEquips) {
    CtrlCrearTemporada^ ctrl = gcnew CtrlCrearTemporada();
    ExecutarSql("UPDATE EquipTemporada SET victories = 4, punts = 12, golsAFavor = 15, golsEnContra = 4, diferenciaGols = 11 WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");
    ExecutarSql("UPDATE Temporada SET estat = 'Finalitzat' WHERE idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");

    ctrl->CrearTemporada(DateTime::Now.AddDays(-1), DateTime::Now.AddDays(45), escenari->adminEmail);
    String^ novaTemporadaId = EscalarString("SELECT idTemporada FROM Temporada WHERE idLliga = '" + EscaparSql(escenari->lligaId) + "' AND idTemporada <> '" + EscaparSql(escenari->temporadaId) + "' ORDER BY dataInici DESC LIMIT 1");

    EXPECT_FALSE(String::IsNullOrWhiteSpace(novaTemporadaId));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(novaTemporadaId) + "'"));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipVisitantId) + "' AND idTemporada = '" + EscaparSql(novaTemporadaId) + "'"));
    EXPECT_EQ(0, EscalarInt("SELECT punts FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(novaTemporadaId) + "'"));
    EXPECT_EQ(12, EscalarInt("SELECT punts FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
}

TEST_F(FixtureControladors, RetirarTemporadaAssignaEquipsALaSeguentIManteHistorial) {
    CtrlCrearTemporada^ ctrlCrear = gcnew CtrlCrearTemporada();
    ctrlCrear->CrearTemporada(DateTime::Now.AddDays(70), DateTime::Now.AddDays(130), escenari->adminEmail);
    String^ temporadaSeguentId = EscalarString("SELECT idTemporada FROM Temporada WHERE idLliga = '" + EscaparSql(escenari->lligaId) + "' AND idTemporada <> '" + EscaparSql(escenari->temporadaId) + "' ORDER BY dataInici ASC LIMIT 1");
    EXPECT_FALSE(String::IsNullOrWhiteSpace(temporadaSeguentId));

    ExecutarSql("UPDATE EquipTemporada SET partitsJugats = 1, victories = 1, punts = 3, golsAFavor = 2, golsEnContra = 1, diferenciaGols = 1 WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");

    CtrlRetirarTemporada^ ctrlRetirar = gcnew CtrlRetirarTemporada();
    ctrlRetirar->RetirarTemporada(escenari->adminEmail);

    EXPECT_EQ("Finalitzat", ToStd(EscalarString("SELECT estat FROM Temporada WHERE idTemporada = '" + EscaparSql(escenari->temporadaId) + "'")));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(temporadaSeguentId) + "'"));
    EXPECT_EQ(0, EscalarInt("SELECT punts FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(temporadaSeguentId) + "'"));
    EXPECT_EQ(3, EscalarInt("SELECT punts FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
}

TEST_F(FixtureControladors, CrearJornadaAssociadaATemporada) {
    EXPECT_FALSE(String::IsNullOrWhiteSpace(escenari->jornadaId));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Jornada WHERE idJornada = '" + EscaparSql(escenari->jornadaId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
}

TEST_F(FixtureControladors, CrearPartitCorrecte) {
    EXPECT_FALSE(String::IsNullOrWhiteSpace(escenari->partitId));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Partit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "' AND idEquipLocal = '" + EscaparSql(escenari->equipLocalId) + "' AND idEquipVisitant = '" + EscaparSql(escenari->equipVisitantId) + "'"));
}

TEST_F(FixtureControladors, CrearPartitRebutjaMateixEquip) {
    CtrlCrearPartit^ ctrl = gcnew CtrlCrearPartit();

    EXPECT_MANAGED_EXCEPTION_TYPE(
        ctrl->CrearPartit(DateTime::Now.AddDays(3), "Pista", escenari->equipLocalNom, escenari->equipLocalNom, escenari->jornadaId, "Administrador"),
        ArgumentException
    );
}

TEST_F(FixtureControladors, CrearPartitRebutjaNoAdministrador) {
    CtrlCrearPartit^ ctrl = gcnew CtrlCrearPartit();

    EXPECT_MANAGED_EXCEPTION_TYPE(
        ctrl->CrearPartit(DateTime::Now.AddDays(3), "Pista", escenari->equipLocalNom, escenari->equipVisitantNom, escenari->jornadaId, "Capita"),
        UnauthorizedAccessException
    );
}

TEST_F(FixtureControladors, UnirEquipLligaValidaContrasenyaIVinculaEquip) {
    CtrlUnirEquipLliga^ ctrl = gcnew CtrlUnirEquipLliga();
    ExecutarSql("DELETE FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");

    EXPECT_TRUE(ctrl->ValidarContrasenyaLliga(escenari->lligaNom, "secret"));
    String^ resposta = ctrl->VincularEquip(escenari->capitaEmail, escenari->lligaNom);

    EXPECT_TRUE(resposta->Contains("ha sigut enregistrat"));
    EXPECT_EQ(ToStd(escenari->temporadaId), ToStd(EscalarString("SELECT idTemporada FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'")));
}

TEST_F(FixtureControladors, AfegirJugadorCreaJugadorIVinculaEquip) {
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + escenari->jugadorId + " AND idEquip = '" + EscaparSql(escenari->equipLocalId) + "'"));
    EXPECT_EQ("Jugador", ToStd(EscalarString("SELECT Tipus FROM Usuari WHERE identificador = " + escenari->jugadorId)));
}

TEST_F(FixtureControladors, AfegirJugadorRebutjaDorsalDuplicat) {
    CtrlAfegirJugador^ ctrl = gcnew CtrlAfegirJugador();

    EXPECT_MANAGED_EXCEPTION(ctrl->AfegirJugador(escenari->estudiant2Email, 10, "Porter", escenari->capitaEmail, System::DateTime(2004, 1, 1)));
}

TEST_F(FixtureControladors, AfegirJugadorNouCorrecte) {
    String^ extra = RegistrarEstudiantExtra(escenari);
    CtrlAfegirJugador^ ctrl = gcnew CtrlAfegirJugador();

    String^ missatge = ctrl->AfegirJugador(extra, 88, "Reserva", escenari->capitaEmail, System::DateTime(2004, 1, 1));
    int idExtra = IdUsuariPerCorreu(extra);

    EXPECT_EQ("Jugador afegit correctament!", ToStd(missatge));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + Convert::ToString(idExtra) + " AND dorsal = 88 AND idEquip = '" + EscaparSql(escenari->equipLocalId) + "'"));
}

TEST_F(FixtureControladors, VeurePlantillaRetornaJugadorsDelCapita) {
    CtrlVeurePlantilla^ ctrl = gcnew CtrlVeurePlantilla();

    DataTable^ plantilla = ctrl->ObtenirPlantillaEquip(escenari->capitaEmail);

    bool plantillaNoNull = plantilla != nullptr;
    EXPECT_TRUE(plantillaNoNull);
    if (plantillaNoNull) {
        EXPECT_GE(plantilla->Rows->Count, 2);
    }
}

TEST_F(FixtureControladors, VeurePlantillaRebutjaUsuariNoCapita) {
    CtrlVeurePlantilla^ ctrl = gcnew CtrlVeurePlantilla();

    EXPECT_MANAGED_EXCEPTION(ctrl->ObtenirPlantillaEquip(escenari->adminEmail));
}

TEST_F(FixtureControladors, EditarJugadorValidaIActualitzaJugadorPropi) {
    CtrlEditarJugador^ ctrl = gcnew CtrlEditarJugador();

    EXPECT_EQ("Validació d'edició realitzada correctament.", ToStd(ctrl->EditarJugador(escenari->capitaEmail, escenari->jugadorId)));
    EXPECT_EQ("Jugador actualitzat correctament.", ToStd(ctrl->ActualitzarJugador(escenari->capitaEmail, escenari->jugadorId, 55, "Central")));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + escenari->jugadorId + " AND dorsal = 55 AND posicio = 'Central'"));
}

TEST_F(FixtureControladors, EditarJugadorRebutjaJugadorDunAltreEquip) {
    CtrlEditarJugador^ ctrl = gcnew CtrlEditarJugador();

    EXPECT_MANAGED_EXCEPTION(ctrl->EditarJugador(escenari->capitaEmail, escenari->jugadorVisitantId));
}

TEST_F(FixtureControladors, EliminarJugadorExpulsaJugadorDelEquip) {
    CtrlEliminarJugador^ ctrl = gcnew CtrlEliminarJugador();

    String^ resposta = ctrl->EliminarJugador(escenari->capitaEmail, escenari->jugador2Id);

    EXPECT_TRUE(resposta->Contains("Jugador expulsat correctament"));
    EXPECT_EQ(0, EscalarInt("SELECT COUNT(*) FROM Jugador WHERE idJugador = " + escenari->jugador2Id + " AND idEquip = '" + EscaparSql(escenari->equipLocalId) + "'"));
}

TEST_F(FixtureControladors, EliminarJugadorRebutjaJugadorDunAltreEquip) {
    CtrlEliminarJugador^ ctrl = gcnew CtrlEliminarJugador();

    EXPECT_MANAGED_EXCEPTION(ctrl->EliminarJugador(escenari->capitaEmail, escenari->jugadorVisitantId));
}

TEST_F(FixtureControladors, AssignarJugadorMostraPartitsIJugadorsDisponibles) {
    CtrlAssignarJugador^ ctrl = gcnew CtrlAssignarJugador();

    List<Dictionary<String^, String^>^>^ partits = ctrl->ObtenirPartitsDisponibles(escenari->capitaEmail);
    List<Dictionary<String^, String^>^>^ jugadors = ctrl->ObtenirJugadorsEquip(escenari->capitaEmail);

    bool partitsNoNull = partits != nullptr;
    bool jugadorsNoNull = jugadors != nullptr;
    EXPECT_TRUE(partitsNoNull);
    EXPECT_TRUE(jugadorsNoNull);
    if (partitsNoNull) {
        EXPECT_GE(partits->Count, 1);
    }
    if (jugadorsNoNull) {
        EXPECT_GE(jugadors->Count, 2);
    }
}

TEST_F(FixtureControladors, AssignarJugadorCorrecte) {
    CtrlAssignarJugador^ ctrl = gcnew CtrlAssignarJugador();

    String^ resposta = ctrl->AssignarJugador(escenari->capitaEmail, escenari->partitId, escenari->jugadorId);

    EXPECT_EQ("Jugador assignat correctament al partit.", ToStd(resposta));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM AssignacioJugadorPartit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "' AND idJugador = " + escenari->jugadorId));
}

TEST_F(FixtureControladors, AssignarJugadorRebutjaDuplicat) {
    CtrlAssignarJugador^ ctrl = gcnew CtrlAssignarJugador();

    ctrl->AssignarJugador(escenari->capitaEmail, escenari->partitId, escenari->jugadorId);
    EXPECT_MANAGED_EXCEPTION(ctrl->AssignarJugador(escenari->capitaEmail, escenari->partitId, escenari->jugadorId));
}

TEST_F(FixtureControladors, AssignarJugadorRebutjaPartitFinalitzat) {
    CtrlAssignarJugador^ ctrl = gcnew CtrlAssignarJugador();
    ExecutarSql("UPDATE Partit SET estat = 'Finalitzat' WHERE idPartit = '" + EscaparSql(escenari->partitId) + "'");

    EXPECT_MANAGED_EXCEPTION(ctrl->AssignarJugador(escenari->capitaEmail, escenari->partitId, escenari->jugadorId));
}

TEST_F(FixtureControladors, AssignarJugadorRebutjaJugadorAltreEquip) {
    CtrlAssignarJugador^ ctrl = gcnew CtrlAssignarJugador();

    EXPECT_MANAGED_EXCEPTION(ctrl->AssignarJugador(escenari->capitaEmail, escenari->partitId, escenari->jugadorVisitantId));
}

TEST_F(FixtureControladors, ConvocarJugadorIConfirmarAssistencia) {
    CtlrConvocarJugadors^ ctrl = gcnew CtlrConvocarJugadors();

    ctrl->ActualitzarConvocatoria(escenari->partitId, escenari->jugadorId, Nullable<bool>(true));
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM ConvocatoriaPartit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "' AND idJugador = " + escenari->jugadorId + " AND convocat = 1 AND confirmat IS NULL"));

    Dictionary<String^, String^>^ avis = ctrl->ObtenirAvisPendent(escenari->estudiantEmail);
    bool avisNoNull = avis != nullptr;
    EXPECT_TRUE(avisNoNull);
    if (avisNoNull) {
        EXPECT_EQ("convocat", ToStd(avis["tipus"]));
    }

    ctrl->ConfirmarAssistencia(escenari->partitId, escenari->jugadorId, true);
    EXPECT_EQ(1, EscalarInt("SELECT COUNT(*) FROM ConvocatoriaPartit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "' AND idJugador = " + escenari->jugadorId + " AND confirmat = 1"));
}

TEST_F(FixtureControladors, ConvocarJugadorCarregaEstatConvocatoria) {
    CtlrConvocarJugadors^ ctrl = gcnew CtlrConvocarJugadors();

    List<Dictionary<String^, String^>^>^ estat = ctrl->ObtenirEstatConvocatoria(escenari->partitId, escenari->equipLocalId);

    bool estatNoNull = estat != nullptr;
    EXPECT_TRUE(estatNoNull);
    if (estatNoNull) {
        EXPECT_GE(estat->Count, 2);
    }
}

TEST_F(FixtureControladors, EditarPartitValidaAdministrador) {
    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();

    EXPECT_TRUE(ctrl->ValidarAdministradorLliga(escenari->lligaNom, escenari->adminEmail));
    EXPECT_FALSE(ctrl->ValidarAdministradorLliga(escenari->lligaNom, escenari->adminAltEmail));
    EXPECT_EQ(ToStd(escenari->lligaNom), ToStd(ctrl->ObtenirNomLligaAdmin(escenari->adminEmail)));
}

TEST_F(FixtureControladors, EditarPartitObteDetallCorrecte) {
    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();

    Dictionary<String^, String^>^ detall = ctrl->ObtenirDetallPartit(escenari->partitId, escenari->adminEmail);

    bool detallNoNull = detall != nullptr;
    EXPECT_TRUE(detallNoNull);
    if (detallNoNull) {
        EXPECT_EQ(ToStd(escenari->partitId), ToStd(detall["idPartit"]));
        EXPECT_EQ("Futbol", ToStd(detall["disciplina"]));
    }
}

TEST_F(FixtureControladors, EditarPartitRebutjaAdministradorIncorrecte) {
    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();

    EXPECT_MANAGED_EXCEPTION_TYPE(ctrl->ObtenirDetallPartit(escenari->partitId, escenari->adminAltEmail), UnauthorizedAccessException);
}

TEST_F(FixtureControladors, EditarPartitActualitzaResultatIEstadistiquesEquip) {
    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();

    ctrl->ActualitzarPartitIStats(escenari->partitId, "Finalitzat", 2, 1, "", escenari->adminEmail, Nullable<DateTime>());

    EXPECT_EQ("Finalitzat", ToStd(EscalarString("SELECT estat FROM Partit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "'")));
    EXPECT_EQ(2, EscalarInt("SELECT golsLocal FROM Partit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "'"));
    EXPECT_EQ(1, EscalarInt("SELECT victories FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
    EXPECT_EQ(3, EscalarInt("SELECT punts FROM EquipTemporada WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'"));
}

TEST_F(FixtureControladors, EditarPartitRebutjaResultatNegatiu) {
    CtrlEditarPartit^ ctrl = gcnew CtrlEditarPartit();

    EXPECT_MANAGED_EXCEPTION_TYPE(ctrl->ActualitzarPartitIStats(escenari->partitId, "Finalitzat", -1, 1, "", escenari->adminEmail, Nullable<DateTime>()), ArgumentException);
}

TEST_F(FixtureControladors, EsborrarPartitEliminaPartit) {
    CtrlEsborrarPartit^ ctrl = gcnew CtrlEsborrarPartit();

    ctrl->EsborrarPartit(escenari->partitId);

    EXPECT_EQ(0, EscalarInt("SELECT COUNT(*) FROM Partit WHERE idPartit = '" + EscaparSql(escenari->partitId) + "'"));
    escenari->partitId = nullptr;
}

TEST_F(FixtureControladors, EsborrarPartitObtePartitsPerJornada) {
    CtrlEsborrarPartit^ ctrl = gcnew CtrlEsborrarPartit();

    List<Dictionary<String^, String^>^>^ partits = ctrl->ObtenirPartitsPerJornada(escenari->jornadaId);

    bool partitsNoNull = partits != nullptr;
    EXPECT_TRUE(partitsNoNull);
    if (partitsNoNull) {
        EXPECT_GE(partits->Count, 1);
    }
}

TEST_F(FixtureControladors, ConsultesRetornenDadesBasiques) {
    CtrlConsultes^ ctrl = gcnew CtrlConsultes();

    DataTable^ programacio = ctrl->ObtenirProgramacioPartits();
    DataTable^ calendari = ctrl->ObtenirCalendariCompletLligaPerId(escenari->lligaId);

    bool programacioNoNull = programacio != nullptr;
    bool calendariNoNull = calendari != nullptr;
    EXPECT_TRUE(programacioNoNull);
    EXPECT_TRUE(calendariNoNull);
    EXPECT_EQ(ToStd(escenari->lligaNom), ToStd(ctrl->ObtenirNomLligaAdministrador(escenari->adminEmail)));
}

TEST_F(FixtureControladors, ConsultesRebutgenUsuariBuitPerTelefons) {
    CtrlConsultes^ ctrl = gcnew CtrlConsultes();

    EXPECT_MANAGED_EXCEPTION_TYPE(ctrl->ObtenirTelefonsContacte(""), ArgumentException);
}

TEST_F(FixtureControladors, EstadistiquesLligaRetornenClassificacioDesDEquipTemporada) {
    CtrlVeureEstadistiquesLliga^ ctrl = gcnew CtrlVeureEstadistiquesLliga();
    ExecutarSql("UPDATE EquipTemporada SET partitsJugats = 1, victories = 1, punts = 3, golsAFavor = 2, golsEnContra = 1, diferenciaGols = 1 WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");

    EXPECT_EQ(ToStd(escenari->lligaId), ToStd(ctrl->ObtenirIdLligaPerNom(escenari->lligaNom)));
    DataTable^ classificacio = ctrl->ObtenirClassificacioLligaTemporada(escenari->lligaId, escenari->temporadaId);

    bool classificacioNoNull = classificacio != nullptr;
    EXPECT_TRUE(classificacioNoNull);
    if (classificacioNoNull) {
        EXPECT_TRUE(classificacio->Columns->Contains("Equip"));
        EXPECT_TRUE(classificacio->Columns->Contains("Punts"));
        EXPECT_GE(classificacio->Rows->Count, 2);
        EXPECT_EQ(3, Convert::ToInt32(classificacio->Rows[0]["Punts"]));
    }
}

TEST_F(FixtureControladors, EstadistiquesEquipRetornenEquipTemporadaIEstadistiques) {
    CtrlVeureEstadistiquesEquip^ ctrl = gcnew CtrlVeureEstadistiquesEquip();
    ExecutarSql("UPDATE EquipTemporada SET partitsJugats = 2, victories = 1, empats = 1, punts = 4, golsAFavor = 5, golsEnContra = 3, diferenciaGols = 2 WHERE idEquip = '" + EscaparSql(escenari->equipLocalId) + "' AND idTemporada = '" + EscaparSql(escenari->temporadaId) + "'");

    EXPECT_TRUE(ctrl->ExisteixEquip(escenari->equipLocalNom));
    DataTable^ lligues = ctrl->ObtenirLliguesEquip(escenari->equipLocalNom);
    DataTable^ temporades = ctrl->ObtenirTemporadesEquipLliga(escenari->equipLocalNom, escenari->lligaId);
    DataTable^ estadistiques = ctrl->ObtenirEstadistiquesEquip(escenari->equipLocalNom, escenari->lligaId, escenari->temporadaId);

    bool lliguesNoNull = lligues != nullptr;
    bool temporadesNoNull = temporades != nullptr;
    bool estadistiquesNoNull = estadistiques != nullptr;
    EXPECT_TRUE(lliguesNoNull);
    EXPECT_TRUE(temporadesNoNull);
    EXPECT_TRUE(estadistiquesNoNull);
    if (estadistiquesNoNull) {
        EXPECT_TRUE(estadistiques->Columns->Contains("Punts"));
        EXPECT_GE(estadistiques->Rows->Count, 1);
        EXPECT_EQ(4, Convert::ToInt32(estadistiques->Rows[0]["Punts"]));
    }
}

TEST_F(FixtureControladors, EstadistiquesJugadorRetornenJugador) {
    CtrlVeureEstadistiquesJugadors^ ctrl = gcnew CtrlVeureEstadistiquesJugadors();

    DataTable^ estadistiques = ctrl->ObtenirEstadistiquesJugador(escenari->jugadorId);

    bool estadistiquesNoNull = estadistiques != nullptr;
    EXPECT_TRUE(estadistiquesNoNull);
    if (estadistiquesNoNull) {
        EXPECT_GE(estadistiques->Rows->Count, 1);
    }
}

TEST_F(FixtureControladors, EstadistiquesPartitRetornaPartitsFinalitzats) {
    CtrlEditarPartit^ ctrlEditar = gcnew CtrlEditarPartit();
    ctrlEditar->ActualitzarPartitIStats(escenari->partitId, "Finalitzat", 2, 1, "", escenari->adminEmail, Nullable<DateTime>());

    CtrlEstadistiquesPartit^ ctrl = gcnew CtrlEstadistiquesPartit();
    DataTable^ partits = ctrl->ObtenirPartitsFinalitzats(escenari->temporadaId);

    bool partitsNoNull = partits != nullptr;
    EXPECT_TRUE(partitsNoNull);
    if (partitsNoNull) {
        EXPECT_GE(partits->Rows->Count, 1);
    }
}
