#include "pch.h"
#include "EditarJugadorForm.h"
#include "Domini/CtrlEditarJugador.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace Playcampus::Domini;

	EditarJugadorForm::EditarJugadorForm(String^ idJugador, String^ nom, int dorsal, String^ posicio) {
		jugadorId = idJugador;
		jugadorNom = nom;
		jugadorDorsal = dorsal;
		jugadorPosicio = posicio;
		correuCapita = nullptr;

		components = nullptr;
		InitializeComponent();
		DesignForm();
	}

	void EditarJugadorForm::InitializeComponent() {
		this->lblTitle = gcnew System::Windows::Forms::Label();
		this->lblNom = gcnew System::Windows::Forms::Label();
		this->txtNom = gcnew System::Windows::Forms::TextBox();
		this->lblDorsal = gcnew System::Windows::Forms::Label();
		this->txtDorsal = gcnew System::Windows::Forms::TextBox();
		this->lblPosicio = gcnew System::Windows::Forms::Label();
		this->txtPosicio = gcnew System::Windows::Forms::TextBox();
		this->btnGuardar = gcnew System::Windows::Forms::Button();
		this->btnCancelar = gcnew System::Windows::Forms::Button();

		// Configuración general del formulario
		this->Text = L"Editar Jugador";
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->StartPosition = FormStartPosition::CenterParent;
		this->ClientSize = System::Drawing::Size(400, 280);
		this->MinimizeBox = false;
		this->MaximizeBox = false;
		this->BackColor = System::Drawing::Color::White;

		// lblTitle
		this->lblTitle->Text = L"Editar Jugador";
		this->lblTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.0F, System::Drawing::FontStyle::Bold);
		this->lblTitle->AutoSize = true;
		this->lblTitle->Location = System::Drawing::Point(30, 20);

		// lblNom
		this->lblNom->Text = L"Nom:";
		this->lblNom->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->lblNom->AutoSize = true;
		this->lblNom->Location = System::Drawing::Point(30, 60);

		// txtNom
		this->txtNom->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->txtNom->Size = System::Drawing::Size(320, 24);
		this->txtNom->Location = System::Drawing::Point(30, 85);
		this->txtNom->Text = jugadorNom;
		this->txtNom->ReadOnly = true; // Solo lectura: no modificable

		// lblDorsal
		this->lblDorsal->Text = L"Dorsal:";
		this->lblDorsal->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->lblDorsal->AutoSize = true;
		this->lblDorsal->Location = System::Drawing::Point(30, 120);

		// txtDorsal
		this->txtDorsal->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->txtDorsal->Size = System::Drawing::Size(320, 24);
		this->txtDorsal->Location = System::Drawing::Point(30, 145);
		this->txtDorsal->Text = jugadorDorsal.ToString();

		// lblPosicio
		this->lblPosicio->Text = L"Posició:";
		this->lblPosicio->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->lblPosicio->AutoSize = true;
		this->lblPosicio->Location = System::Drawing::Point(30, 180);

		// txtPosicio
		this->txtPosicio->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->txtPosicio->Size = System::Drawing::Size(320, 24);
		this->txtPosicio->Location = System::Drawing::Point(30, 205);
		this->txtPosicio->Text = (String::IsNullOrEmpty(jugadorPosicio) ? L"" : jugadorPosicio);

		// btnGuardar
		this->btnGuardar->Text = L"Guardar";
		this->btnGuardar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnGuardar->Size = System::Drawing::Size(150, 35);
		this->btnGuardar->Location = System::Drawing::Point(50, 240);
		this->btnGuardar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGuardar->Click += gcnew System::EventHandler(this, &EditarJugadorForm::btnGuardar_Click);

		// btnCancelar
		this->btnCancelar->Text = L"Cancelar";
		this->btnCancelar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F);
		this->btnCancelar->Size = System::Drawing::Size(150, 35);
		this->btnCancelar->Location = System::Drawing::Point(210, 240);
		this->btnCancelar->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->btnCancelar->Click += gcnew System::EventHandler(this, &EditarJugadorForm::btnCancelar_Click);

		// Agregar controles al formulario
		this->Controls->Add(this->lblTitle);
		this->Controls->Add(this->lblNom);
		this->Controls->Add(this->txtNom);
		this->Controls->Add(this->lblDorsal);
		this->Controls->Add(this->txtDorsal);
		this->Controls->Add(this->lblPosicio);
		this->Controls->Add(this->txtPosicio);
		this->Controls->Add(this->btnGuardar);
		this->Controls->Add(this->btnCancelar);

		this->AcceptButton = this->btnGuardar;
		this->CancelButton = this->btnCancelar;
	}

	void EditarJugadorForm::DesignForm() {
		// Configuración adicional de diseño si es necesaria
	}

	System::Void EditarJugadorForm::btnGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ dorsalText = this->txtDorsal->Text;

		// Validar que el dorsal sea un número válido
		int dorsal = 0;
		if (String::IsNullOrWhiteSpace(dorsalText)) {
			MessageBox::Show(L"El dorsal no puede estar vacío.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (!Int32::TryParse(dorsalText, dorsal) || dorsal < 0) {
			MessageBox::Show(L"El dorsal ha de ser un número enter positiu.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Validar que la posició no estigui buida
		if (String::IsNullOrWhiteSpace(this->txtPosicio->Text)) {
			MessageBox::Show(L"La posció no pot estar buida.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			// Connectar amb el controlador
			CtrlEditarJugador^ ctrl = gcnew CtrlEditarJugador();
			String^ posicio = this->txtPosicio->Text;

			// Actualitzar el jugador a la base de dades
			ctrl->ActualitzarJugador(correuCapita, jugadorId, dorsal, posicio);

			// Actualizar los datos del jugador con los valores editados
			jugadorDorsal = dorsal;
			jugadorPosicio = posicio;

			MessageBox::Show(L"Jugador actualitzat correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Cerrar el formulario con resultado OK
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void EditarJugadorForm::btnCancelar_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
	}
}
