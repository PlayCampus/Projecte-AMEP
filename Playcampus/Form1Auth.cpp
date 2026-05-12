#include "pch.h"
#include "Form1Auth.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::btnShowLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlInici->Visible = false;
		pnlLogin->Visible = true;
	}

System::Void Form1::btnShowRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlInici->Visible = false;
		pnlRegister->Visible = true;
	}

System::Void Form1::btnShowRegisterFromLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlLogin->Visible = false;
		pnlRegister->Visible = true;
	}

System::Void Form1::cmbRegTipus_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ tipus = cmbRegTipus->Text;
		if (tipus == L"Capità" || tipus == L"Administrador") {
			lblRegTelefon->Visible = true;
			txtRegTelefon->Visible = true;
		}
		else {
			lblRegTelefon->Visible = false;
			txtRegTelefon->Visible = false;
		}
	}

System::Void Form1::btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlLogin->Visible = false;
		pnlRegister->Visible = false;
		pnlInici->Visible = true;
	}

System::Void Form1::btnLoginAct_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ correu = txtLoginCorreu->Text;
		String^ pass = txtLoginPass->Text;

		try {
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			bool valid = ctrlInici->IniciarSessio(correu, pass);
			if (valid) {
				currentUsuariTipus = ctrlInici->ObtenirTipusUsuari(correu);
				currentUsuariCorreu = correu;
				pnlLogin->Visible = false;
				pnlMain->Visible = true;
				pnlMain->BringToFront();
				pnlRegister->Visible = false;
				pnlConsultar->Visible = false;
				pnlCrearLliga->Visible = false;
				pnlGestionarLliga->Visible = false;
				pnlEnregistrarEquip->Visible = false;
				pnlGestionarEquip->Visible = false;
				pnlAfegirJugador->Visible = false;

				// --- LÒGICA ADMINISTRADOR ---
				if (currentUsuariTipus->ToLower() == "administrador") {
					btnCrearLligaMainMenu->Visible = true;
					Playcampus::Domini::CtrlCrearLliga^ ctrlCrear = gcnew Playcampus::Domini::CtrlCrearLliga();
					if (ctrlCrear->TeLligaActiva(currentUsuariCorreu)) {
						btnCrearLligaMainMenu->Text = L"Gestionar Lliga";
					}
					else {
						btnCrearLligaMainMenu->Text = L"Crear Lliga";
					}
				}
				else {
					btnCrearLligaMainMenu->Visible = false;
				}

				// --- LÒGICA CAPITÀ ---
				if (currentUsuariTipus->ToLower() == "capita") {
					btnEnregistrarEquip->Visible = true;
					btnUnirEquipLliga->Visible = true;

					// NOU: Mostrem el botó de gestionar convocatòries
					if (btnGestionarConvocatoria != nullptr) {
						btnGestionarConvocatoria->Visible = true;
						btnGestionarConvocatoria->BringToFront();
					}

					if (ctrlInici->CapitaTeEquip(currentUsuariCorreu)) {
						btnEnregistrarEquip->Text = L"Gestionar Equip";
					}
					else {
						btnEnregistrarEquip->Text = L"Enregistrar Equip";
					}

					if (ctrlInici->EquipEstaEnLliga(currentUsuariCorreu)) {
						btnUnirEquipLliga->Text = L"Abandonar Lliga";
					}
					else {
						btnUnirEquipLliga->Text = L"Unir equip a lliga";
					}

				}
				else {
					btnEnregistrarEquip->Visible = false;
					btnUnirEquipLliga->Visible = false;
					if (btnGestionarConvocatoria != nullptr) btnGestionarConvocatoria->Visible = false;
				}

				// --- LÒGICA JUGADOR (NOU CARTELL) ---
				if (currentUsuariTipus->ToLower() == "jugador") {
					Playcampus::Domini::CtlrConvocarJugadors^ ctrlConv = gcnew Playcampus::Domini::CtlrConvocarJugadors();
					auto avis = ctrlConv->ObtenirAvisPendent(currentUsuariCorreu);

					if (avis != nullptr) {
						idPartitPendentConfirmar = avis["idPartit"];
						MostrarAvisJugador(avis["missatge"] + L"\n\nPots assistir-hi?");
					}
				}

				txtLoginCorreu->Text = "";
				txtLoginPass->Text = "";

				// Forcem a redibuixar la pantalla amb els nous botons
				Form1_Resize(nullptr, nullptr);
			}
			else {
				MessageBox::Show(L"Credencials incorrectes.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en iniciar sessió: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnRegAct_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtRegNom->Text;
		String^ correu = txtRegCorreu->Text;
		String^ pass = txtRegPass->Text;
		String^ tipus = cmbRegTipus->Text;
		String^ telefon = txtRegTelefon->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(correu) || String::IsNullOrEmpty(pass)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		if ((tipus == L"Capita" || tipus == L"Administrador") && String::IsNullOrEmpty(telefon)) {
			MessageBox::Show(L"Cal introduir el telèfon per al capità i administrador.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlRegistrarUsuari^ ctrlReg = gcnew Playcampus::Domini::CtrlRegistrarUsuari();
			ctrlReg->CrearUsuari(nom, pass, DateTime::Now, correu, tipus, telefon);
			MessageBox::Show(L"Usuari registrat correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			pnlRegister->Visible = false;
			pnlInici->Visible = true;

			txtRegNom->Text = L"";
			txtRegCorreu->Text = L"";
		txtRegPass->Text = L"";
			cmbRegTipus->SelectedIndex = 0;
			txtRegTelefon->Text = L"";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al registrar: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		Playcampus::Domini::CtrlTancarSessio^ ctrlTancar = gcnew Playcampus::Domini::CtrlTancarSessio();
		ctrlTancar->TancarSessio();

		currentUsuariTipus = L"";
		currentUsuariCorreu = L"";
		pnlConsultar->Visible = false;
		pnlCrearLliga->Visible = false;
		pnlGestionarLliga->Visible = false;
		pnlEnregistrarEquip->Visible = false;
		pnlGestionarEquip->Visible = false;
		pnlAfegirJugador->Visible = false;
		pnlEstadistiques->Visible = false;
		pnlMain->Visible = false;
		pnlInici->Visible = true;
	}


}
