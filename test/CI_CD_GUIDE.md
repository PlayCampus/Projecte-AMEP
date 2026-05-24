# PlayCampus Tests - Guía CI/CD

## ?? Integración con GitHub Actions

```yaml
name: PlayCampus Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup MSBuild
        uses: microsoft/setup-msbuild@v1
      
      - name: Build Tests
        run: msbuild test/test.vcxproj /p:Configuration=Debug /p:Platform=x64
      
      - name: Run Tests
        run: test\x64\Debug\test.exe --gtest_output="xml:test_results.xml"
      
      - name: Upload Results
        uses: actions/upload-artifact@v3
        with:
          name: test-results
          path: test_results.xml

      - name: Publish Test Results
        uses: EnricoMi/publish-unit-test-result-action@v2
        if: always()
        with:
          files: test_results.xml
```

## ?? Integración con GitLab CI

```yaml
stages:
  - build
  - test

build_tests:
  stage: build
  image: windows:latest
  script:
    - msbuild test/test.vcxproj /p:Configuration=Debug /p:Platform=x64
  artifacts:
    paths:
      - test/x64/Debug/test.exe

run_tests:
  stage: test
  image: windows:latest
  dependencies:
    - build_tests
  script:
    - test/x64/Debug/test.exe --gtest_output="xml:test_results.xml"
  artifacts:
    reports:
      junit: test_results.xml
```

## ?? Comandos Útiles

```bash
# Compilar
msbuild test/test.vcxproj /p:Configuration=Debug /p:Platform=x64

# Ejecutar todos los tests
test\x64\Debug\test.exe

# Listar tests
test\x64\Debug\test.exe --gtest_list_tests

# Tests específicos
test\x64\Debug\test.exe --gtest_filter="ReglesPartitTest*"

# Generar report XML
test\x64\Debug\test.exe --gtest_output="xml:test_results.xml"

# Ejecutar N veces
test\x64\Debug\test.exe --gtest_repeat=5

# Shuffle (orden aleatorio)
test\x64\Debug\test.exe --gtest_shuffle
```

## ?? Métrica de Éxito

- ? 66/66 tests pasando
- ? 0 errores de compilación
- ? Tiempo < 100ms
- ? 100% tasa de éxito
