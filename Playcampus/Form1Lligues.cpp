#include "pch.h"
#include "Form1Lligues.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::btnCrearLligaMainMenu_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnCrearLligaMainMenu->Text == L"Gestionar Lliga") {
			pnlMain->Visible = false;
			pnlGestionarLliga->Visible = true;
			return;
		}
		pnlMain->Visible = false;
		pnlCrearLliga->Visible = true;
		txtCLNom->Text = L"";
		txtCLPass->Text = L"";
		cmbCLEsport->SelectedIndex = -1;
	}

System::Void Form1::btnGLTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarLliga->Visible = false;
		pnlMain->Visible = true;
	}

System::Void Form1::btnCLTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearLliga->Visible = false;
		pnlMain->Visible = true;
	}

System::Void Form1::btnCLGuarda_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtCLNom->Text;
		String^ pass = txtCLPass->Text;
		String^ esport = cmbCLEsport->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(pass) || String::IsNullOrEmpty(esport)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		Playcampus::Domini::Disciplina disc;
		if (esport == L"Futbol") disc = Playcampus::Domini::Disciplina::Futbol;
		else if (esport == L"Basquet") disc = Playcampus::Domini::Disciplina::Basquet;
		else if (esport == L"Voley") disc = Playcampus::Domini::Disciplina::Voley;
		else disc = Playcampus::Domini::Disciplina::Futbol;

		try {
			Playcampus::Domini::CtrlCrearLliga^ ctrlCrear = gcnew Playcampus::Domini::CtrlCrearLliga();
			// El mètode CrearLliga requereix: idLliga, nom, disciplina, descripcio, contrasenya, tipusUsuari, correuUsuari
			// Generem un ID aleatori o utilitzem el nom com a ID base per fer-ho simple.
			String^ idLliga = "L-" + Guid::NewGuid().ToString()->Substring(0, 8);

			ctrlCrear->CrearLliga(idLliga, nom, disc, L"Nova Lliga " + nom, pass, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Lliga creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			
			btnCrearLligaMainMenu->Text = L"Gestionar Lliga";

			pnlCrearLliga->Visible = false;
			pnlMain->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear lliga: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGL_EnDesenvolupament_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(L"Funcionalitat en desenvolupament.");
	}


}
