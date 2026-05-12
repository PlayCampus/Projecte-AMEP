#include "pch.h"
#include "Form1Consultes.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::btnConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlConsultar->Visible = true;
		txtNomLliga->Text = L"";
	}

System::Void Form1::btnTornarConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlConsultar->Visible = false;
		pnlMain->Visible = true;
		txtNomLliga->Text = L"";
	}

System::Void Form1::btnComprovarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtNomLliga->Text;
		try {
			Playcampus::Domini::CtrlCrearLliga^ ctrlTornar = gcnew Playcampus::Domini::CtrlCrearLliga();
			bool check = ctrlTornar->ExisteixLliga(nom);
			if (check) MessageBox::Show(L"Aquesta lliga ja existeix");
			else MessageBox::Show(L"Aquesta lliga no existeix");
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error : " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::MostrarTaulaConsulta(System::String^ titol, System::Data::DataTable^ dades) {
		Form^ finestra = gcnew Form();
		finestra->Text = titol;
		finestra->StartPosition = FormStartPosition::CenterParent;
		finestra->Size = System::Drawing::Size(950, 520);
		finestra->MinimizeBox = false;
		finestra->MaximizeBox = true;

		DataGridView^ graella = gcnew DataGridView();
		graella->Dock = DockStyle::Fill;
		graella->ReadOnly = true;
		graella->AllowUserToAddRows = false;
		graella->AllowUserToDeleteRows = false;
		graella->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
		graella->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		graella->DataSource = dades;

		Button^ btnTancar = gcnew Button();
		btnTancar->Text = L"Tancar";
		btnTancar->Dock = DockStyle::Bottom;
		btnTancar->Height = 35;
		btnTancar->DialogResult = System::Windows::Forms::DialogResult::OK;

		finestra->Controls->Add(graella);
		finestra->Controls->Add(btnTancar);
		finestra->AcceptButton = btnTancar;
		finestra->ShowDialog(this);
	}

System::Void Form1::MostrarConsultaGeneral(System::String^ titol, System::Data::DataTable^ dades) {
		if (dades == nullptr || dades->Rows->Count == 0) {
			MessageBox::Show(L"No hi ha dades per mostrar.", titol, MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			MostrarTaulaConsulta(titol, dades);
		}
	}

System::Void Form1::btnProgPartits_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Programació de partits", ctrl->ObtenirProgramacioPartits());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant la programacio de partits: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnEstatLligues_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Estat de les lligues", ctrl->ObtenirEstatLligues());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant l'estat de les lligues: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}


}
