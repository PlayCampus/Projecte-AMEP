#include "pch.h"
#include <msclr/marshal_cppstd.h>
#include <string>

#include "../Playcampus/Domini/Jugador.hxx"
#include "../Playcampus/Domini/Equip.hxx"
#include "../Playcampus/Domini/Temporada.hxx"
#include "../Playcampus/Domini/Jornada.hxx"
#include "../Playcampus/Domini/Lliga.hxx"
#include "../Playcampus/Domini/Partit.hxx"

using namespace System;
using namespace Playcampus::Domini;

namespace {
    std::string ToStdString(String^ text) {
        if (text == nullptr) {
            return "";
        }
        return msclr::interop::marshal_as<std::string>(text);
    }

    Jugador^ CrearJugadorBase(int dorsal, int edat) {
        DateTime avui = DateTime::Now;
        return gcnew Jugador(
            "1",
            "Jugador Prova",
            "pwd",
            avui.AddDays(-10),
            "jugador.prova@playcampus.test",
            "Davanter",
            dorsal,
            edat,
            avui.AddYears(-1),
            avui.AddYears(-edat)
        );
    }
}

TEST(DominiJugador, ValidarDorsalAcceptaRangValidIRebutjaLimitsInvalids) {
    Jugador^ jugador = CrearJugadorBase(10, 18);
    EXPECT_TRUE(jugador->ValidarDorsal());

    jugador->SetDorsal(99);
    EXPECT_TRUE(jugador->ValidarDorsal());

    jugador->SetDorsal(0);
    EXPECT_FALSE(jugador->ValidarDorsal());

    jugador->SetDorsal(120);
    EXPECT_FALSE(jugador->ValidarDorsal());
}

TEST(DominiJugador, ValidarEdatAplicaValorsLimit) {
    Jugador^ jugador = CrearJugadorBase(7, 16);
    EXPECT_TRUE(jugador->ValidarEdat());

    jugador->SetEdat(99);
    EXPECT_TRUE(jugador->ValidarEdat());

    jugador->SetEdat(15);
    EXPECT_FALSE(jugador->ValidarEdat());

    jugador->SetEdat(100);
    EXPECT_FALSE(jugador->ValidarEdat());
}

TEST(DominiJugador, ValidarDatesIEstadistiquesDelJugador) {
    Jugador^ jugador = CrearJugadorBase(7, 18);

    EXPECT_TRUE(jugador->ValidarAntiguitat());
    EXPECT_TRUE(jugador->ValidarDataNaixement());
    EXPECT_TRUE(jugador->ValidarEstadistiques());

    jugador->SetAntiguitat(DateTime::Now.AddDays(1));
    EXPECT_FALSE(jugador->ValidarAntiguitat());

    jugador->SetDataNaixement(DateTime::Now.AddDays(1));
    EXPECT_FALSE(jugador->ValidarDataNaixement());

    jugador->SetAnotacions(-1);
    EXPECT_FALSE(jugador->ValidarEstadistiques());
}

TEST(DominiEquip, ValidarDataFundacioRebutjaDatesFutures) {
    Equip^ equip = gcnew Equip("Equip Prova", DateTime::Now.AddYears(-1), Disciplina::Futbol);
    EXPECT_TRUE(equip->ValidarDataFundacio());

    equip->SetDataFundacio(DateTime::Now.AddDays(1));
    EXPECT_FALSE(equip->ValidarDataFundacio());
}

TEST(DominiTemporada, ValidarDatesComprovaOrdreTemporal) {
    Temporada^ temporada = gcnew Temporada(DateTime(2026, 1, 1), DateTime(2026, 6, 1), "Proxim");
    EXPECT_TRUE(temporada->ValidarDates());

    temporada->SetDataInici(DateTime(2026, 6, 1));
    temporada->SetDataFi(DateTime(2026, 6, 1));
    EXPECT_FALSE(temporada->ValidarDates());

    temporada->SetDataInici(DateTime(2026, 7, 1));
    temporada->SetDataFi(DateTime(2026, 6, 1));
    EXPECT_FALSE(temporada->ValidarDates());
}

TEST(DominiJornada, ValidarDatesINumero) {
    Jornada^ jornada = gcnew Jornada("J-TEST", 1, DateTime(2026, 3, 1), DateTime(2026, 3, 7));
    EXPECT_TRUE(jornada->ValidarDates());
    EXPECT_TRUE(jornada->ValidarNumero());

    jornada->SetNumero(0);
    EXPECT_FALSE(jornada->ValidarNumero());

    jornada->SetNumero(2);
    jornada->SetDataInici(DateTime(2026, 3, 10));
    jornada->SetDataFi(DateTime(2026, 3, 7));
    EXPECT_FALSE(jornada->ValidarDates());
}

TEST(DominiLliga, ValidarActivacioIJornadesSegonsNombreEquips) {
    Lliga^ lliga = gcnew Lliga("L-TEST", "Lliga Prova", Disciplina::Futbol, "Descripcio", "secret");

    EXPECT_FALSE(lliga->EsPotActivar(0));
    EXPECT_TRUE(lliga->EsPotActivar(1));

    EXPECT_FALSE(lliga->PotTenirJornades(1));
    EXPECT_TRUE(lliga->PotTenirJornades(2));
}

TEST(DominiPartit, SetEstatISetResultatActualitzenValors) {
    DateTime dataHora = DateTime(2026, 4, 10, 18, 30, 0);
    Partit^ partit = gcnew Partit("P-TEST", dataHora, "Pista 1", "Pendent", 0, 0, "J-TEST");

    EXPECT_EQ(std::string("P-TEST"), ToStdString(partit->GetIdentificador()));
    EXPECT_EQ(std::string("Pendent"), ToStdString(partit->GetEstat()));
    EXPECT_EQ(0, partit->GetGolsLocal());
    EXPECT_EQ(0, partit->GetGolsVisitant());

    partit->SetEstat("Finalitzat");
    partit->SetResultat(3, 2);

    EXPECT_EQ(std::string("Finalitzat"), ToStdString(partit->GetEstat()));
    EXPECT_EQ(3, partit->GetGolsLocal());
    EXPECT_EQ(2, partit->GetGolsVisitant());
    EXPECT_EQ(std::string("J-TEST"), ToStdString(partit->GetIdJornada()));
}
