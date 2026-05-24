#!/usr/bin/env pwsh
<#
.SYNOPSIS
    PlayCampus - Script PowerShell per executar tests unitaris

.DESCRIPTION
    Script que permet executar la suite de tests de PlayCampus de manera fàcil
    Inclou filtres per categoria, generació de reports, etc.

.PARAMETER Action
    Acció a executar: 'All', 'Entities', 'Business', 'Rules', 'List'

.PARAMETER Output
    Format d'output: 'Console' o 'XML'

.EXAMPLE
    .\run_tests.ps1 -Action All
    .\run_tests.ps1 -Action Entities -Output XML
#>

param(
    [ValidateSet('All', 'Entities', 'Business', 'Rules', 'List', 'Interactive')]
    [string]$Action = 'Interactive',
    
    [ValidateSet('Console', 'XML', 'Both')]
    [string]$Output = 'Console'
)

# Configuració
$testExecutable = 'test.exe'
$xmlOutput = 'test_results.xml'

# Funcions auxiliars
function Write-Header {
    param([string]$Title)
    Write-Host ""
    Write-Host "??????????????????????????????????????????????????????????????" -ForegroundColor Cyan
    Write-Host "?  PlayCampus - Suite de Tests Unitaris                     ?" -ForegroundColor Cyan
    Write-Host "?  Google Test Framework                                     ?" -ForegroundColor Cyan
    Write-Host "?                                                            ?" -ForegroundColor Cyan
    Write-Host "?  $Title" -ForegroundColor Cyan
    Write-Host "??????????????????????????????????????????????????????????????" -ForegroundColor Cyan
    Write-Host ""
}

function Test-ExecutableExists {
    if (-not (Test-Path $testExecutable)) {
        Write-Host "ERROR: No s'ha trobat $testExecutable" -ForegroundColor Red
        Write-Host "Assegureu-vos de compilar primer el projecte amb:" -ForegroundColor Yellow
        Write-Host "  msbuild Playcampus.sln /p:Configuration=Debug /p:Platform=x64" -ForegroundColor Yellow
        exit 1
    }
}

function Run-Tests {
    param(
        [string]$Filter = '',
        [string]$Description = 'Tests'
    )
    
    Write-Host "Executant: $Description" -ForegroundColor Green
    Write-Host "????????????????????????????????????????????????????????????" -ForegroundColor Gray
    
    $args = @('--gtest_print_time=true')
    
    if ($Filter) {
        $args += "--gtest_filter=$Filter"
    }
    
    if ($Output -eq 'XML' -or $Output -eq 'Both') {
        $args += "--gtest_output=xml:$xmlOutput"
    }
    
    & $testExecutable $args
    
    Write-Host ""
}

function Show-Menu {
    Write-Host ""
    Write-Host "Opcions disponibles:" -ForegroundColor Yellow
    Write-Host "[1] Executar TOTS els tests" -ForegroundColor Cyan
    Write-Host "[2] Executar tests d'ENTITATS" -ForegroundColor Cyan
    Write-Host "[3] Executar tests de LÒGICA DE NEGOCI" -ForegroundColor Cyan
    Write-Host "[4] Executar tests de REGLES DE NEGOCI" -ForegroundColor Cyan
    Write-Host "[5] Llistar tots els tests disponibles" -ForegroundColor Cyan
    Write-Host "[6] Executar amb output XML (per a CI/CD)" -ForegroundColor Cyan
    Write-Host "[7] Sortir" -ForegroundColor Cyan
    Write-Host ""
}

# Funcions per executar categories
function Run-AllTests {
    Write-Header "Executant TOTS els tests"
    Run-Tests -Description "Tots els tests"
}

function Run-EntityTests {
    Write-Header "Executant tests d'ENTITATS"
    Run-Tests -Filter "JugadorTest*" -Description "Tests de Jugador"
    Run-Tests -Filter "TemporadaTest*" -Description "Tests de Temporada"
    Run-Tests -Filter "JornadaTest*" -Description "Tests de Jornada"
    Run-Tests -Filter "AdministradorTest*" -Description "Tests d'Administrador"
    Run-Tests -Filter "IntegracioEntitatsTest*" -Description "Tests de Integració"
    Run-Tests -Filter "EdgeCasesTest*" -Description "Tests de Casos Extrems"
}

function Run-BusinessLogicTests {
    Write-Header "Executant tests de LÒGICA DE NEGOCI"
    Run-Tests -Filter "CtrlCrearPartitTest*" -Description "Tests CtrlCrearPartit"
    Run-Tests -Filter "CtrlIniciSessioTest*" -Description "Tests CtrlIniciSessio"
    Run-Tests -Filter "CtrlEnregistrarEquipTest*" -Description "Tests CtrlEnregistrarEquip"
    Run-Tests -Filter "CtrlCrearLligaTest*" -Description "Tests CtrlCrearLliga"
    Run-Tests -Filter "CtrlCrearTemporadaTest*" -Description "Tests CtrlCrearTemporada"
    Run-Tests -Filter "ValidacioDataTest*" -Description "Tests de Validació de Dades"
    Run-Tests -Filter "ComparacioTest*" -Description "Tests de Comparació"
}

function Run-BusinessRulesTests {
    Write-Header "Executant tests de REGLES DE NEGOCI"
    Run-Tests -Filter "ReglesPartitTest*" -Description "Regles de Partit"
    Run-Tests -Filter "ReglesEquipTest*" -Description "Regles d'Equip"
    Run-Tests -Filter "ClasificacioTest*" -Description "Tests de Classificació"
    Run-Tests -Filter "ValidacioJornadaTest*" -Description "Validació de Jornada"
    Run-Tests -Filter "ValidacioCapitaTest*" -Description "Validació de Capita"
    Run-Tests -Filter "ValidacioAdminTest*" -Description "Validació d'Admin"
    Run-Tests -Filter "TestConvocatoriaTest*" -Description "Tests de Convocatòria"
    Run-Tests -Filter "EstadistiquesJugadorTest*" -Description "Tests d'Estadístiques"
    Run-Tests -Filter "LimitsConstraintsTest*" -Description "Tests de Límits"
}

function Show-AvailableTests {
    Write-Header "Llistant tests disponibles"
    & $testExecutable --gtest_list_tests
}

function Show-XmlOutput {
    Write-Header "Generant output XML"
    & $testExecutable --gtest_output="xml:$xmlOutput"
    Write-Host "? Resultats guardats en: $xmlOutput" -ForegroundColor Green
}

function Show-InteractiveMenu {
    do {
        Write-Header "Mode Interactiu"
        Show-Menu
        $choice = Read-Host "Selecciona una opció (1-7)"
        
        switch ($choice) {
            '1' { Run-AllTests }
            '2' { Run-EntityTests }
            '3' { Run-BusinessLogicTests }
            '4' { Run-BusinessRulesTests }
            '5' { Show-AvailableTests }
            '6' { Show-XmlOutput }
            '7' {
                Write-Host "Fins aviat!" -ForegroundColor Cyan
                exit 0
            }
            default {
                Write-Host "ERROR: Opció no vàlida. Tria entre 1 i 7." -ForegroundColor Red
            }
        }
        
        Read-Host "Prem ENTER per continuar"
    } while ($true)
}

# Main
Test-ExecutableExists

switch ($Action) {
    'All' {
        Write-Header "Executant TOTS els tests"
        Run-AllTests
    }
    'Entities' {
        Run-EntityTests
    }
    'Business' {
        Run-BusinessLogicTests
    }
    'Rules' {
        Run-BusinessRulesTests
    }
    'List' {
        Show-AvailableTests
    }
    'Interactive' {
        Show-InteractiveMenu
    }
}

if ($Output -eq 'XML' -or $Output -eq 'Both') {
    Write-Host ""
    Write-Host "? Resultats guardats en: $xmlOutput" -ForegroundColor Green
}

Write-Host ""
