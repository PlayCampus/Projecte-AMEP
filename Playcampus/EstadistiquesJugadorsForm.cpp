#include "pch.h"
#include "EstadistiquesJugadorsForm.h"
#include "EstilInterficie.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace Playcampus::Domini;

	// PRE: cert.
	// POST: crea el formulari i carrega les estadistiques inicials dels jugadors.
	EstadistiquesJugadorsForm::EstadistiquesJugadorsForm() {
		components = nullptr;
		InitializeComponent();
		DesignForm();
		CarregarEstadistiques();
	}

	// PRE: el formulari pot tenir components inicialitzats.
	// POST: allibera els components del formulari.
	EstadistiquesJugadorsForm::~EstadistiquesJugadorsForm() {
		if (components) {
			delete components;
		}
	}

	// PRE: cert.
	// POST: inicialitza i situa tots els controls del formulari.
	void EstadistiquesJugadorsForm::InitializeComponent() {
		this->lblTitle = gcnew System::Windows::Forms::Label();
		this->lblCerca = gcnew System::Windows::Forms::Label();
		this->txtCercaJugador = gcnew System::Windows::Forms::TextBox();
		this->btnCercar = gcnew System::Windows::Forms::Button();
		this->btnNetejar = gcnew System::Windows::Forms::Button();
		this->lblResultatCerca = gcnew System::Windows::Forms::Label();
		this->dgvEstadistiques = gcnew System::Windows::Forms::DataGridView();
		this->btnTornar = gcnew System::Windows::Forms::Button();

		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvEstadistiques))->BeginInit();
		this->SuspendLayout();

		// Configuracio general del formulari
		this->Text = L"Estad\u00EDstiques dels Jugadors";
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->StartPosition = FormStartPosition::CenterParent;
		this->ClientSize = System::Drawing::Size(1000, 620);
		this->MinimizeBox = false;
		this->MaximizeBox = false;
		this->BackColor = System::Drawing::Color::White;
		this->ControlBox = false;

		// lblTitle
		this->lblTitle->Text = L"Estad\u00EDstiques dels Jugadors";
		this->lblTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.0F, System::Drawing::FontStyle::Bold);
		this->lblTitle->AutoSize = true;
		this->lblTitle->Location = System::Drawing::Point(30, 20);
		this->lblTitle->ForeColor = System::Drawing::Color::Black;

		// lblCerca
		this->lblCerca->Text = L"Cercar jugador:";
		this->lblCerca->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->lblCerca->AutoSize = true;
		this->lblCerca->Location = System::Drawing::Point(30, 70);
		this->lblCerca->ForeColor = System::Drawing::Color::Black;

		// txtCercaJugador
		this->txtCercaJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->txtCercaJugador->Location = System::Drawing::Point(150, 67);
		this->txtCercaJugador->Name = L"txtCercaJugador";
		this->txtCercaJugador->Size = System::Drawing::Size(360, 26);
		this->txtCercaJugador->TabIndex = 0;
		this->txtCercaJugador->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EstadistiquesJugadorsForm::txtCercaJugador_KeyDown);

		// btnCercar
		this->btnCercar->Text = L"Cercar";
		this->btnCercar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnCercar->Size = System::Drawing::Size(95, 32);
		this->btnCercar->Location = System::Drawing::Point(530, 64);
		this->btnCercar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnCercar->TabIndex = 1;
		this->btnCercar->Click += gcnew System::EventHandler(this, &EstadistiquesJugadorsForm::btnCercar_Click);

		// btnNetejar
		this->btnNetejar->Text = L"Netejar";
		this->btnNetejar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnNetejar->Size = System::Drawing::Size(95, 32);
		this->btnNetejar->Location = System::Drawing::Point(640, 64);
		this->btnNetejar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnNetejar->TabIndex = 2;
		this->btnNetejar->Click += gcnew System::EventHandler(this, &EstadistiquesJugadorsForm::btnNetejar_Click);

		// lblResultatCerca
		this->lblResultatCerca->Text = L"";
		this->lblResultatCerca->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.0F, System::Drawing::FontStyle::Italic);
		this->lblResultatCerca->AutoSize = true;
		this->lblResultatCerca->Location = System::Drawing::Point(30, 105);
		this->lblResultatCerca->ForeColor = System::Drawing::Color::DimGray;

		// dgvEstadistiques
		this->dgvEstadistiques->AllowUserToAddRows = false;
		this->dgvEstadistiques->AllowUserToDeleteRows = false;
		this->dgvEstadistiques->ReadOnly = true;
		this->dgvEstadistiques->BackgroundColor = System::Drawing::Color::White;
		this->dgvEstadistiques->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->dgvEstadistiques->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		this->dgvEstadistiques->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::SystemColors::Control;
		this->dgvEstadistiques->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold);
		this->dgvEstadistiques->Location = System::Drawing::Point(30, 135);
		this->dgvEstadistiques->Name = L"dgvEstadistiques";
		this->dgvEstadistiques->Size = System::Drawing::Size(940, 425);
		this->dgvEstadistiques->TabIndex = 3;
		this->dgvEstadistiques->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
		this->dgvEstadistiques->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;

		// btnTornar
		this->btnTornar->Text = L"Tornar";
		this->btnTornar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnTornar->Size = System::Drawing::Size(100, 35);
		this->btnTornar->Location = System::Drawing::Point(870, 575);
		this->btnTornar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnTornar->TabIndex = 4;
		this->btnTornar->Click += gcnew System::EventHandler(this, &EstadistiquesJugadorsForm::btnTornar_Click);

		this->AcceptButton = this->btnCercar;

		// Afegir controls al formulari
		this->Controls->Add(this->lblTitle);
		this->Controls->Add(this->lblCerca);
		this->Controls->Add(this->txtCercaJugador);
		this->Controls->Add(this->btnCercar);
		this->Controls->Add(this->btnNetejar);
		this->Controls->Add(this->lblResultatCerca);
		this->Controls->Add(this->dgvEstadistiques);
		this->Controls->Add(this->btnTornar);

		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvEstadistiques))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();
	}

	// PRE: els controls estan creats.
	// POST: deixa preparat el disseny del formulari.
	void EstadistiquesJugadorsForm::DesignForm() {
		EstilInterficie::Aplicar(this);
	}

	// PRE: cert.
	// POST: mostra totes les estadistiques disponibles dels jugadors.
	void EstadistiquesJugadorsForm::CarregarEstadistiques() {
		CarregarEstadistiquesFiltrades(L"");
	}

	// PRE: textCerca conte el filtre escrit per l'usuari o una cadena buida.
	// POST: mostra a la taula les estadistiques dels jugadors que coincideixen amb el filtre.
	void EstadistiquesJugadorsForm::CarregarEstadistiquesFiltrades(String^ textCerca) {
		try {
			CtrlVeureEstadistiquesJugadors^ ctrl = gcnew CtrlVeureEstadistiquesJugadors();
			String^ filtre = L"";
			if (textCerca != nullptr) {
				filtre = textCerca->Trim();
			}

			DataTable^ dt = ctrl->CercarEstadistiquesJugadors(filtre);
			this->dgvEstadistiques->DataSource = dt;
			ConfigurarColumnes();

			int total = 0;
			if (dt != nullptr) {
				total = dt->Rows->Count;
			}

			if (String::IsNullOrWhiteSpace(filtre)) {
				this->lblResultatCerca->Text = String::Format(L"{0} jugador(s) carregats.", total);
			}
			else {
				if (total == 0) {
					this->lblResultatCerca->Text = L"No s'ha trobat cap jugador que coincideixi amb la cerca.";
				}
				else {
					this->lblResultatCerca->Text = String::Format(L"{0} resultat(s) trobats per: {1}", total, filtre);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les estad\u00EDstiques: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	// PRE: el DataGridView pot tenir columnes carregades.
	// POST: aplica noms llegibles i estil basic a les columnes.
	void EstadistiquesJugadorsForm::ConfigurarColumnes() {
		if (this->dgvEstadistiques->Columns->Contains(L"IdJugador")) {
			this->dgvEstadistiques->Columns[L"IdJugador"]->Visible = false;
		}
		if (this->dgvEstadistiques->Columns->Contains(L"DataNaixement")) {
			this->dgvEstadistiques->Columns[L"DataNaixement"]->HeaderText = L"Data naixement";
		}
		if (this->dgvEstadistiques->Columns->Contains(L"PartitsJugats")) {
			this->dgvEstadistiques->Columns[L"PartitsJugats"]->HeaderText = L"Partits jugats";
		}
		if (this->dgvEstadistiques->Columns->Contains(L"FaltesLleus")) {
			this->dgvEstadistiques->Columns[L"FaltesLleus"]->HeaderText = L"Faltes lleus";
		}
		if (this->dgvEstadistiques->Columns->Contains(L"FaltesGreus")) {
			this->dgvEstadistiques->Columns[L"FaltesGreus"]->HeaderText = L"Faltes greus";
		}
		if (this->dgvEstadistiques->Columns->Contains(L"MinutsJugats")) {
			this->dgvEstadistiques->Columns[L"MinutsJugats"]->HeaderText = L"Minuts jugats";
		}

		for (int i = 0; i < this->dgvEstadistiques->Columns->Count; i++) {
			this->dgvEstadistiques->Columns[i]->ReadOnly = true;
			this->dgvEstadistiques->Columns[i]->DefaultCellStyle->NullValue = L"";
		}
	}

	// PRE: l'usuari ha premut el boto de cerca.
	// POST: actualitza la taula amb el filtre escrit.
	System::Void EstadistiquesJugadorsForm::btnCercar_Click(System::Object^ sender, System::EventArgs^ e) {
		CarregarEstadistiquesFiltrades(this->txtCercaJugador->Text);
	}

	// PRE: l'usuari ha premut el boto de netejar.
	// POST: esborra el filtre i torna a mostrar tots els jugadors.
	System::Void EstadistiquesJugadorsForm::btnNetejar_Click(System::Object^ sender, System::EventArgs^ e) {
		this->txtCercaJugador->Text = L"";
		CarregarEstadistiques();
		this->txtCercaJugador->Focus();
	}

	// PRE: l'usuari esta escrivint al camp de cerca.
	// POST: si prem Enter, executa la cerca sense afegir cap salt de linia.
	System::Void EstadistiquesJugadorsForm::txtCercaJugador_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
			e->SuppressKeyPress = true;
			btnCercar_Click(sender, e);
		}
	}

	// PRE: l'usuari ha premut el boto de tornar.
	// POST: tanca el formulari d'estadistiques de jugadors.
	System::Void EstadistiquesJugadorsForm::btnTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
}
