#include "pch.h"
#include "../Playcampus/Domini/Jugador.hxx"
#include "../Playcampus/Domini/Temporada.hxx"
#include "../Playcampus/Domini/Jornada.hxx"
#include "../Playcampus/Domini/Lliga.hxx"
#include "../Playcampus/Domini/Disciplina.hxx"

using namespace Playcampus::Domini;
using namespace System;

TEST(JugadorTest, ValidarDorsalValid) {
    // PU-01 Dorsal vàlid d'un jugador (dorsal = 10 -> retorna cert)
    Jugador^ j = gcnew Jugador("1", "Nom", "Pass", DateTime::Now, "correu@test.com", "Pos", 10, 20, DateTime::Now);
    EXPECT_TRUE(j->ValidarDorsal());
}

TEST(JugadorTest, ValidarDorsalInvalid) {
    // PU-02 Dorsal invàlid d'un jugador (dorsal = 120 -> retorna fals)
    Jugador^ j = gcnew Jugador("1", "Nom", "Pass", DateTime::Now, "correu@test.com", "Pos", 120, 20, DateTime::Now);
    EXPECT_FALSE(j->ValidarDorsal());
}

TEST(JugadorTest, ValidarEdatMinimaValida) {
    // PU-03 Edat mínima vàlida (edat = 16 -> retorna cert)
    Jugador^ j = gcnew Jugador("1", "Nom", "Pass", DateTime::Now, "correu@test.com", "Pos", 10, 16, DateTime::Now);
    EXPECT_TRUE(j->ValidarEdat());
}

TEST(JugadorTest, ValidarEdatMassaBaixa) {
    // PU-04 Edat massa baixa (edat = 15 -> retorna fals)
    Jugador^ j = gcnew Jugador("1", "Nom", "Pass", DateTime::Now, "correu@test.com", "Pos", 10, 15, DateTime::Now);
    EXPECT_FALSE(j->ValidarEdat());
}

TEST(TemporadaTest, ValidarDatesCorrectes) {
    // PU-05 Temporada amb dates correctes inici anterior a fi -> retorna cert
    DateTime inici = DateTime::Now;
    DateTime fi = inici.AddMonths(1);
    Temporada^ t = gcnew Temporada(inici, fi, "EnCurs");
    EXPECT_TRUE(t->ValidarDates());
}

TEST(TemporadaTest, ValidarDatesIncorrectes) {
    // PU-06 Temporada amb dates incorrectes inici posterior a fi -> retorna fals
    DateTime inici = DateTime::Now;
    DateTime fi = inici.AddMonths(-1);
    Temporada^ t = gcnew Temporada(inici, fi, "EnCurs");
    EXPECT_FALSE(t->ValidarDates());
}

TEST(LligaTest, PotTenirJornadesEficaç) {
    // PU-07 Lliga amb prou equips per tenir jornades (quantitat = 2 -> retorna cert)
    Lliga^ l = gcnew Lliga("1", "Lliga Test", Disciplina::Futbol, "Desc", "Pass");
    EXPECT_TRUE(l->PotTenirJornades(2));
}

TEST(LligaTest, PotTenirJornadesSenseProu) {
    // PU-08 Lliga sense prou equips per tenir jornades (quantitat = 1 -> retorna fals)
    Lliga^ l = gcnew Lliga("1", "Lliga Test", Disciplina::Futbol, "Desc", "Pass");
    EXPECT_FALSE(l->PotTenirJornades(1));
}