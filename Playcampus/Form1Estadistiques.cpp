#include "pch.h"
#include "Form1Estadistiques.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Void Form1::btnEstadistiquesMenu_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlEstadistiques->Visible = true;
	}

	System::Void Form1::btnEstTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlMain->Visible = true;
		ActualitzarEstatSeguirLliga();
		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::btnEstadistiques_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlEstadistiquesEquipDetail->Visible = true;
		pnlEstadistiquesEquipDetail->BringToFront();
		ResetEstadistiquesEquipPanel();
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::ResetEstadistiquesEquipPanel() {
		txtEstEquipBuscar->Text = L"";

		estEquipLligaIds->Clear();
		estEquipTemporadaIds->Clear();

		cmbEstEquipLligues->Items->Clear();
		cmbEstEquipTemporades->Items->Clear();

		lblEstEquipLliga->Visible = false;
		cmbEstEquipLligues->Visible = false;
		lblEstEquipTemporada->Visible = false;
		cmbEstEquipTemporades->Visible = false;

		dgvEstEquipStats->DataSource = nullptr;
		dgvEstEquipStats->Visible = false;
	}

	System::Void Form1::btnEstEquipCercar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomEquip = txtEstEquipBuscar->Text->Trim();

		estEquipLligaIds->Clear();
		estEquipTemporadaIds->Clear();
		cmbEstEquipLligues->Items->Clear();
		cmbEstEquipTemporades->Items->Clear();
		lblEstEquipLliga->Visible = false;
		cmbEstEquipLligues->Visible = false;
		lblEstEquipTemporada->Visible = false;
		cmbEstEquipTemporades->Visible = false;
		dgvEstEquipStats->DataSource = nullptr;
		dgvEstEquipStats->Visible = false;

		if (String::IsNullOrWhiteSpace(nomEquip)) {
			MessageBox::Show(L"Escriu el nom de l'equip que vols cercar.", L"Cerca d'equip", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		try {
			Playcampus::Domini::CtrlVeureEstadistiquesEquip^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesEquip();

			if (!ctrl->ExisteixEquip(nomEquip)) {
				MessageBox::Show(L"No s'ha trobat cap equip amb aquest nom a la base de dades.", L"Equip no trobat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			DataTable^ lligues = ctrl->ObtenirLliguesEquip(nomEquip);
			if (lligues->Rows->Count == 0) {
				MessageBox::Show(L"L'equip existeix, per\u00F2 no t\u00E9 cap lliga associada.", L"Sense lligues", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			for (int i = 0; i < lligues->Rows->Count; i++) {
				DataRow^ row = lligues->Rows[i];
				estEquipLligaIds->Add(row["IdLliga"]->ToString());
				cmbEstEquipLligues->Items->Add(row["NomLliga"]->ToString());
			}

			lblEstEquipLliga->Visible = true;
			cmbEstEquipLligues->Visible = true;
			cmbEstEquipLligues->SelectedIndex = 0;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error cercant l'equip: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::cmbEstEquipLligues_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		estEquipTemporadaIds->Clear();
		cmbEstEquipTemporades->Items->Clear();
		lblEstEquipTemporada->Visible = false;
		cmbEstEquipTemporades->Visible = false;
		dgvEstEquipStats->DataSource = nullptr;
		dgvEstEquipStats->Visible = false;

		if (cmbEstEquipLligues->SelectedIndex < 0 || cmbEstEquipLligues->SelectedIndex >= estEquipLligaIds->Count) {
			return;
		}

		try {
			String^ nomEquip = txtEstEquipBuscar->Text->Trim();
			String^ idLliga = estEquipLligaIds[cmbEstEquipLligues->SelectedIndex];
			Playcampus::Domini::CtrlVeureEstadistiquesEquip^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesEquip();
			DataTable^ temporades = ctrl->ObtenirTemporadesEquipLliga(nomEquip, idLliga);

			if (temporades->Rows->Count == 0) {
				MessageBox::Show(L"No s'ha trobat cap temporada d'aquesta lliga associada a l'equip.", L"Sense temporades", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			for (int i = 0; i < temporades->Rows->Count; i++) {
				DataRow^ row = temporades->Rows[i];
				estEquipTemporadaIds->Add(row["IdTemporada"]->ToString());
				cmbEstEquipTemporades->Items->Add(row["NomTemporada"]->ToString());
			}

			lblEstEquipTemporada->Visible = true;
			cmbEstEquipTemporades->Visible = true;
			cmbEstEquipTemporades->SelectedIndex = 0;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les temporades de l'equip: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::cmbEstEquipTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CarregarEstadistiquesEquipSeleccionades();
	}

	void Form1::CarregarEstadistiquesEquipSeleccionades() {
		dgvEstEquipStats->DataSource = nullptr;
		dgvEstEquipStats->Visible = false;

		if (cmbEstEquipLligues->SelectedIndex < 0 || cmbEstEquipLligues->SelectedIndex >= estEquipLligaIds->Count) {
			return;
		}

		if (cmbEstEquipTemporades->SelectedIndex < 0 || cmbEstEquipTemporades->SelectedIndex >= estEquipTemporadaIds->Count) {
			return;
		}

		try {
			String^ nomEquip = txtEstEquipBuscar->Text->Trim();
			String^ idLliga = estEquipLligaIds[cmbEstEquipLligues->SelectedIndex];
			String^ idTemporada = estEquipTemporadaIds[cmbEstEquipTemporades->SelectedIndex];

			Playcampus::Domini::CtrlVeureEstadistiquesEquip^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesEquip();
			DataTable^ estadistiques = ctrl->ObtenirEstadistiquesEquip(nomEquip, idLliga, idTemporada);

			if (estadistiques->Rows->Count == 0) {
				MessageBox::Show(L"No hi ha estad\u00EDstiques per aquest equip en la lliga i temporada seleccionades.", L"Sense dades", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			dgvEstEquipStats->DataSource = estadistiques;
			dgvEstEquipStats->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les estad\u00EDstiques de l'equip: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::btnEstEquipTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiquesEquipDetail->Visible = false;
		pnlEstadistiques->Visible = true;
		pnlEstadistiques->BringToFront();
	}

	System::Void Form1::btnEstLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlEstadistiquesLligaDetail->Visible = true;
		pnlEstadistiquesLligaDetail->BringToFront();

		ResetEstadistiquesLligaPanel();
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::ResetEstadistiquesLligaPanel() {
		currentIdLligaEstadistiques = nullptr;
		txtEstLligaBuscar->Text = L"";

		estLligaIds->Clear();
		estLligaTemporadaIds->Clear();
		cmbEstLligaLligues->Items->Clear();
		cmbEstLligaTemporades->Items->Clear();

		lblEstLligaBuscar->Visible = true;
		txtEstLligaBuscar->Visible = true;
		btnEstLligaExecutarCerca->Visible = true;
		lblEstLligaSeleccionar->Visible = false;
		cmbEstLligaLligues->Visible = false;
		lblEstLligaInfo->Visible = true;
		lblEstLligaInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, System::Drawing::FontStyle::Bold);
		lblEstLligaInfo->Text = L"Escriu el nom de la lliga i prem Cercar.";

		lblEstLligaTemporada->Visible = false;
		cmbEstLligaTemporades->Visible = false;
		dgvEstLligaClassificacio->DataSource = nullptr;
		dgvEstLligaClassificacio->Visible = false;
	}

	void Form1::CarregarLliguesEstadistiques() {
		try {
			Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
			DataTable^ lligues = ctrl->ObtenirTotesLligues();
			OmplirComboLliguesEstadistiques(lligues);

			if (cmbEstLligaLligues->Items->Count == 0) {
				MessageBox::Show(L"No hi ha cap lliga registrada a la base de dades.", L"Sense lligues", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les lligues: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	void Form1::OmplirComboLliguesEstadistiques(DataTable^ lligues) {
		estLligaIds->Clear();
		estLligaTemporadaIds->Clear();
		cmbEstLligaLligues->Items->Clear();
		cmbEstLligaTemporades->Items->Clear();
		lblEstLligaTemporada->Visible = false;
		cmbEstLligaTemporades->Visible = false;
		dgvEstLligaClassificacio->DataSource = nullptr;
		dgvEstLligaClassificacio->Visible = false;

		if (lligues != nullptr) {
			for (int i = 0; i < lligues->Rows->Count; i++) {
				DataRow^ row = lligues->Rows[i];
				String^ idLliga = row["IdLliga"]->ToString();
				String^ nomLliga = row["NomLliga"]->ToString();
				String^ esport = row["Esport"]->ToString();
				String^ administrador = row["Administrador"]->ToString();
				String^ numTemporades = row["Temporades"]->ToString();

				String^ textCombo = nomLliga + L" (" + esport + L")";
				if (!String::IsNullOrWhiteSpace(administrador)) {
					textCombo += L" - Admin: " + administrador;
				}
				textCombo += L" - Temporades: " + numTemporades;

				estLligaIds->Add(idLliga);
				cmbEstLligaLligues->Items->Add(textCombo);
			}
		}

		if (cmbEstLligaLligues->Items->Count > 0) {
			cmbEstLligaLligues->SelectedIndex = 0;
		}
	}

	void Form1::CarregarTemporadesEstadistiquesLligaSeleccionada() {
		estLligaTemporadaIds->Clear();
		cmbEstLligaTemporades->Items->Clear();
		lblEstLligaTemporada->Visible = false;
		cmbEstLligaTemporades->Visible = false;
		dgvEstLligaClassificacio->DataSource = nullptr;
		dgvEstLligaClassificacio->Visible = false;
		currentIdLligaEstadistiques = nullptr;

		if (cmbEstLligaLligues->SelectedIndex >= 0 && cmbEstLligaLligues->SelectedIndex < estLligaIds->Count) {
			try {
				currentIdLligaEstadistiques = estLligaIds[cmbEstLligaLligues->SelectedIndex];
				Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
				DataTable^ temporades = ctrl->ObtenirTemporadesLliga(currentIdLligaEstadistiques);

				for (int i = 0; i < temporades->Rows->Count; i++) {
					DataRow^ row = temporades->Rows[i];
					estLligaTemporadaIds->Add(row["idTemporada"]->ToString());
					cmbEstLligaTemporades->Items->Add(row["NomTemporada"]->ToString());
				}

				if (cmbEstLligaTemporades->Items->Count > 0) {
					lblEstLligaTemporada->Visible = true;
					cmbEstLligaTemporades->Visible = true;
					cmbEstLligaTemporades->SelectedIndex = 0;
				}
				else {
					MessageBox::Show(L"La lliga seleccionada no t\u00E9 cap temporada creada.", L"Sense temporades", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error carregant les temporades de la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	void Form1::CarregarClassificacioLligaSeleccionada() {
		dgvEstLligaClassificacio->DataSource = nullptr;
		dgvEstLligaClassificacio->Visible = false;

		if (cmbEstLligaTemporades->SelectedIndex >= 0 && cmbEstLligaTemporades->SelectedIndex < estLligaTemporadaIds->Count && currentIdLligaEstadistiques != nullptr) {
			try {
				String^ idTemporada = estLligaTemporadaIds[cmbEstLligaTemporades->SelectedIndex];
				Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
				DataTable^ classificacio = ctrl->ObtenirClassificacioLligaTemporada(currentIdLligaEstadistiques, idTemporada);

				if (classificacio->Rows->Count == 0) {
					MessageBox::Show(L"No hi ha equips ni estad\u00EDstiques per a aquesta lliga i temporada.", L"Sense dades", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					dgvEstLligaClassificacio->DataSource = classificacio;
					dgvEstLligaClassificacio->Visible = true;
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error carregant la classificaci\u00F3 de la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	void Form1::CarregarDadesLligaDirecte(Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl, String^ idLliga) {
		currentIdLligaEstadistiques = idLliga;
		estLligaTemporadaIds->Clear();
		cmbEstLligaTemporades->Items->Clear();
		dgvEstLligaClassificacio->DataSource = nullptr;
		dgvEstLligaClassificacio->Visible = false;

		DataTable^ dtTemp = ctrl->ObtenirTemporadesLliga(idLliga);
		for (int i = 0; i < dtTemp->Rows->Count; i++) {
			DataRow^ row = dtTemp->Rows[i];
			estLligaTemporadaIds->Add(row["idTemporada"]->ToString());
			cmbEstLligaTemporades->Items->Add(row["NomTemporada"]->ToString());
		}

		if (cmbEstLligaTemporades->Items->Count > 0) {
			lblEstLligaTemporada->Visible = true;
			cmbEstLligaTemporades->Visible = true;
			cmbEstLligaTemporades->SelectedIndex = 0;
		}
	}

	System::Void Form1::btnEstLligaExecutarCerca_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ textCerca = txtEstLligaBuscar->Text->Trim();
		if (String::IsNullOrWhiteSpace(textCerca)) {
			MessageBox::Show(L"Escriu el nom de la lliga que vols consultar.", L"Cerca de lliga", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		try {
			Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
			DataTable^ lligues = ctrl->CercarLliguesPerNom(textCerca);

			if (lligues == nullptr || lligues->Rows->Count == 0) {
				lblEstLligaInfo->Visible = true;
				lblEstLligaInfo->Text = L"No s'ha trobat cap lliga amb aquest nom.";
				currentIdLligaEstadistiques = nullptr;
				estLligaTemporadaIds->Clear();
				cmbEstLligaTemporades->Items->Clear();
				lblEstLligaTemporada->Visible = false;
				cmbEstLligaTemporades->Visible = false;
				dgvEstLligaClassificacio->DataSource = nullptr;
				dgvEstLligaClassificacio->Visible = false;
				return;
			}

			int indexTriat = 0;
			bool trobatExacte = false;
			for (int i = 0; i < lligues->Rows->Count; i++) {
				String^ nomFila = lligues->Rows[i]["NomLliga"]->ToString();
				if (!trobatExacte && String::Equals(nomFila, textCerca, StringComparison::OrdinalIgnoreCase)) {
					indexTriat = i;
					trobatExacte = true;
				}
			}

			DataRow^ row = lligues->Rows[indexTriat];
			String^ idLliga = row["IdLliga"]->ToString();
			String^ nomLliga = row["NomLliga"]->ToString();
			String^ numTemporades = row["Temporades"]->ToString();

			lblEstLligaInfo->Visible = true;
			lblEstLligaInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 13.0F, System::Drawing::FontStyle::Bold);
			lblEstLligaInfo->Text = L"Lliga: " + nomLliga + L"    |    Temporades: " + numTemporades;

			CarregarDadesLligaDirecte(ctrl, idLliga);
			Form1_Resize(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error cercant la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::cmbEstLligaLligues_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CarregarTemporadesEstadistiquesLligaSeleccionada();
	}

	System::Void Form1::cmbEstLligaTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CarregarClassificacioLligaSeleccionada();
	}

	System::Void Form1::btnEstLligaTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiquesLligaDetail->Visible = false;
		pnlEstadistiques->Visible = true;
	}

	System::Void Form1::btnEstPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlEstadistiquesPartitDetail->Visible = true;
		pnlEstadistiquesPartitDetail->BringToFront();

		cmbEstPartitLligues->Items->Clear();
		estPartitLligaIds->Clear();
		cmbEstPartitTemporades->Items->Clear();
		estPartitTemporadaIds->Clear();
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		txtEstPartitBuscar->Text = L"";
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitInfo->Text = L"Escriu el nom d'un equip, la lliga, la ubicació o la data del partit i prem Cercar.";
		lblEstPartitResultat->Text = L"";

		lblEstPartitLliga->Visible = false;
		cmbEstPartitLligues->Visible = false;
		lblEstPartitTemporada->Visible = false;
		cmbEstPartitTemporades->Visible = false;
		lblEstPartitPartits->Visible = false;
		cmbEstPartitPartits->Visible = false;
		lblEstPartitPartits->Text = L"Resultats trobats:";

		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::cmbEstPartitLligues_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEstPartitLligues->SelectedIndex < 0) return;

		cmbEstPartitTemporades->Items->Clear();
		estPartitTemporadaIds->Clear();
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitInfo->Text = L"";
		lblEstPartitResultat->Text = L"";

		try {
			String^ idLliga = estPartitLligaIds[cmbEstPartitLligues->SelectedIndex];
			Playcampus::Domini::CtrlEstadistiquesPartit^ ctrl = gcnew Playcampus::Domini::CtrlEstadistiquesPartit();
			DataTable^ temporades = ctrl->ObtenirTemporadesLliga(idLliga);

			for (int i = 0; i < temporades->Rows->Count; i++) {
				estPartitTemporadaIds->Add(temporades->Rows[i]["idTemporada"]->ToString());
				String^ min = Convert::ToDateTime(temporades->Rows[i]["dataInici"]).ToString("dd/MM/yyyy");
				String^ max = Convert::ToDateTime(temporades->Rows[i]["dataFi"]).ToString("dd/MM/yyyy");
				cmbEstPartitTemporades->Items->Add(min + " - " + max);
			}

			if (cmbEstPartitTemporades->Items->Count > 0) {
				cmbEstPartitTemporades->SelectedIndex = 0;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant temporades: " + ex->Message);
		}
	}

	System::Void Form1::cmbEstPartitTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CarregarPartitsFinalitzatsEstadistiques(txtEstPartitBuscar->Text->Trim());
	}

	void Form1::CarregarPartitsFinalitzatsEstadistiques(String^ textCerca) {
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitInfo->Text = L"";
		lblEstPartitResultat->Text = L"";

		if (String::IsNullOrWhiteSpace(textCerca)) {
			lblEstPartitPartits->Visible = false;
			cmbEstPartitPartits->Visible = false;
			lblEstPartitInfo->Text = L"Escriu el nom d'un equip, la lliga, la ubicació o la data del partit i prem Cercar.";
			return;
		}

		try {
			Playcampus::Domini::CtrlEstadistiquesPartit^ ctrl = gcnew Playcampus::Domini::CtrlEstadistiquesPartit();
			DataTable^ partits = ctrl->CercarPartitsFinalitzatsGlobal(textCerca);
			OmplirComboPartitsEstadistiques(partits, textCerca);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant partits: " + ex->Message);
		}
	}

	void Form1::OmplirComboPartitsEstadistiques(DataTable^ partits, String^ textCerca) {
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitInfo->Text = L"";
		lblEstPartitResultat->Text = L"";

		if (partits != nullptr) {
			for (int i = 0; i < partits->Rows->Count; i++) {
				DataRow^ row = partits->Rows[i];
				estPartitIds->Add(row["idPartit"]->ToString());

				String^ display = row["EquipLocal"]->ToString() + L" vs " + row["EquipVisitant"]->ToString();
				if (partits->Columns->Contains("Lliga")) {
					display = row["Lliga"]->ToString() + L" | " + display;
				}
				if (partits->Columns->Contains("DataHora")) {
					display += L" - " + row["DataHora"]->ToString();
				}
				if (partits->Columns->Contains("Ubicacio") && !String::IsNullOrWhiteSpace(row["Ubicacio"]->ToString())) {
					display += L" - " + row["Ubicacio"]->ToString();
				}
				if (partits->Columns->Contains("GolsLocal") && partits->Columns->Contains("GolsVisitant")) {
					display += L" (" + row["GolsLocal"]->ToString() + L"-" + row["GolsVisitant"]->ToString() + L")";
				}

				cmbEstPartitPartits->Items->Add(display);
			}
		}

		if (cmbEstPartitPartits->Items->Count > 0) {
			lblEstPartitPartits->Visible = true;
			cmbEstPartitPartits->Visible = true;
			cmbEstPartitPartits->DropDownWidth = 900;
			if (cmbEstPartitPartits->Items->Count == 1) {
				lblEstPartitPartits->Text = L"Partit trobat:";
			}
			else {
				lblEstPartitPartits->Text = L"Selecciona partit:";
			}

			cmbEstPartitPartits->SelectedIndex = 0;
			if (String::IsNullOrWhiteSpace(textCerca)) {
				lblEstPartitInfo->Text = cmbEstPartitPartits->Items->Count.ToString() + L" partit(s) carregats.";
			}
			else {
				lblEstPartitInfo->Text = cmbEstPartitPartits->Items->Count.ToString() + L" resultat(s) trobats per: " + textCerca;
			}
		}
		else {
			lblEstPartitPartits->Visible = false;
			cmbEstPartitPartits->Visible = false;
			if (String::IsNullOrWhiteSpace(textCerca)) {
				lblEstPartitInfo->Text = L"No s'han jugat partits en aquesta temporada.";
			}
			else {
				lblEstPartitInfo->Text = L"No s'ha trobat cap partit que coincideixi amb la cerca.";
			}
		}
	}

	System::Void Form1::btnEstPartitCercar_Click(System::Object^ sender, System::EventArgs^ e) {
		CarregarPartitsFinalitzatsEstadistiques(txtEstPartitBuscar->Text->Trim());
	}

	System::Void Form1::btnEstPartitNetejar_Click(System::Object^ sender, System::EventArgs^ e) {
		txtEstPartitBuscar->Text = L"";
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitPartits->Visible = false;
		cmbEstPartitPartits->Visible = false;
		lblEstPartitResultat->Text = L"";
		lblEstPartitInfo->Text = L"Cerca netejada. Escriu un text i prem Cercar.";
	}

	System::Void Form1::txtEstPartitBuscar_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
			e->SuppressKeyPress = true;
			CarregarPartitsFinalitzatsEstadistiques(txtEstPartitBuscar->Text->Trim());
		}
	}

	System::Void Form1::cmbEstPartitPartits_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEstPartitPartits->SelectedIndex < 0) return;

		try {
			String^ idPartit = estPartitIds[cmbEstPartitPartits->SelectedIndex];
			Playcampus::Domini::CtrlEstadistiquesPartit^ ctrl = gcnew Playcampus::Domini::CtrlEstadistiquesPartit();

			// Cargar los detalles del partido (como los goles)
			DataTable^ detalls = ctrl->ObtenirDetallsPartit(idPartit);
			if (detalls->Rows->Count > 0) {
				String^ eqLocal = detalls->Rows[0]["EquipLocal"]->ToString();
				String^ eqVisitant = detalls->Rows[0]["EquipVisitant"]->ToString();
				String^ golsLocal = detalls->Rows[0]["GolsLocals"]->ToString();
				String^ golsVisitant = detalls->Rows[0]["GolsVisitants"]->ToString();

				lblEstPartitResultat->Text = String::Format("Resultat: {0} {1} - {2} {3}", eqLocal, golsLocal, golsVisitant, eqVisitant);
				lblEstPartitResultat->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold);
			}

			// Carrega les estadístiques dels jugadors del partit.
			DataTable^ stats = ctrl->ObtenirEstadistiquesPartit(idPartit);
			dgvEstPartitDetalls->DataSource = stats;
			dgvEstPartitDetalls->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			dgvEstPartitDetalls->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dgvEstPartitDetalls->DefaultCellStyle->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			dgvEstPartitDetalls->ColumnHeadersDefaultCellStyle->WrapMode = System::Windows::Forms::DataGridViewTriState::False;

			if (dgvEstPartitDetalls->Columns->Contains("IdJugador")) {
				dgvEstPartitDetalls->Columns["IdJugador"]->Visible = false;
			}
			if (dgvEstPartitDetalls->Columns->Contains("NomJugador")) {
				dgvEstPartitDetalls->Columns["NomJugador"]->HeaderText = L"Jugador";
				dgvEstPartitDetalls->Columns["NomJugador"]->FillWeight = 150;
			}
			if (dgvEstPartitDetalls->Columns->Contains("Posicio")) {
				dgvEstPartitDetalls->Columns["Posicio"]->HeaderText = L"Posició";
				dgvEstPartitDetalls->Columns["Posicio"]->FillWeight = 90;
			}
			if (dgvEstPartitDetalls->Columns->Contains("TargetesGrogues")) {
				dgvEstPartitDetalls->Columns["TargetesGrogues"]->HeaderText = L"Grogu.";
				dgvEstPartitDetalls->Columns["TargetesGrogues"]->FillWeight = 70;
			}
			if (dgvEstPartitDetalls->Columns->Contains("TargetesVermelles")) {
				dgvEstPartitDetalls->Columns["TargetesVermelles"]->HeaderText = L"Verm.";
				dgvEstPartitDetalls->Columns["TargetesVermelles"]->FillWeight = 70;
			}
			if (dgvEstPartitDetalls->Columns->Contains("GolsMarcats")) {
				dgvEstPartitDetalls->Columns["GolsMarcats"]->HeaderText = L"Gols/Punts";
				dgvEstPartitDetalls->Columns["GolsMarcats"]->FillWeight = 80;
			}
			if (dgvEstPartitDetalls->Columns->Contains("Assistencies")) {
				dgvEstPartitDetalls->Columns["Assistencies"]->HeaderText = L"Assist.";
				dgvEstPartitDetalls->Columns["Assistencies"]->FillWeight = 80;
			}
			if (dgvEstPartitDetalls->Columns->Contains("TargetesGroguesObtenides")) {
				dgvEstPartitDetalls->Columns["TargetesGroguesObtenides"]->HeaderText = L"Grogu. obt.";
				dgvEstPartitDetalls->Columns["TargetesGroguesObtenides"]->FillWeight = 90;
			}
			if (dgvEstPartitDetalls->Columns->Contains("TargetesVermelllesObtenides")) {
				dgvEstPartitDetalls->Columns["TargetesVermelllesObtenides"]->HeaderText = L"Verm. obt.";
				dgvEstPartitDetalls->Columns["TargetesVermelllesObtenides"]->FillWeight = 90;
			}
			if (dgvEstPartitDetalls->Columns->Contains("DataActualitzacio")) {
				dgvEstPartitDetalls->Columns["DataActualitzacio"]->HeaderText = L"Actualitzat";
				dgvEstPartitDetalls->Columns["DataActualitzacio"]->FillWeight = 100;
			}
			if (dgvEstPartitDetalls->Columns->Contains("Equip")) {
				dgvEstPartitDetalls->Columns["Equip"]->HeaderText = L"Equip";
				dgvEstPartitDetalls->Columns["Equip"]->FillWeight = 120;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant dades del partit: " + ex->Message);
		}
	}

	System::Void Form1::btnEstPartitTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiquesPartitDetail->Visible = false;
		pnlEstadistiques->Visible = true;
	}

	System::Void Form1::btnEstJugadors_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			// Crear instancia del formulario de estadísticas de jugadores
			EstadistiquesJugadorsForm^ estadistiquesForm = gcnew EstadistiquesJugadorsForm();

			// Mostrar el formulario de forma modal sobre el formulario principal
			estadistiquesForm->ShowDialog(this);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error obrint les estad\u00EDstiques dels jugadors: " + ex->Message, 
						   L"Error", 
						   MessageBoxButtons::OK, 
						   MessageBoxIcon::Error);
		}
	}

}
