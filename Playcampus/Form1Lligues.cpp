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

System::Void Form1::btnGLMostrarEquips_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultaLligues^ ctrl = gcnew Playcampus::Domini::CtrlConsultaLligues();
			String^ nomLliga = ctrl->ObtenirNomLligaAdministrador(currentUsuariCorreu);
			if (String::IsNullOrWhiteSpace(nomLliga)) {
				MessageBox::Show(L"No tens cap lliga activa associada.", L"Avis", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else {
				MostrarConsultaGeneral(L"Equips de " + nomLliga, ctrl->ObtenirEquipsDeLaLligaAdministrador(currentUsuariCorreu));
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant els equips: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGLEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultaLligues^ ctrl = gcnew Playcampus::Domini::CtrlConsultaLligues();
			DataTable^ equips = ctrl->ObtenirEquipsDeLaLligaAdministrador(currentUsuariCorreu);
			if (equips == nullptr || equips->Rows->Count == 0) {
				MessageBox::Show(L"No hi ha equips dins de la teva lliga activa.", L"Avis", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				Form^ finestra = gcnew Form();
				finestra->Text = L"Esborrar equip de la lliga";
				finestra->StartPosition = FormStartPosition::CenterParent;
				finestra->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				finestra->ClientSize = System::Drawing::Size(430, 150);
				finestra->MinimizeBox = false;
				finestra->MaximizeBox = false;

				Label^ lblEquip = gcnew Label();
				lblEquip->Text = L"Selecciona l'equip:";
				lblEquip->Location = System::Drawing::Point(20, 20);
				lblEquip->AutoSize = true;

				ComboBox^ cmbEquips = gcnew ComboBox();
				cmbEquips->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbEquips->Location = System::Drawing::Point(20, 50);
				cmbEquips->Size = System::Drawing::Size(390, 24);

				for each (DataRow^ fila in equips->Rows) {
					cmbEquips->Items->Add(fila[L"Equip"]->ToString() + L" (" + fila[L"IdEquip"]->ToString() + L")");
				}
				cmbEquips->SelectedIndex = 0;

				Button^ btnConfirmar = gcnew Button();
				btnConfirmar->Text = L"Esborrar";
				btnConfirmar->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnConfirmar->Location = System::Drawing::Point(220, 100);
				btnConfirmar->Size = System::Drawing::Size(90, 30);

				Button^ btnCancelar = gcnew Button();
				btnCancelar->Text = L"Cancelar";
				btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelar->Location = System::Drawing::Point(320, 100);
				btnCancelar->Size = System::Drawing::Size(90, 30);

				finestra->Controls->Add(lblEquip);
				finestra->Controls->Add(cmbEquips);
				finestra->Controls->Add(btnConfirmar);
				finestra->Controls->Add(btnCancelar);
				finestra->AcceptButton = btnConfirmar;
				finestra->CancelButton = btnCancelar;

				if (finestra->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
					DataRow^ filaSeleccionada = equips->Rows[cmbEquips->SelectedIndex];
					String^ idEquip = filaSeleccionada[L"IdEquip"]->ToString();
					String^ nomEquip = filaSeleccionada[L"Equip"]->ToString();

					System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
						L"Vols treure l'equip '" + nomEquip + L"' de la lliga?",
						L"Confirmació",
						MessageBoxButtons::YesNo,
						MessageBoxIcon::Warning);

					if (confirmacio == System::Windows::Forms::DialogResult::Yes) {
						ctrl->TreureEquipDeLaLliga(idEquip, currentUsuariCorreu);
						MessageBox::Show(L"Equip tret de la lliga correctament.", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en esborrar l'equip de la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGL_EnDesenvolupament_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(L"Funcionalitat en desenvolupament.");
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

System::Void Form1::btnGLRetirarTemporada_Click(System::Object^ sender, System::EventArgs^ e) {
				System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
					L"Estàs segur que vols retirar la temporada activa respecte a la teva Lliga?",
					L"Confirmació",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Warning
				);

				if (confirmacio == System::Windows::Forms::DialogResult::Yes) {
					try {
						// Es fa servir la teva classe CtrlRetirarTemporada que ja inclous.
						Playcampus::Domini::CtrlRetirarTemporada^ ctrl = gcnew Playcampus::Domini::CtrlRetirarTemporada();

						// Assumint que el mètode accepti el correu de l'administrador per saber-ne la lliga activa:
						ctrl->RetirarTemporada(currentUsuariCorreu); // *Nota: Si la funció d'aquest controlador es diu diferent o prent un altre paràmetre, adapta aquest mètode aquí pel que posa a "CtrlRetirarTemporada.hxx".

						MessageBox::Show(L"La temporada i les seves jornades han estat retirades correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (Exception^ ex) {
						MessageBox::Show(L"Error al retirar la temporada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}

}
