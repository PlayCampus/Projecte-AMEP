#include "pch.h"
#include "Form1Consultes.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void Form1::CarregarUltimsFitxatges() {
		if (this->lblNoticies != nullptr) this->lblNoticies->Text = L"Últims fitxatges";
		if (this->lstNoticies == nullptr) return;

		this->lstNoticies->Items->Clear();
		try {
			Playcampus::Domini::CtrlConsultaFitxatges^ ctrl = gcnew Playcampus::Domini::CtrlConsultaFitxatges();
			DataTable^ dt = ctrl->ObtenirUltimsFitxatges(10);
			if (dt == nullptr || dt->Rows->Count == 0) {
				this->lstNoticies->Items->Add(L"No hi ha fitxatges recents.");
				return;
			}

			for each (DataRow^ row in dt->Rows) {
				String^ data = row->Table->Columns->Contains("Data") ? row["Data"]->ToString() : L"";
				String^ jugador = row->Table->Columns->Contains("Jugador") ? row["Jugador"]->ToString() : L"";
				String^ equip = row->Table->Columns->Contains("Equip") ? row["Equip"]->ToString() : L"";
				String^ esport = row->Table->Columns->Contains("Esport") ? row["Esport"]->ToString() : L"";

				String^ linia = String::IsNullOrEmpty(esport)
					? String::Format(L"{0} - {1}  {2}", data, jugador, equip)
					: String::Format(L"{0} - {1}  {2} ({3})", data, jugador, equip, esport);

				this->lstNoticies->Items->Add(linia);
			}
		}
		catch (Exception^) {
			this->lstNoticies->Items->Add(L"No s'han pogut carregar els fitxatges.");
		}
	}

System::Void Form1::btnConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlConsultar->Visible = true;
		txtNomLliga->Text = L"";
       ActualitzarAccesRapidCalendariLligaSeguida();
	}

System::Void Form1::btnTornarConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlConsultar->Visible = false;
		pnlMain->Visible = true;
		txtNomLliga->Text = L"";
	}

	void Form1::ActualitzarAccesRapidCalendariLligaSeguida() {
		if (this->lblAccesRapidCalendari == nullptr || this->btnCalendariLligaSeguida == nullptr) return;

		this->lblAccesRapidCalendari->Visible = false;
		this->btnCalendariLligaSeguida->Visible = false;
		this->btnCalendariLligaSeguida->Text = L"Veure calendari de la lliga seguida";

		if (String::IsNullOrEmpty(currentUsuariCorreu)) return;
		try {
			Playcampus::Domini::CtrlSeguirLliga^ ctrl = gcnew Playcampus::Domini::CtrlSeguirLliga();
			String^ id = ctrl->ObtenirIdLligaSeguida(currentUsuariCorreu);
			if (String::IsNullOrEmpty(id)) return;
			String^ nom = ctrl->ObtenirNomLligaPerId(id);
			if (!String::IsNullOrEmpty(nom)) {
				this->btnCalendariLligaSeguida->Text = L"Calendari: " + nom;
			}
			this->lblAccesRapidCalendari->Visible = true;
			this->btnCalendariLligaSeguida->Visible = true;
		}
		catch (Exception^) {
			// Ignorem errors d'accés ràpid; el buscador segueix funcionant.
		}
	}

	System::Void Form1::btnCalendariLligaSeguida_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(currentUsuariCorreu)) return;
		try {
			Playcampus::Domini::CtrlSeguirLliga^ ctrlSeguir = gcnew Playcampus::Domini::CtrlSeguirLliga();
			String^ idLliga = ctrlSeguir->ObtenirIdLligaSeguida(currentUsuariCorreu);
			if (String::IsNullOrEmpty(idLliga)) {
				MessageBox::Show(L"No estàs seguint cap lliga.", L"Calendari", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			String^ nom = ctrlSeguir->ObtenirNomLligaPerId(idLliga);
			Playcampus::Domini::CtrlConsultaPartits^ ctrl = gcnew Playcampus::Domini::CtrlConsultaPartits();
			MostrarConsultaGeneral(L"Calendari - " + (String::IsNullOrEmpty(nom) ? idLliga : nom), ctrl->ObtenirCalendariCompletLligaPerId(idLliga));
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant el calendari: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnComprovarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ nom = txtNomLliga->Text;
		if (String::IsNullOrWhiteSpace(nom)) return;
		try {
            nom = nom->Trim();
			Playcampus::Domini::CtrlSeguirLliga^ ctrlSeguir = gcnew Playcampus::Domini::CtrlSeguirLliga();
			String^ idLliga = ctrlSeguir->ObtenirIdLligaPerNom(nom);
			if (String::IsNullOrEmpty(idLliga)) {
				MessageBox::Show(L"Aquesta lliga no existeix", L"Calendari", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}
			Playcampus::Domini::CtrlConsultaPartits^ ctrl = gcnew Playcampus::Domini::CtrlConsultaPartits();
			MostrarConsultaGeneral(L"Calendari - " + nom, ctrl->ObtenirCalendariCompletLligaPerId(idLliga));
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



System::Void Form1::MostrarTelefonsContacteUsuariActual() {
        if (String::IsNullOrWhiteSpace(currentUsuariCorreu)) {
            MessageBox::Show(L"No s'ha pogut identificar l'usuari actual.", L"Consultar telèfons", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
        else {
            try {
                Playcampus::Domini::CtrlConsultaTelefons^ ctrl = gcnew Playcampus::Domini::CtrlConsultaTelefons();
                DataTable^ dades = ctrl->ObtenirTelefonsContacte(currentUsuariCorreu);
                MostrarConsultaGeneral(L"Telèfons de contacte", dades);
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Error carregant els telèfons de contacte: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
}

System::Void Form1::btnConsultarTelefons_Click(System::Object^ sender, System::EventArgs^ e) {
        MostrarTelefonsContacteUsuariActual();
}

System::Void Form1::btnProgPartits_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultaPartits^ ctrl = gcnew Playcampus::Domini::CtrlConsultaPartits();
			MostrarConsultaGeneral(L"Programació de partits", ctrl->ObtenirProgramacioPartits());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant la programacio de partits: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnEstatLligues_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultaLligues^ ctrl = gcnew Playcampus::Domini::CtrlConsultaLligues();
			MostrarConsultaGeneral(L"Estat de les lligues", ctrl->ObtenirEstatLligues());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant l'estat de les lligues: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

}
