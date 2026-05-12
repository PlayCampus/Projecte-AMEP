#include "pch.h"
#include "EstadistiquesJugadorsForm.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace MySql::Data::MySqlClient;
	using namespace Playcampus::Domini;

	EstadistiquesJugadorsForm::EstadistiquesJugadorsForm() {
		components = nullptr;
		InitializeComponent();
		DesignForm();
		CarregarEstadistiques();
	}

	EstadistiquesJugadorsForm::~EstadistiquesJugadorsForm() {
		if (components) {
			delete components;
		}
	}

	void EstadistiquesJugadorsForm::InitializeComponent() {
		this->lblTitle = gcnew System::Windows::Forms::Label();
		this->dgvEstadistiques = gcnew System::Windows::Forms::DataGridView();
		this->btnTornar = gcnew System::Windows::Forms::Button();

		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvEstadistiques))->BeginInit();
		this->SuspendLayout();

		// Configuración general del formulario
		this->Text = L"Estadístiques dels Jugadors";
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->StartPosition = FormStartPosition::CenterParent;
		this->ClientSize = System::Drawing::Size(1000, 600);
		this->MinimizeBox = false;
		this->MaximizeBox = false;
		this->BackColor = System::Drawing::Color::White;
		this->ControlBox = false;

		// lblTitle
		this->lblTitle->Text = L"Estadístiques dels Jugadors";
		this->lblTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.0F, System::Drawing::FontStyle::Bold);
		this->lblTitle->AutoSize = true;
		this->lblTitle->Location = System::Drawing::Point(30, 20);
		this->lblTitle->ForeColor = System::Drawing::Color::Black;

		// dgvEstadistiques
		this->dgvEstadistiques->AllowUserToAddRows = false;
		this->dgvEstadistiques->AllowUserToDeleteRows = false;
		this->dgvEstadistiques->ReadOnly = true;
		this->dgvEstadistiques->BackgroundColor = System::Drawing::Color::White;
		this->dgvEstadistiques->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->dgvEstadistiques->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		this->dgvEstadistiques->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::SystemColors::Control;
		this->dgvEstadistiques->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold);
		this->dgvEstadistiques->Location = System::Drawing::Point(30, 60);
		this->dgvEstadistiques->Name = L"dgvEstadistiques";
		this->dgvEstadistiques->Size = System::Drawing::Size(940, 480);
		this->dgvEstadistiques->TabIndex = 1;
		this->dgvEstadistiques->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;

		// btnTornar
		this->btnTornar->Text = L"Tornar";
		this->btnTornar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnTornar->Size = System::Drawing::Size(100, 35);
		this->btnTornar->Location = System::Drawing::Point(870, 550);
		this->btnTornar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnTornar->Click += gcnew System::EventHandler(this, &EstadistiquesJugadorsForm::btnTornar_Click);

		// Agregar controles al formulario
		this->Controls->Add(this->lblTitle);
		this->Controls->Add(this->dgvEstadistiques);
		this->Controls->Add(this->btnTornar);

		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvEstadistiques))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();
	}

	void EstadistiquesJugadorsForm::DesignForm() {
		// Configuración adicional de diseño si es necesaria
	}

	void EstadistiquesJugadorsForm::CarregarEstadistiques() {
		try {
			// Crear instancia del controlador
			CtrlVeureEstadistiquesJugadors^ ctrl = gcnew CtrlVeureEstadistiquesJugadors();

			// Obtener estadísticas de un jugador específico
			// Nota: Esta es una solución temporal. Si necesitas todas las estadísticas,
			// deberías ampliar el controlador con un método que retorne todos los jugadores.
			// Por ahora, usaremos ObtenirEstadistiquesJugador con un ID específico o
			// modificaremos el enfoque.

			// Crear una consulta SQL directa para obtener todos los jugadores
			DataTable^ dt = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(Playcampus::Dades::ConnexioBD::ObtenirConnectionString());

			try {
				conn->Open();
				String^ query =
					"SELECT u.identificador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS Posicio, "
					"j.partitsJugats AS PartitsJugats, j.anotacions AS Anotacions, j.assistencies AS Assistencies, "
					"j.faltesLleus AS FaltesLleus, j.faltesGreus AS FaltesGreus, j.minutsJugats AS MinutsJugats "
					"FROM Jugador j INNER JOIN Usuari u ON j.idJugador = u.identificador "
					"ORDER BY u.nom ASC";

				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(dt);

				// Asignar los datos al DataGridView
				this->dgvEstadistiques->DataSource = dt;

				// Ajustar estilos de las columnas
				for each (DataGridViewColumn^ col in this->dgvEstadistiques->Columns) {
					col->ReadOnly = true;
				}

				// Si la tabla está vacía, mostrar mensaje informativo
				if (dt->Rows->Count == 0) {
					MessageBox::Show(L"No s'han trobat estadístiques de jugadors.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al cargar las estadísticas: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void EstadistiquesJugadorsForm::btnTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
}
