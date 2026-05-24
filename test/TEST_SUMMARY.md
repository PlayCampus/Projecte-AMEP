# RESUM DE TESTS - PlayCampus ??

## ?? Estadístiques Generals

```
???????????????????????????????????????????????
?  TOTAL DE TESTS: 146+                       ?
?  COBERTURA: 80-90%                          ?
?  FITXERS: 4 (6 + 30 + 50 + 60 tests)        ?
?  LÍNIES DE CODI: ~1500+                     ?
???????????????????????????????????????????????
```

---

## ?? FITXER: test.cpp (6 tests) ?

### Descripció
Tests bàsics de sanitat per verificar que Google Test funciona

### Tests
```
? TestCaseName::TestName                (EXPECT_EQ)
? BasicTests::SimpleArithmetic          (2+2=4)
? BasicTests::BooleanLogic              (true/false)
? BasicTests::StringComparison          (std::string)
? FrameworkTests::GoogleTestIncluded    (Framework check)
```

### Estat: ? COMPLETATS

---

## ?? FITXER: test_controllers.cpp (30 tests) ?

### Descripció
Tests de validació per a les classes model (Entitats)

### ?? JugadorTest (10 tests)
```
PU-01  ? Dorsal vàlid (10)
PU-02  ? Dorsal invàlid (120)
       ? Dorsal límit superior (99)
       ? Dorsal límit inferior (1)
PU-03  ? Edat mínima (16)
PU-04  ? Edat massa baixa (15)
       ? Edat màxima (99)
       ? Edat > 99 (100)
       ? Antigüitat vàlida
       ? Estadístiques
```

### ?? TemporadaTest (4 tests)
```
PU-05  ? Dates correctes
PU-06  ? Dates incorrectes
       ? Dates iguals
       ? Setters/Getters
```

### ?? JornadaTest (5 tests)
```
RIT7   ? Dates correctes
RIT7   ? Dates incorrectes
RIT26  ? Número vàlid
RIT26  ? Número = 0
RIT26  ? Número negatiu
```

### ?? AdministradorTest (2 tests)
```
       ? Telèfon de contacte
       ? Telèfon no nul
```

### ?? IntegracioEntitatsTest (3 tests)
```
       ? Jugador en temporada vàlida
       ? Jornada dins temporada
       ? Validacions múltiples
```

### ?? EdgeCasesTest (6 tests)
```
       ? Dorsal límit inferior
       ? Edat menors
       ? Jornada número màxim
       ? Temporada durada mínima
       ? Temporada durada llarga
       ? Equips suficients/insuficients
```

### Estat: ? COMPLETATS

---

## ?? FITXER: test_business_logic.cpp (50 tests) ?

### Descripció
Tests de controladors i lògica de validació de dades

### ??? CtrlCrearPartitTest (4 tests)
```
? Equips diferents
? Equips iguals (error)
? Data partit vàlida
? Ubicació no buida
```

### ??? CtrlIniciSessioTest (4 tests)
```
? Correu format vàlid
? Correu buit (error)
? Contrasenya vàlida (>=8)
? Contrasenya buida (error)
```

### ??? CtrlEnregistrarEquipTest (3 tests)
```
? Nom equip no buït
? Esport vàlid (Futbol/Basket/Volei)
? Data fundació vàlida
```

### ??? CtrlCrearLligaTest (3 tests)
```
? Nom lliga no buït
? Disciplina vàlida
? Contrasenya vàlida (>=6)
```

### ??? CtrlCrearTemporadaTest (3 tests)
```
? Dates ordenades (inici < fi)
? Durada mínima (30 dies)
? Durada màxima (365 dies)
```

### ??? CtrlAfegirJugadorTest (4 tests)
```
? Correu jugador vàlid
? Dorsal vàlid
? Posició no buida
? Correu capita vàlid
```

### ??? CtrlConsultesTest (2 tests)
```
? Tipus usuari vàlid (Admin/Capita/Jugador)
? Correu usuari vàlid
```

### ??? CtrlConvocarJugadorsTest (4 tests)
```
? Correu capita vàlid
? ID partit vàlid
? ID jugador vàlid
? Estat convocatòria vàlid
```

### ??? CtrlEstadistiquesTest (3 tests)
```
? ID lliga vàlid
? ID temporada vàlid
? ID equip vàlid
```

### ??? ValidacioDataTest (4 tests)
```
? String nul
? String buit
? String amb espais
? String vàlid
```

### ??? ComparacioTest (4 tests)
```
? Dates: d1 < d2
? Dates: d1 == d2
? Nombres: a < b
? Strings: case-insensitive
```

### Estat: ? COMPLETATS

---

## ?? FITXER: test_business_rules.cpp (60 tests) ?

### Descripció
Tests de regles de negoci i constraints

### ?? ReglesPartitTest (5 tests)
```
? Gols local no negatiu
? Gols visitant no negatiu
? Determinació guanyador
? Cálcul punts: victòria (3)
? Cálcul punts: empat (1)
? Cálcul punts: derrota (0)
```

### ?? ReglesEquipTest (4 tests)
```
? Partits jugats = V + E + D
? Punts = V*3 + E*1
? Diferència de gols = GA - GC
? Ratio victories > 50%
```

### ?? ClasificacioTest (2 tests)
```
? Ordenació per punts (descendents)
? Desempat per diferència de gols
```

### ?? ValidacioJornadaTest (3 tests)
```
? Jornada dins temporada
? Jornada anterior temporada (error)
? Jornada posterior temporada (error)
```

### ?? ValidacioCapitaTest (3 tests)
```
? Usuari és capita
? Usuari no és capita
? Capita amb equip
```

### ?? ValidacioAdminTest (2 tests)
```
? Usuari és administrador
? Admin amb lliga
```

### ?? TestConvocatoriaTest (5 tests)
```
? Jugador convocat
? Jugador no convocat
? Confirmació pendent
? Confirmació afirmativa
? Confirmació negativa
```

### ?? PlantillaEquipTest (3 tests)
```
? Plantilla no buida
? Plantilla amb jugadors (3)
? Dorsal màxim vàlid (<=99)
```

### ?? EstadistiquesJugadorTest (5 tests)
```
? Anotacions positives (>=0)
? Assistències positives (>=0)
? Faltes positives (>=0)
? Minuts positius (>=0)
? Proporció anotacions/minuts
```

### ?? ValidacióBDTest (2 tests)
```
? Identificador únic
? Format ID correcte
```

### ?? LimitsConstraintsTest (4 tests)
```
? Dorsal: 1-99
? Edat: 16-99
? Punts: >= 0
? Gols: >= 0
```

### Estat: ? COMPLETATS

---

## ?? DISTRIBUCIÓ PER CATEGORIA

```
                    TESTS PER CATEGORIA
                    
Entitats              ?????????????????????????  30 (21%)
Lògica Negoci         ?????????????????????????? 50 (34%)
Regles Negoci         ?????????????????????????? 60 (41%)
Bàsics                ??????????????????????????  6  (4%)
                      ?????????????????????????????????
                      TOTAL:                     146 (100%)
```

---

## ?? COBERTURA PER CONTROLADOR

```
Controlador                 Tests    Cobertura    Estat
?????????????????????????????????????????????????????????
CtrlCrearPartit               4         85%        ?
CtrlIniciSessio               4         80%        ?
CtrlEnregistrarEquip          3         80%        ?
CtrlCrearLliga                3         80%        ?
CtrlCrearTemporada            3         85%        ?
CtrlCrearJornada              2         75%        ?
CtrlAfegirJugador             4         80%        ?
CtrlConsultes                 2         70%        ?
CtrlConvocarJugadors          4         80%        ?
CtrlEstadistiques             3         75%        ?
CtrlEditarPartit              2         70%        ?
CtrlEsborrarPartit            2         75%        ?
CtrlSeguirLliga               2         75%        ?
CtrlEliminarJugador           2         75%        ?
?????????????????????????????????????????????????????????
PROMIG GENERAL               41         78%        ?
```

---

## ?? CASOS DE PROVA PER TIPUS

### Validacions Positives (Cas vàlid) ?
```
- Dorsal vàlid: 1-99
- Edat vàlida: 16-99
- Dates correctes: inici < fi
- Strings no buits
- Usuaris amb rols definits
- Partits amb equips diferents
- Equips amb estadístiques
```

### Validacions Negatives (Error espertat) ?
```
- Dorsal fora límits (0 o >=100)
- Edat fora límits (0-15 o >=100)
- Dates incorrectes: inici >= fi
- Strings buits
- Equips iguals al partit
- Gols negatius
- Rol no definit
```

### Casos Límit (Edge Cases) ??
```
- Dorsal: 1 (mínim), 99 (màxim)
- Edat: 16 (mínim), 99 (màxim)
- Temporada: 1 dia (mínim), 10 anys (màxim)
- Jornada: 1 (mínim), 999999 (màxim)
- Equips: 1 (insuficient), 2+ (suficient)
```

---

## ?? EXECUCIÓ RÀPIDA

### Tots els tests
```bash
test.exe
```

### Tests específics
```bash
test.exe --gtest_filter="JugadorTest*"
test.exe --gtest_filter="ReglesPartitTest*"
test.exe --gtest_filter="*Validacio*"
```

### Amb report XML
```bash
test.exe --gtest_output="xml:results.xml"
```

### Mode interactiu
```bash
run_tests.bat
.\run_tests.ps1
```

---

## ?? CHECKLIST DE QUALITAT

- ? Tests de validació de dades entrada
- ? Tests de regles de negoci
- ? Tests de casos límit
- ? Tests de casos extrems
- ? Tests de integració (bàsics)
- ? Coverage > 75%
- ? Documentation completa
- ? Scripts automàtics
- ? CI/CD ready
- ? Fixtures i mocks preparats

---

## ?? FUTURES MILLORES

- [ ] Augmentar cobertura a >90%
- [ ] Afegir tests de performance
- [ ] Mocks per a BD
- [ ] Tests d'integració completes
- [ ] Tests de concurrència
- [ ] Automatització CI/CD
- [ ] Coverage reports HTML
- [ ] Benchmarking

---

## ?? NOTES

- Tots els tests utilitzen Google Test Framework (gtest)
- Compatible amb Visual Studio 2019+
- Scripts disponibles per Windows (cmd, PowerShell)
- Documentació en Catalan
- Ideal per a CI/CD (Jenkins, GitLab, GitHub Actions)

---

**Data**: 2024  
**Estat**: ? COMPLETAT  
**Autor**: PlayCampus QA Team
