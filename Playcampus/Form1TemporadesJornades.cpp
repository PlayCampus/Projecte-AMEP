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

			txtCJNomLliga->Text = L"";
			cmbCJTemporada->Items->Clear();
			cjTemporadaIds->Clear();
			dtpCJDataInici->Value = DateTime::Now;
			dtpCJDataFi->Value = DateTime::Now.AddDays(7); // Acostuma a durar 1 setmana
		}

System::Void Form1::btnCJCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearJornada->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

System::Void Form1::btnCJBuscarTemporades_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtCJNomLliga->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) {
			MessageBox::Show(L"Introdueix el nom de la Lliga.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			
			Playcampus::Domini::CtrlCrearJornada^ ctrl = gcnew Playcampus::Domini::CtrlCrearJornada();

			// Comprovar que ets l'administrador
			bool esAdmin = ctrl->ValidarAdministradorLliga(nomLliga, currentUsuariCorreu);
			if (!esAdmin) {
				MessageBox::Show(L"No ets l'administrador d'aquesta lliga o la lliga no existeix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Obtenir temporades de la lliga
			System::Collections::Generic::List<System::Collections::Generic::Dictionary<String^, String^>^>^ temporades = ctrl->ObtenirTemporadesLliga(nomLliga);

			cmbCJTemporada->Items->Clear();
			cjTemporadaIds->Clear();

			for each(auto temp in temporades) {
				String^ display = temp["dataInici"] + L" - " + temp["dataFi"];
				cmbCJTemporada->Items->Add(display);
				cjTemporadaIds->Add(temp["idTemporada"]);
			}

			if (cmbCJTemporada->Items->Count > 0) cmbCJTemporada->SelectedIndex = 0;
			else MessageBox::Show(L"No s'han trobat temporades per a aquesta lliga.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Information);
			

		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al cercar temporades: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
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
			txtCTNomLliga->Text = L""; // <--- AFEGIR AQUESTA LÍNIA PELS VALORS RESIDUALS
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
		String^ nomLliga = txtCTNomLliga->Text; // <--- AFEGIR AQUESTA VARIABLE

		if (String::IsNullOrWhiteSpace(nomLliga)) { // <-- EVITAR QUE EL NOMBRE ESTE EN BLANCO
			MessageBox::Show(L"Introdueix el nom de la Lliga a la que vols unir la temporada.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dataFi <= dataInici) {
			MessageBox::Show(L"La data de fi ha de ser posterior a la data d'inici.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			// Instanciar el controlador y llamar a la BD pasandole ahora el nombre
			Playcampus::Domini::CtrlCrearTemporada^ ctrl = gcnew Playcampus::Domini::CtrlCrearTemporada();
			ctrl->CrearTemporada(dataInici, dataFi, currentUsuariCorreu, nomLliga); // <--- AFEGIM EL NOU PARAMETRE

			MessageBox::Show(L"Temporada creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			pnlCrearTemporada->Visible = false;
			pnlGestionarLliga->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear la temporada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

}
