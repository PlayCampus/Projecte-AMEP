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

			Form1_Resize(nullptr, nullptr);
		}

Form1::~Form1() {
			if (components)
			{
				delete components;
			}
		}

}
