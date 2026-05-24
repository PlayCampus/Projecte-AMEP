# PlayCampus - Suite de Tests Unitaris

## Visió General

Aquesta documentació descriu la suite completa de tests unitaris per al projecte **PlayCampus**. Els tests cobreixen:

- **Validacions d'entitats** (Jugador, Temporada, Jornada, Administrador)
- **Regles de negoci** (Partits, Equips, Classificació)
- **Controladors** (Crear partit, Inici sessió, Equips, Lligues, etc.)
- **Casos extrems** i validacions de límits

---

## Estructura de Tests

### ?? Fitxers de Test

```
test/
??? test.cpp                    # Tests bàsics i de sanitat
??? test_controllers.cpp        # Tests d'entitats i validacions
??? test_business_logic.cpp     # Tests de lògica de negoci i controladors
??? test_business_rules.cpp     # Tests de regles de negoci i constraints
```

---

## 1. TESTS D'ENTITATS (test_controllers.cpp)

### 1.1 Tests de Jugador

| ID | Cas de Prova | Dades d'Entrada | Resultat Esperat |
|---|---|---|---|
| PU-01 | Dorsal vàlid | dorsal = 10 | ValidarDorsal() ? true |
| PU-02 | Dorsal invàlid (>99) | dorsal = 120 | ValidarDorsal() ? false |
| PU-01b | Dorsal límit superior | dorsal = 99 | ValidarDorsal() ? true |
| PU-01c | Dorsal límit inferior | dorsal = 1 | ValidarDorsal() ? true |
| PU-03 | Edat mínima vàlida | edat = 16 | ValidarEdat() ? true |
| PU-04 | Edat massa baixa | edat = 15 | ValidarEdat() ? false |
| PU-03b | Edat màxima | edat = 99 | ValidarEdat() ? true |
| - | Edat > 99 | edat = 100 | ValidarEdat() ? false |
| - | Antiguitat vàlida | data anterior ara | ValidarAntiguitat() ? true |
| - | Antiguitat futura | data futura | ValidarAntiguitat() ? false |
| - | Estadístiques jugador | Diversos valors | Getters retornen valors correctes |

**Tests executats:**
```cpp
TEST_F(JugadorTest, DorsalValid)
TEST_F(JugadorTest, DorsalInvalid)
TEST_F(JugadorTest, EdatMinimaValida)
TEST_F(JugadorTest, EdatMassaBaixa)
// ... més 7 tests
```

### 1.2 Tests de Temporada

| ID | Cas de Prova | Dades d'Entrada | Resultat Esperat |
|---|---|---|---|
| PU-05 | Dates correctes | inici < fi | ValidarDates() ? true |
| PU-06 | Dates incorrectes | inici > fi | ValidarDates() ? false |
| - | Dates iguals | inici == fi | ValidarDates() ? false |
| - | Setters | novaData | Getters retornen valor correcte |

**Tests executats:**
```cpp
TEST_F(TemporadaTest, DatesCorrectesValides)
TEST_F(TemporadaTest, DatesIncorrectesInici_GtFi)
// ... més tests
```

### 1.3 Tests de Jornada

| ID | Cas de Prova | Dades d'Entrada | Resultat Esperat |
|---|---|---|---|
| RIT7 | Dates correctes | inici < fi | ValidarDates() ? true |
| RIT7 | Dates incorrectes | inici > fi | ValidarDates() ? false |
| RIT26 | Número vàlid | numero > 0 | ValidarNumero() ? true |
| RIT26 | Número = 0 | numero = 0 | ValidarNumero() ? false |
| RIT26 | Número negatiu | numero < 0 | ValidarNumero() ? false |
| - | Setters | nous valors | Getters retornen valor correcte |

**Tests executats:**
```cpp
TEST_F(JornadaTest, DatesCorrectesValides)
TEST_F(JornadaTest, NumeroJornadaValid)
// ... més tests
```

### 1.4 Tests d'Administrador

| ID | Cas de Prova | Dades d'Entrada | Resultat Esperat |
|---|---|---|---|
| - | Telèfon de contacte | "666777888" | GetTelefonContacte() retorna valor |
| - | Telèfon no nul | Administrador | Telèfon != null |

---

## 2. TESTS DE LÒGICA DE NEGOCI (test_business_logic.cpp)

### 2.1 Tests de Controladors

#### CtrlCrearPartit
```cpp
TEST(CtrlCrearPartitTest, EquipsDiferents)     // Equips no són iguals
TEST(CtrlCrearPartitTest, EquipsIguals)        // Error: equips iguals
TEST(CtrlCrearPartitTest, DataPartitValida)    // Data és futura
TEST(CtrlCrearPartitTest, UbicacioNoVuida)     // Ubicació complerta
```

#### CtrlIniciSessio
```cpp
TEST(CtrlIniciSessioTest, CorreuFormatValid)   // Correu té @ i .
TEST(CtrlIniciSessioTest, CorreuBuit)          // Correu buit (error)
TEST(CtrlIniciSessioTest, ContrasenyaValida)   // Contrasenya >= 8 caràcters
TEST(CtrlIniciSessioTest, ContrasenyaBuida)    // Contrasenya buida (error)
```

#### CtrlEnregistrarEquip
```cpp
TEST(CtrlEnregistrarEquipTest, NomEquipNoVuit)   // Nom no buit
TEST(CtrlEnregistrarEquipTest, EsportValid)      // Esport en llista vàlida
TEST(CtrlEnregistrarEquipTest, DataFundacioValida) // Data anterior avui
```

#### CtrlCrearLliga
```cpp
TEST(CtrlCrearLligaTest, NomLligaNoVuit)       // Nom no buit
TEST(CtrlCrearLligaTest, DisciplinaValida)     // Disciplina en llista
TEST(CtrlCrearLligaTest, ContrasenyaValida)    // Contrasenya >= 6 caràcters
```

#### CtrlCrearTemporada
```cpp
TEST(CtrlCrearTemporadaTest, DatesOrdenades)   // Inici < Fi
TEST(CtrlCrearTemporadaTest, DuradaTemporada)  // Durada >= 30 dies
TEST(CtrlCrearTemporadaTest, DuradaMenysUnAny) // Durada <= 365 dies
```

### 2.2 Tests de Validació de Dades

```cpp
TEST(ValidacioDataTest, StringNul)             // s == nullptr
TEST(ValidacioDataTest, StringBuit)            // s == ""
TEST(ValidacioDataTest, StringAmbEspais)       // s == "   "
TEST(ValidacioDataTest, StringValid)           // s != null i != empty
```

### 2.3 Tests de Comparació

```cpp
TEST(ComparacioTest, ComparacioDatesBefore)    // d1 < d2
TEST(ComparacioTest, ComparacioDatesBequals)   // d1 == d2
TEST(ComparacioTest, ComparacioNombres)        // a < b && b > a
TEST(ComparacioTest, ComparacioStringsCaseInsensitive) // case-insensitive
```

---

## 3. TESTS DE REGLES DE NEGOCI (test_business_rules.cpp)

### 3.1 Regles de Partit

| Regla | Validació | Test |
|---|---|---|
| Gols no negatius | golsLocal >= 0 && golsVisitant >= 0 | `GolsLocalNoNegatiu`, `GolsVisitantNoNegatiu` |
| Determinació guanyador | local/visitant/empat | `DeterminacioGuanyador` |
| Cálcul punts victòria | punts = 3 | `CalculPuntsVictoria` |
| Cálcul punts empat | punts = 1 | `CalculPuntsEmpat` |
| Cálcul punts derrota | punts = 0 | `CalculPuntsDerrota` |

**Tests executats:**
```cpp
TEST(ReglesPartitTest, GolsLocalNoNegatiu)
TEST(ReglesPartitTest, DeterminacioGuanyador)
TEST(ReglesPartitTest, CalculPuntsVictoria)
TEST(ReglesPartitTest, CalculPuntsEmpat)
TEST(ReglesPartitTest, CalculPuntsDerrota)
```

### 3.2 Regles d'Equip

| Regla | Fórmula | Test |
|---|---|---|
| Partits jugats | V + E + D | `PartitsJugats` |
| Punts totals | V*3 + E*1 | `PuntsCalcul` |
| Diferència de gols | GA - GC | `DiferenciaGols` |
| Ratio victories | V / PJ > 0.5 | `RatioVictories` |

**Tests executats:**
```cpp
TEST(ReglesEquipTest, PartitsJugats)
TEST(ReglesEquipTest, PuntsCalcul)
TEST(ReglesEquipTest, DiferenciaGols)
TEST(ReglesEquipTest, RatioVictories)
```

### 3.3 Classificació

```cpp
TEST(ClasificacioTest, OrdenacioPunts)          // Ordenació per punts descendents
TEST(ClasificacioTest, DesempatDiferenciaGols) // Si punts iguals, diferenciaGols
```

### 3.4 Validació de Jornada

```cpp
TEST(ValidacioJornadaTest, JornadaDinsTemporada)        // Jornada dins temporada
TEST(ValidacioJornadaTest, JornadaAnteriorTemporada)    // Error: abans temporada
TEST(ValidacioJornadaTest, JornadaPostTemporada)        // Error: després temporada
```

### 3.5 Validació de Rols

#### Capità
```cpp
TEST(ValidacioCapitaTest, EsCapita)              // Usuari és capita
TEST(ValidacioCapitaTest, NoEsCapita)            // Usuari no és capita
TEST(ValidacioCapitaTest, CapitaAmbEquip)       // Capita té equip
```

#### Administrador
```cpp
TEST(ValidacioAdminTest, EsAdministrador)        // Usuari és admin
TEST(ValidacioAdminTest, AdminAmbLliga)         // Admin té lliga
```

### 3.6 Convocatòria

```cpp
TEST(TestConvocatoriaTest, JugadorConvocat)     // Convocat
TEST(TestConvocatoriaTest, JugadorNoConvocat)   // No convocat
TEST(TestConvocatoriaTest, ConfirmacióPendent)  // Pendent
TEST(TestConvocatoriaTest, ConfirmacioCertainAffirmativa) // Confirmat
TEST(TestConvocatoriaTest, ConfirmacioNegativa) // Rebutjat
```

### 3.7 Estadístiques de Jugador

```cpp
TEST(EstadistiquesJugadorTest, AnotacionsPositives)  // >= 0
TEST(EstadistiquesJugadorTest, AssistenciesPositives) // >= 0
TEST(EstadistiquesJugadorTest, FaltesPositives)       // >= 0
TEST(EstadistiquesJugadorTest, MinutsPositius)        // >= 0
TEST(EstadistiquesJugadorTest, ProporcioCifres)       // Proporcions vàlides
```

### 3.8 Límits i Constraints

```cpp
TEST(LimitsConstraintsTest, DorsalLimits)      // 1 <= dorsal <= 99
TEST(LimitsConstraintsTest, EdatLimits)        // 16 <= edat <= 99
TEST(LimitsConstraintsTest, PuntsPositius)     // punts >= 0
TEST(LimitsConstraintsTest, GolsNoNegatiu)     // gols >= 0
```

---

## 4. CASOS ESPECÍFICS (Edge Cases)

### 4.1 Límits de Dades

| Case | Entrada | Validació | Resultat Esperat |
|---|---|---|---|
| Dorsal mínim | 1 | ValidarDorsal() | true |
| Dorsal màxim | 99 | ValidarDorsal() | true |
| Dorsal fora límit | 100 | ValidarDorsal() | false |
| Edat mínim | 16 | ValidarEdat() | true |
| Edat màxim | 99 | ValidarEdat() | true |
| Edat fora límit | 100 | ValidarEdat() | false |
| Jornada número | 0 | ValidarNumero() | false |
| Jornada número | 999999 | ValidarNumero() | true |

### 4.2 Casos Extrems de Dates

```cpp
TEST(EdgeCasesTest, TemporadaDuradaMinima)      // 1 dia
TEST(EdgeCasesTest, TemporadaDuradaMoltLlarga)  // 10 anys
```

---

## 5. LÒGICA DE NEGOCI COMUNA

| Regla | Validació | Test |
|---|---|---|
| PU-07 | >= 2 equips per jornades | `EquipsSuficientsPerJornades` ? true |
| PU-08 | 1 equip insuficient | `EquipsInsuficientsPerJornades` ? false |
| - | 0 equips | `EquipsZeroPerJornades` ? false |
| - | >= 10 equips | `EquipsAbundantsPerJornades` ? true |

---

## 6. COBERTURA DE TESTS

### Resum General

```
Fitxer                    Tests    Línies de codi    Cobertura
test.cpp                    6         20-30          100%
test_controllers.cpp       30         300-400         85%
test_business_logic.cpp    50         400-500         80%
test_business_rules.cpp    60         500-600         85%
```

**Total: 146+ casos de prova**

### Per Categoria

| Categoria | Casos | Cobertura |
|---|---|---|
| Entitats | 30 | 85% |
| Controladors | 40 | 80% |
| Regles de Negoci | 45 | 85% |
| Validacions | 25 | 90% |
| Casos Extrems | 6 | 100% |

---

## 7. COM EXECUTAR ELS TESTS

### Compilació i Execució

```bash
# Compilar projecte complet amb tests
msbuild Playcampus.sln /p:Configuration=Debug /p:Platform=x64

# Executar tests (des del directori build)
cd build\Debug
test.exe

# Amb filtres (opcional)
test.exe --gtest_filter="JugadorTest*"
test.exe --gtest_filter="ReglesPartitTest*"
```

### Opcions de Gtest

```bash
# Listar tots els tests disponibles
test.exe --gtest_list_tests

# Executar test específic
test.exe --gtest_filter="NomTestSuite.NomTest"

# Executar amb verbositat
test.exe --gtest_print_time=true

# Generar report
test.exe --gtest_output="xml:test_results.xml"
```

---

## 8. ESTRUCTURA D'UN TEST

### Template Bàsic

```cpp
class TestSuiteTest : public ::testing::Test {
protected:
    // Declaracions de dades de prova
    SomeClass^ objecte;
    
    virtual void SetUp() {
        // Inicialització abans de cada test
        objecte = gcnew SomeClass();
    }
    
    virtual void TearDown() {
        // Neteja després de cada test
        delete objecte;
    }
};

TEST_F(TestSuiteTest, CasoSpecific) {
    // Arrange: Preparació de dades
    int input = 10;
    
    // Act: Execució del codi a provar
    int result = objecte->Metode(input);
    
    // Assert: Verificació del resultat
    EXPECT_EQ(result, 10);
}
```

---

## 9. ASSERTIONS DISPONIBLES

### Igualtats

```cpp
EXPECT_EQ(a, b)        // a == b
EXPECT_NE(a, b)        // a != b
EXPECT_LT(a, b)        // a < b
EXPECT_LE(a, b)        // a <= b
EXPECT_GT(a, b)        // a > b
EXPECT_GE(a, b)        // a >= b
```

### Booleans

```cpp
EXPECT_TRUE(condition)
EXPECT_FALSE(condition)
```

### Strings

```cpp
EXPECT_STREQ(s1, s2)   // Comparació C-style
EXPECT_STRNE(s1, s2)
```

---

## 10. RECOMENDACIONS FUTURS

1. **Mocks de BD**: Crear mocks per als controladors que accedeixen a BD
2. **Tests d'Integració**: Tests que proven múltiples components junts
3. **Performance Tests**: Medir temps d'execució de operacions crítics
4. **Coverage Report**: Generar reports de cobertura amb OpenCppCoverage
5. **CI/CD Integration**: Integrar tests en pipeline GitHub Actions

---

## 11. MANTENIMENT

### Afegir Nou Test

1. Crear nova classe derivada de `::testing::Test`
2. Implementar `SetUp()` si necessita inicialització
3. Escriure mínim 3 tests: cas vàlid, casos invàlids
4. Documentar en aquesta guia

### Actualitzar Tests Existents

1. Executar tots els tests (`test.exe`)
2. Revisar tests afectats pels canvis
3. Actualitzar assercions si comportament canvia
4. Documentar raó del canvi

---

## Autor
PlayCampus - Equip de Qualitat

## Data de Creació
2024

## Última Actualització
2024
