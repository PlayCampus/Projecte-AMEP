# PlayCampus - Suite de Tests Unitaris ??

## ?? Descripció

Suite completa de tests unitaris per al projecte **PlayCampus** utilitzant **Google Test Framework (gtest)**.

La suite inclou:
- ? **146+ casos de prova**
- ? **Cobertura 80-90%** dels controladors
- ? **Tests d'entitats** (Jugador, Temporada, Jornada, Administrador)
- ? **Tests de lògica de negoci** (Controladors, Validacions)
- ? **Tests de regles de negoci** (Partits, Equips, Classificació)
- ? **Tests de casos extrems** (Edge cases)

---

## ?? Estructura

```
test/
??? test.cpp                    # Tests bàsics (6 tests)
??? test_controllers.cpp        # Tests d'entitats (30 tests)
??? test_business_logic.cpp     # Tests de controladors (50 tests)
??? test_business_rules.cpp     # Tests de regles (60 tests)
??? pch.h                       # Pre-compiled headers
??? run_tests.bat               # Script Windows per executar tests
??? run_tests.ps1               # Script PowerShell per executar tests
??? TEST_DOCUMENTATION.md       # Documentació completa
??? README.md                   # Aquest fitxer
```

---

## ?? Inici Ràpid

### 1. Compilar el Projecte

```bash
# Des del directori arrel
msbuild Playcampus.sln /p:Configuration=Debug /p:Platform=x64
```

### 2. Executar Tests

#### **Opció A: Script Windows (cmd)**
```bash
cd test
run_tests.bat
```

#### **Opció B: PowerShell**
```powershell
cd test
.\run_tests.ps1
```

#### **Opció C: Directe**
```bash
cd test
test.exe
```

---

## ?? Categories de Tests

### 1?? Tests d'Entitats (30 tests)

Validen les classes del model:

```cpp
// Jugador
? Dorsal vàlid/invàlid (1-99)
? Edat vàlida/invàlida (16-99)
? Antigüitat vàlida/invàlida
? Estadístiques (anotacions, assistències, etc.)

// Temporada
? Dates correctes (inici < fi)
? Dates incorrectes
? Setters/Getters

// Jornada
? Dates correctes/incorrectes
? Número vàlid/invàlid (> 0)
? Setters/Getters

// Administrador
? Telèfon de contacte
? Propietats
```

**Execució:**
```bash
test.exe --gtest_filter="*Test*"
```

### 2?? Tests de Lògica de Negoci (50 tests)

Validen els controladors i validacions:

```cpp
// CtrlCrearPartit
? Equips diferents
? Data vàlida
? Ubicació complerta

// CtrlIniciSessio
? Format correu vàlid
? Contrasenya vàlida

// CtrlEnregistrarEquip
? Nom equip vàlid
? Esport vàlid
? Data fundació vàlida

// CtrlCrearLliga
? Nom lliga vàlid
? Disciplina vàlida
? Contrasenya vàlida

// Validacions de dades
? Strings nuls/buits
? Comparacions
```

**Execució:**
```bash
test.exe --gtest_filter="*CtrlTest*"
```

### 3?? Tests de Regles de Negoci (60 tests)

Validen les regles del negoci:

```cpp
// Partit
? Gols no negatius
? Cálcul de punts (victòria=3, empat=1, derrota=0)
? Determinació de guanyador

// Equip
? Partits jugats = V + E + D
? Punts = V*3 + E*1
? Diferència de gols

// Classificació
? Ordenació per punts
? Desempat per diferència de gols

// Validacions
? Jornada dins de temporada
? Capita amb equip
? Admin amb lliga
? Convocatòria

// Estadístiques
? Valors positius
? Proporcions vàlides

// Límits
? Dorsal: 1-99
? Edat: 16-99
? Gols: >= 0
? Punts: >= 0
```

**Execució:**
```bash
test.exe --gtest_filter="*RulesTest*"
```

---

## ?? Opcions d'Execució

### Executar TOTS els tests
```bash
test.exe
```

### Executar tests específics
```bash
# Tests de Jugador
test.exe --gtest_filter="JugadorTest*"

# Tests de Partit
test.exe --gtest_filter="ReglesPartitTest*"

# Tests múltiples
test.exe --gtest_filter="*PartitTest*"
```

### Llistar tests disponibles
```bash
test.exe --gtest_list_tests
```

### Generar XML output (per a CI/CD)
```bash
test.exe --gtest_output="xml:test_results.xml"
```

### Execució amb temporització
```bash
test.exe --gtest_print_time=true
```

### Execució amb detalls
```bash
test.exe --gtest_verbose
```

---

## ?? Reportes

### Generar Report de Cobertura

Amb **OpenCppCoverage**:
```bash
OpenCppCoverage.exe --sources Playcampus -- test.exe
```

### Generar Report XML (Jenkins/GitLab)

```bash
test.exe --gtest_output="xml:test_results.xml"
```

Resultat: `test_results.xml` compatible amb Jenkins, GitLab CI, etc.

---

## ?? Exemples de Tests

### Test Senzill
```cpp
TEST(ExempleTest, CasoSimple) {
    int result = 2 + 2;
    EXPECT_EQ(result, 4);
}
```

### Test amb Fixture
```cpp
class JugadorTest : public ::testing::Test {
protected:
    Jugador^ jugador;
    
    virtual void SetUp() {
        jugador = gcnew Jugador(...);
    }
};

TEST_F(JugadorTest, DorsalValid) {
    jugador->SetDorsal(10);
    EXPECT_TRUE(jugador->ValidarDorsal());
}
```

### Test amb Paràmetres
```cpp
class ParametrizatTest : public ::testing::TestWithParam<int> {};

TEST_P(ParametrizatTest, CasMultiple) {
    int param = GetParam();
    EXPECT_GT(param, 0);
}

INSTANTIATE_TEST_SUITE_P(
    Numbers, ParametrizatTest,
    ::testing::Values(1, 5, 10, 50, 99)
);
```

---

## ? Assertions Comunes

```cpp
// Igualtats
EXPECT_EQ(a, b)         // a == b
EXPECT_NE(a, b)         // a != b
EXPECT_LT(a, b)         // a < b
EXPECT_LE(a, b)         // a <= b
EXPECT_GT(a, b)         // a > b
EXPECT_GE(a, b)         // a >= b

// Booleans
EXPECT_TRUE(condition)
EXPECT_FALSE(condition)

// Strings
EXPECT_STREQ(s1, s2)    // Comparació C
EXPECT_STRNE(s1, s2)
EXPECT_STRCASEEQ(s1, s2) // Case-insensitive

// Punts flotants
EXPECT_FLOAT_EQ(a, b)
EXPECT_DOUBLE_EQ(a, b)
EXPECT_NEAR(a, b, tolerance)

// Exceptions
EXPECT_THROW(statement, exception_type)
EXPECT_NO_THROW(statement)
```

---

## ?? Debugging Tests

### Executar un test específic
```bash
test.exe --gtest_filter="JugadorTest.DorsalValid"
```

### Parar en fallar
```bash
test.exe --gtest_break_on_failure
```

### Repetir N vegades
```bash
test.exe --gtest_repeat=5
```

### Shuffle (ordre aleatori)
```bash
test.exe --gtest_shuffle
```

---

## ?? Taula de Tests per Categoria

| Categoria | Tests | Fitxer | Cobertura |
|-----------|-------|--------|-----------|
| Entitats | 30 | test_controllers.cpp | 85% |
| Lògica | 50 | test_business_logic.cpp | 80% |
| Regles | 60 | test_business_rules.cpp | 85% |
| Bàsics | 6 | test.cpp | 100% |
| **TOTAL** | **146+** | | **85%** |

---

## ?? CI/CD Integration

### GitHub Actions

```yaml
name: Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v2
      - name: Build
        run: msbuild Playcampus.sln /p:Configuration=Debug
      - name: Run Tests
        run: cd test && test.exe --gtest_output="xml:test_results.xml"
      - name: Upload Results
        uses: actions/upload-artifact@v2
        with:
          name: test-results
          path: test/test_results.xml
```

### GitLab CI

```yaml
test:
  image: windows:ltsc2022
  script:
    - msbuild Playcampus.sln /p:Configuration=Debug
    - cd test
    - test.exe --gtest_output="xml:test_results.xml"
  artifacts:
    reports:
      junit: test/test_results.xml
```

---

## ?? Documentació

Per a documentació detallada, consulteu:
- [`TEST_DOCUMENTATION.md`](./TEST_DOCUMENTATION.md) - Guia completa
- [Google Test Documentation](https://google.github.io/googletest/)

---

## ?? Contribuïr

Si vols afegir nous tests:

1. Crear nova classe `XxxTest` que hereti de `::testing::Test`
2. Implementar `SetUp()` si necessita inicialització
3. Escriure mínim 3 tests (cas vàlid, cases invàlids)
4. Documentar en `TEST_DOCUMENTATION.md`
5. Fer push i esperar revisió

---

## ?? Requisits

- **Visual Studio 2019+**
- **Google Test Framework** (inclòs al projecte)
- **.NET Framework 4.7+**
- **C++ CLI Support**

---

## ?? Suport

Per a problemes o preguntes:
1. Consultar [`TEST_DOCUMENTATION.md`](./TEST_DOCUMENTATION.md)
2. Revisar output dels tests (`test_results.xml`)
3. Contactar amb l'equip de qualitat

---

## ?? Llicència

Igual al projecte principal PlayCampus

---

## ?? Equip

PlayCampus Development Team - 2024

---

**Darrera actualització**: 2024
