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
		if (tipus == L"Capita" || tipus == L"Capità" || tipus == L"Administrador") {
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

						// EN VEZ DE AÑADIR EL TEXTO "Pots assistir-hi?", PASAMOS EL TIPO DE AVISO
						// El controlador ya se encarga de poner el texto correcto según si está convocado o no
						MostrarAvisJugador(avis["missatge"], avis["tipus"]);
					}
				}


				String^ tipusNormalitzat = currentUsuariTipus->ToLower();
				if (this->btnMenuConsultarTelefons != nullptr) {
					this->btnMenuConsultarTelefons->Visible = (tipusNormalitzat == "jugador");
				}
				if (this->btnGEConsultarTelefons != nullptr) {
					this->btnGEConsultarTelefons->Visible = (tipusNormalitzat == "capita");
				}
				if (this->btnGLConsultarTelefons != nullptr) {
					this->btnGLConsultarTelefons->Visible = (tipusNormalitzat == "administrador");
				}
				if (this->btnGLEsborrarJornada != nullptr) {
					this->btnGLEsborrarJornada->Visible = (tipusNormalitzat == "administrador");
				}

				if (this->btnSeguirLligaMainMenu != nullptr) {
					this->btnSeguirLligaMainMenu->Visible = true;
					ActualitzarEstatSeguirLliga();
				}

				CarregarUltimsFitxatges();

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
		pnlEstadistiquesEquipDetail->Visible = false;
		pnlEstadistiquesLligaDetail->Visible = false;
		pnlMain->Visible = false;
		pnlInici->Visible = true;
		if (this->btnMenuConsultarTelefons != nullptr) this->btnMenuConsultarTelefons->Visible = false;
		if (this->btnGEConsultarTelefons != nullptr) this->btnGEConsultarTelefons->Visible = false;
		if (this->btnGLConsultarTelefons != nullptr) this->btnGLConsultarTelefons->Visible = false;

       if (this->btnSeguirLligaMainMenu != nullptr) {
			this->btnSeguirLligaMainMenu->Visible = false;
			this->btnSeguirLligaMainMenu->Text = L"Seguir Lliga";
		}
		if (this->pnlDashboardLliga != nullptr) this->pnlDashboardLliga->Visible = false;
		if (this->picImatge != nullptr) this->picImatge->Visible = true;
	}

	System::String^ Form1::DemanarNomLliga(System::String^ titol, System::String^ missatge) {
		Form^ dlg = gcnew Form();
		dlg->Text = titol;
        dlg->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		dlg->StartPosition = FormStartPosition::CenterParent;
		dlg->MinimizeBox = false;
		dlg->MaximizeBox = false;
		dlg->ClientSize = System::Drawing::Size(420, 140);

		Label^ lbl = gcnew Label();
		lbl->Text = missatge;
		lbl->AutoSize = false;
		lbl->Size = System::Drawing::Size(390, 40);
		lbl->Location = System::Drawing::Point(15, 10);

		TextBox^ txt = gcnew TextBox();
		txt->Size = System::Drawing::Size(390, 22);
		txt->Location = System::Drawing::Point(15, 55);

		Button^ ok = gcnew Button();
		ok->Text = L"OK";
		ok->DialogResult = System::Windows::Forms::DialogResult::OK;
		ok->Location = System::Drawing::Point(235, 95);
		ok->Size = System::Drawing::Size(80, 30);

		Button^ cancel = gcnew Button();
		cancel->Text = L"Cancel·lar";
		cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		cancel->Location = System::Drawing::Point(325, 95);
		cancel->Size = System::Drawing::Size(80, 30);

		dlg->AcceptButton = ok;
		dlg->CancelButton = cancel;
		dlg->Controls->Add(lbl);
		dlg->Controls->Add(txt);
		dlg->Controls->Add(ok);
		dlg->Controls->Add(cancel);

     System::Windows::Forms::DialogResult r = dlg->ShowDialog(this);
		String^ value = nullptr;
        if (r == System::Windows::Forms::DialogResult::OK) {
			value = txt->Text;
		}
		delete dlg;
		return value;
	}

	void Form1::CarregarDashboardLliga(System::String^ idLliga) {
		if (String::IsNullOrEmpty(idLliga)) return;
		Playcampus::Domini::CtrlSeguirLliga^ ctrl = gcnew Playcampus::Domini::CtrlSeguirLliga();
		String^ nom = ctrl->ObtenirNomLligaPerId(idLliga);
		if (this->lblDashboardLliga != nullptr) {
			this->lblDashboardLliga->Text = String::IsNullOrEmpty(nom) ? L"" : (L"Lliga: " + nom);
		}
		if (this->dgvDashboardClassificacio != nullptr) {
			this->dgvDashboardClassificacio->DataSource = ctrl->ObtenirClassificacioLliga(idLliga);
		}
		if (this->dgvDashboardProximsPartits != nullptr) {
			this->dgvDashboardProximsPartits->DataSource = ctrl->ObtenirProximsPartits(idLliga, 5);
		}
		if (this->dgvDashboardUltimsResultats != nullptr) {
			this->dgvDashboardUltimsResultats->DataSource = ctrl->ObtenirUltimsResultats(idLliga, 5);
		}

		if (this->pnlDashboardLliga != nullptr) this->pnlDashboardLliga->Visible = true;
		if (this->picImatge != nullptr) this->picImatge->Visible = false;
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::ActualitzarEstatSeguirLliga() {
		if (String::IsNullOrEmpty(currentUsuariCorreu) || this->btnSeguirLligaMainMenu == nullptr) return;
		try {
			Playcampus::Domini::CtrlSeguirLliga^ ctrl = gcnew Playcampus::Domini::CtrlSeguirLliga();
			String^ id = ctrl->ObtenirIdLligaSeguida(currentUsuariCorreu);
			if (!String::IsNullOrEmpty(id)) {
				this->btnSeguirLligaMainMenu->Text = L"Deixar de seguir lliga actual";
				CarregarDashboardLliga(id);
			}
			else {
				this->btnSeguirLligaMainMenu->Text = L"Seguir Lliga";
				if (this->pnlDashboardLliga != nullptr) this->pnlDashboardLliga->Visible = false;
				if (this->picImatge != nullptr) this->picImatge->Visible = true;
			}
		}
		catch (Exception^) {
			this->btnSeguirLligaMainMenu->Text = L"Seguir Lliga";
			if (this->pnlDashboardLliga != nullptr) this->pnlDashboardLliga->Visible = false;
			if (this->picImatge != nullptr) this->picImatge->Visible = true;
		}
	}

	System::Void Form1::btnSeguirLligaMainMenu_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(currentUsuariCorreu)) return;
		try {
			Playcampus::Domini::CtrlSeguirLliga^ ctrl = gcnew Playcampus::Domini::CtrlSeguirLliga();
			String^ idActual = ctrl->ObtenirIdLligaSeguida(currentUsuariCorreu);

			if (!String::IsNullOrEmpty(idActual)) {
				auto r = MessageBox::Show(L"Estàs segur que vols deixar de seguir la lliga?", L"Confirmació", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
				if (r == System::Windows::Forms::DialogResult::Yes) {
					ctrl->DeixarDeSeguir(currentUsuariCorreu);
					ActualitzarEstatSeguirLliga();
				}
				return;
			}

			String^ nomLliga = DemanarNomLliga(L"Seguir Lliga", L"Introdueix el nom de la lliga que vols seguir:");
			if (String::IsNullOrWhiteSpace(nomLliga)) return;

			ctrl->SeguirLliga(currentUsuariCorreu, nomLliga->Trim());
			String^ id = ctrl->ObtenirIdLligaPerNom(nomLliga->Trim());
			this->btnSeguirLligaMainMenu->Text = L"Deixar de seguir lliga actual";
			CarregarDashboardLliga(id);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error: " + ex->Message, L"Seguir Lliga", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

}
