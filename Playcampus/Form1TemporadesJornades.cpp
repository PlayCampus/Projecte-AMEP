#include "pch.h"
#include "Form1TemporadesJornades.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::btnGLCrearJornada_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearJornada->Visible = true;

			// txtCJNomLliga is no longer required, ignored
			cmbCJTemporada->Items->Clear();
			cjTemporadaIds->Clear();
			dtpCJDataInici->Value = DateTime::Now;
			dtpCJDataFi->Value = DateTime::Now.AddDays(7); // Acostuma a durar 1 setmana

			try {
				Playcampus::Domini::CtrlCrearJornada^ ctrl = gcnew Playcampus::Domini::CtrlCrearJornada();
				String^ nomLliga = ctrl->ObtenirNomLligaAdministrador(currentUsuariCorreu);

				if (String::IsNullOrEmpty(nomLliga)) {
					MessageBox::Show(L"No ets administrador de cap lliga.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				// Obtenir temporades de la lliga
				System::Collections::Generic::List<System::Collections::Generic::Dictionary<String^, String^>^>^ temporades = ctrl->ObtenirTemporadesLliga(nomLliga);

				for each (auto temp in temporades) {
					String^ display = temp["dataInici"] + L" - " + temp["dataFi"];
					cmbCJTemporada->Items->Add(display);
					cjTemporadaIds->Add(temp["idTemporada"]);
				}

				if (cmbCJTemporada->Items->Count > 0) {
					cmbCJTemporada->SelectedIndex = 0;
				} else {
					MessageBox::Show(L"No s'han trobat temporades per a aquesta lliga.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}

			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar temporades: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

System::Void Form1::btnCJCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearJornada->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

System::Void Form1::btnCJBuscarTemporades_Click(System::Object^ sender, System::EventArgs^ e) {
		// Aquest botó ja no fa res, l'obtenció és automàtica en obrir el panel
	}

System::Void Form1::btnCJConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbCJTemporada->SelectedIndex == -1) {
			MessageBox::Show(L"Si us plau, cerca i selecciona una Temporada.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int numJornada = 0; 
		if (!Int32::TryParse(txtCJNumero->Text, numJornada)) {
			MessageBox::Show(L"Introdueix un número de jornada vàlid.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		DateTime dataInici = dtpCJDataInici->Value;
		DateTime dataFi = dtpCJDataFi->Value;

		if (dataFi <= dataInici) {
			MessageBox::Show(L"La data de fi ha de ser posterior a la data d'inici.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			
			Playcampus::Domini::CtrlCrearJornada^ ctrl = gcnew Playcampus::Domini::CtrlCrearJornada();
			String^ idTemporadaSelecionada = cjTemporadaIds[cmbCJTemporada->SelectedIndex];
			String^ estat = L"Proxim"; // Per defecte

			ctrl->CrearJornada(idTemporadaSelecionada, numJornada, dataInici, dataFi, estat);
			
			MessageBox::Show(L"Jornada creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			pnlCrearJornada->Visible = false;
			pnlGestionarLliga->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al desar la jornada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGLCrearTemporada_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearTemporada->Visible = true;
			dtpCTDataInici->Value = DateTime::Now;
			dtpCTDataFi->Value = DateTime::Now.AddMonths(6); // Por defecto acaba en 6 meses
		}

System::Void Form1::btnCTCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearTemporada->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

System::Void Form1::btnCTConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		DateTime dataInici = dtpCTDataInici->Value;
		DateTime dataFi = dtpCTDataFi->Value;

		if (dataFi <= dataInici) {
			MessageBox::Show(L"La data de fi ha de ser posterior a la data d'inici.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			// Instanciar el controlador y llamar a la BD usando el correu del administrador (omitiendo el nom de la liga)
			Playcampus::Domini::CtrlCrearTemporada^ ctrl = gcnew Playcampus::Domini::CtrlCrearTemporada();
			ctrl->CrearTemporada(dataInici, dataFi, currentUsuariCorreu);

			MessageBox::Show(L"Temporada creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			pnlCrearTemporada->Visible = false;
			pnlGestionarLliga->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear la temporada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}


System::Void Form1::btnGLEsborrarJornada_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"administrador") {
			MessageBox::Show(L"Només els administradors poden esborrar jornades.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		pnlGestionarLliga->Visible = false;
		pnlEsborrarJornada->Visible = true;
		pnlEsborrarJornada->BringToFront();
		CarregarTemporadesEsborrarJornada();
	}

System::Void Form1::btnEJTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEsborrarJornada->Visible = false;
		pnlGestionarLliga->Visible = true;
		pnlGestionarLliga->BringToFront();
	}

void Form1::CarregarTemporadesEsborrarJornada() {
		cmbEJTemporades->Items->Clear();
		ejTemporadaIds->Clear();
		cmbEJJornades->Items->Clear();
		ejJornadaIds->Clear();

		try {
			Playcampus::Domini::CtrlEsborrarJornada^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarJornada();
			auto temporades = ctrl->ObtenirTemporadesAdmin(currentUsuariCorreu);

			if (temporades == nullptr || temporades->Count == 0) {
				MessageBox::Show(L"Aquest administrador no té cap lliga associada o no hi ha temporades disponibles per a la seva lliga.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			for each(auto dict in temporades) {
				String^ display = dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
				cmbEJTemporades->Items->Add(display);
				ejTemporadaIds->Add(dict["idTemporada"]);
			}

			if (cmbEJTemporades->Items->Count > 0) cmbEJTemporades->SelectedIndex = 0;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar temporades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::cmbEJTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cmbEJJornades->Items->Clear();
		ejJornadaIds->Clear();

		if (cmbEJTemporades->SelectedIndex >= 0) {
			String^ idTemporadaStr = ejTemporadaIds[cmbEJTemporades->SelectedIndex];

			try {
				Playcampus::Domini::CtrlEsborrarJornada^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarJornada();
				auto jornades = ctrl->ObtenirJornadesPerTemporada(idTemporadaStr);

				if (jornades == nullptr || jornades->Count == 0) {
					MessageBox::Show(L"No hi ha jornades associades a aquesta temporada.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return;
				}

				for each(auto dict in jornades) {
					String^ display = L"Jornada " + dict["numero"] + L" | " + dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
					cmbEJJornades->Items->Add(display);
					ejJornadaIds->Add(dict["idJornada"]);
				}

				if (cmbEJJornades->Items->Count > 0) cmbEJJornades->SelectedIndex = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar jornades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

bool Form1::ConfirmarEsborrarJornadaPermanent() {
		Form^ dialeg = gcnew Form();
		dialeg->Text = L"Confirmació";
		dialeg->StartPosition = FormStartPosition::CenterParent;
		dialeg->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		dialeg->MaximizeBox = false;
		dialeg->MinimizeBox = false;
		dialeg->ShowInTaskbar = false;
		dialeg->ClientSize = System::Drawing::Size(520, 165);

		Label^ lblMissatge = gcnew Label();
		lblMissatge->Text = L"Vols esborrar aquesta jornada de forma permanent? No podras desfer els canvis.";
		lblMissatge->AutoSize = false;
		lblMissatge->Location = System::Drawing::Point(20, 25);
		lblMissatge->Size = System::Drawing::Size(480, 55);

		Button^ btnCancelar = gcnew Button();
		btnCancelar->Text = L"cancel·lar";
		btnCancelar->Size = System::Drawing::Size(130, 35);
		btnCancelar->Location = System::Drawing::Point(210, 105);
		btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;

		Button^ btnEsborrar = gcnew Button();
		btnEsborrar->Text = L"Esborrar permanentment";
		btnEsborrar->Size = System::Drawing::Size(160, 35);
		btnEsborrar->Location = System::Drawing::Point(350, 105);
		btnEsborrar->BackColor = System::Drawing::Color::Red;
		btnEsborrar->ForeColor = System::Drawing::Color::White;
		btnEsborrar->DialogResult = System::Windows::Forms::DialogResult::OK;

		dialeg->Controls->Add(lblMissatge);
		dialeg->Controls->Add(btnCancelar);
		dialeg->Controls->Add(btnEsborrar);
		dialeg->CancelButton = btnCancelar;

		System::Windows::Forms::DialogResult resultat = dialeg->ShowDialog(this);
		return resultat == System::Windows::Forms::DialogResult::OK;
	}

System::Void Form1::btnEJEsborrarFinal_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEJTemporades->SelectedIndex < 0 || cmbEJJornades->SelectedIndex < 0) {
			MessageBox::Show(L"Si us plau, selecciona una temporada i una jornada per a esborrar.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (!ConfirmarEsborrarJornadaPermanent()) {
			return;
		}

		String^ idJornada = ejJornadaIds[cmbEJJornades->SelectedIndex];

		try {
			Playcampus::Domini::CtrlEsborrarJornada^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarJornada();
			ctrl->EsborrarJornada(idJornada);

			MessageBox::Show(L"Jornada esborrada correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			cmbEJTemporades_SelectedIndexChanged(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			if (ex->Message == L"No es pot borrar una jornada amb partits finalitzats") {
				MessageBox::Show(ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {
				MessageBox::Show(L"Hi ha hagut una fallada en esborrar la jornada: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

}
