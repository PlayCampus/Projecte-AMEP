#include "pch.h"
#include "Form1.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

Form1::Form1(void) {
			InitializeComponent(); // IMPORTANT: NO ESBORRAR

			// 1. Creació d'objectes
			this->pnlConvocatoria = gcnew System::Windows::Forms::Panel();
			this->btnGestionarConvocatoria = gcnew System::Windows::Forms::Button();
			this->btnTornarConvocatoria = gcnew System::Windows::Forms::Button();
			this->cbPartitsConvocatoria = gcnew System::Windows::Forms::ComboBox();
			this->dgvConvocatoria = gcnew System::Windows::Forms::DataGridView();
			this->convocatoriaPartitIds = gcnew System::Collections::Generic::List<System::String^>();

			// 2. Propietats i Events
			this->btnGestionarConvocatoria->Text = L"Gestionar Convocatòries";
			this->btnGestionarConvocatoria->Click += gcnew System::EventHandler(this, &Form1::btnGestionarConvocatoria_Click);

			this->btnTornarConvocatoria->Text = L"Tornar al Menú";
			this->btnTornarConvocatoria->Click += gcnew System::EventHandler(this, &Form1::btnTornarConvocatoria_Click);

			this->cbPartitsConvocatoria->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPartitsConvocatoria->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbPartitsConvocatoria_SelectedIndexChanged);

			this->dgvConvocatoria->AllowUserToAddRows = false;
			this->dgvConvocatoria->ReadOnly = true;
			this->dgvConvocatoria->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvConvocatoria->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dgvConvocatoria_CellClick);

			// 3. Jerarquia (Afegir-los a la pantalla)
			this->pnlMain->Controls->Add(this->btnGestionarConvocatoria);
			this->Controls->Add(this->pnlConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->btnTornarConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->cbPartitsConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->dgvConvocatoria);

			// 4. Estat Inicial
			this->pnlConvocatoria->Visible = false;
			this->btnGestionarConvocatoria->Visible = false;

			// --- INICI ESTADÍSTIQUES PARTIT ---
			this->btnEstPartit = gcnew System::Windows::Forms::Button();
			this->btnEstJugadors = gcnew System::Windows::Forms::Button();
			this->pnlEstadistiquesPartitDetail = gcnew System::Windows::Forms::Panel();
			this->lblEstPartitTitle = gcnew System::Windows::Forms::Label();
			this->lblEstPartitLliga = gcnew System::Windows::Forms::Label();
			this->cmbEstPartitLligues = gcnew System::Windows::Forms::ComboBox();
			this->lblEstPartitTemporada = gcnew System::Windows::Forms::Label();
			this->cmbEstPartitTemporades = gcnew System::Windows::Forms::ComboBox();
			this->lblEstPartitPartits = gcnew System::Windows::Forms::Label();
			this->cmbEstPartitPartits = gcnew System::Windows::Forms::ComboBox();
			this->lblEstPartitResultat = gcnew System::Windows::Forms::Label();
			this->dgvEstPartitDetalls = gcnew System::Windows::Forms::DataGridView();
			this->btnEstPartitTornar = gcnew System::Windows::Forms::Button();

			this->estPartitLligaIds = gcnew System::Collections::Generic::List<String^>();
			this->estPartitTemporadaIds = gcnew System::Collections::Generic::List<String^>();
			this->estPartitIds = gcnew System::Collections::Generic::List<String^>();

			this->btnEstPartit->Text = L"Estadístiques Partit";
			this->btnEstPartit->Click += gcnew System::EventHandler(this, &Form1::btnEstPartit_Click);
			this->btnEstPartitTornar->Text = L"Tornar";
			this->btnEstPartitTornar->Click += gcnew System::EventHandler(this, &Form1::btnEstPartitTornar_Click);

			this->lblEstPartitTitle->Text = L"ESTADÍSTIQUES DE PARTIT";
			this->lblEstPartitTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold);
			this->lblEstPartitTitle->AutoSize = true;

			this->lblEstPartitLliga->Text = L"Selecciona Lliga:";
			this->lblEstPartitTemporada->Text = L"Selecciona Temporada:";
			this->lblEstPartitPartits->Text = L"Selecciona Partit:";
			this->lblEstPartitResultat->Text = L"";

			this->lblEstPartitLliga->AutoSize = true;
			this->lblEstPartitTemporada->AutoSize = true;
			this->lblEstPartitPartits->AutoSize = true;
			this->lblEstPartitResultat->AutoSize = true;

			this->cmbEstPartitLligues->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEstPartitTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEstPartitPartits->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

			this->cmbEstPartitLligues->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitLligues_SelectedIndexChanged);
			this->cmbEstPartitTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitTemporades_SelectedIndexChanged);
			this->cmbEstPartitPartits->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitPartits_SelectedIndexChanged);

			this->dgvEstPartitDetalls->AllowUserToAddRows = false;
			this->dgvEstPartitDetalls->ReadOnly = true;
			this->dgvEstPartitDetalls->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;

			this->dgvEstPartitDetalls->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;

			// Configuración del botón Estadístiques Jugadors
			this->btnEstJugadors->Text = L"Estadístiques Jugadors";
			this->btnEstJugadors->Click += gcnew System::EventHandler(this, &Form1::btnEstJugadors_Click);

			// Jerarquia
			this->pnlEstadistiques->Controls->Add(this->btnEstPartit);
			this->pnlEstadistiques->Controls->Add(this->btnEstJugadors);

			this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitTitle);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitLliga);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitLligues);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitTemporada);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitTemporades);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitPartits);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitPartits);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitResultat);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->dgvEstPartitDetalls);
			this->pnlEstadistiquesPartitDetail->Controls->Add(this->btnEstPartitTornar);

			this->Controls->Add(this->pnlEstadistiquesPartitDetail);
			this->pnlEstadistiquesPartitDetail->Visible = false;
			// --- FI ESTADÍSTIQUES PARTIT ---

			// --- INICI SEGUIR LLIGA (MENÚ PRINCIPAL) ---
			this->btnSeguirLligaMainMenu = gcnew System::Windows::Forms::Button();
			this->btnSeguirLligaMainMenu->Text = L"Seguir Lliga";
			this->btnSeguirLligaMainMenu->Size = System::Drawing::Size(180, 40);
			this->btnSeguirLligaMainMenu->Visible = false;
			this->btnSeguirLligaMainMenu->Click += gcnew System::EventHandler(this, &Form1::btnSeguirLligaMainMenu_Click);
			this->pnlMain->Controls->Add(this->btnSeguirLligaMainMenu);

			this->pnlDashboardLliga = gcnew System::Windows::Forms::Panel();
			this->pnlDashboardLliga->Visible = false;
			this->pnlDashboardLliga->BackColor = System::Drawing::Color::White;
			this->pnlDashboardLliga->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlMain->Controls->Add(this->pnlDashboardLliga);

			this->lblDashboardLliga = gcnew System::Windows::Forms::Label();
			this->lblDashboardLliga->Text = L"";
			this->lblDashboardLliga->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Bold);
			this->lblDashboardLliga->AutoSize = true;
			this->pnlDashboardLliga->Controls->Add(this->lblDashboardLliga);

			this->lblDashboardClassificacio = gcnew System::Windows::Forms::Label();
			this->lblDashboardClassificacio->Text = L"Classificació";
			this->lblDashboardClassificacio->AutoSize = true;
			this->pnlDashboardLliga->Controls->Add(this->lblDashboardClassificacio);

			this->dgvDashboardClassificacio = gcnew System::Windows::Forms::DataGridView();
			this->dgvDashboardClassificacio->AllowUserToAddRows = false;
			this->dgvDashboardClassificacio->ReadOnly = true;
			this->dgvDashboardClassificacio->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvDashboardClassificacio->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->pnlDashboardLliga->Controls->Add(this->dgvDashboardClassificacio);

			this->lblDashboardProximsPartits = gcnew System::Windows::Forms::Label();
			this->lblDashboardProximsPartits->Text = L"Pròxims partits";
			this->lblDashboardProximsPartits->AutoSize = true;
			this->pnlDashboardLliga->Controls->Add(this->lblDashboardProximsPartits);

			this->dgvDashboardProximsPartits = gcnew System::Windows::Forms::DataGridView();
			this->dgvDashboardProximsPartits->AllowUserToAddRows = false;
			this->dgvDashboardProximsPartits->ReadOnly = true;
			this->dgvDashboardProximsPartits->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvDashboardProximsPartits->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->pnlDashboardLliga->Controls->Add(this->dgvDashboardProximsPartits);

			this->lblDashboardUltimsResultats = gcnew System::Windows::Forms::Label();
			this->lblDashboardUltimsResultats->Text = L"Últims resultats";
			this->lblDashboardUltimsResultats->AutoSize = true;
			this->pnlDashboardLliga->Controls->Add(this->lblDashboardUltimsResultats);

			this->dgvDashboardUltimsResultats = gcnew System::Windows::Forms::DataGridView();
			this->dgvDashboardUltimsResultats->AllowUserToAddRows = false;
			this->dgvDashboardUltimsResultats->ReadOnly = true;
			this->dgvDashboardUltimsResultats->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvDashboardUltimsResultats->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->pnlDashboardLliga->Controls->Add(this->dgvDashboardUltimsResultats);
			// --- FI SEGUIR LLIGA ---

			Form1_Resize(nullptr, nullptr);
		}

Form1::~Form1() {
			if (components)
			{
				delete components;
			}
		}

}
