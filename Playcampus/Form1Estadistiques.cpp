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

		// Crear botón dinámico para Estadísticas de Jugadores si es Capitán
		if (currentUsuariTipus != nullptr && currentUsuariTipus == "Capita") {
			// Verificar si el botón ya existe para evitar duplicados
			if (btnEstJugadors == nullptr) {
				// 1. Crear el botón
				btnEstJugadors = gcnew System::Windows::Forms::Button();

				// 2. Configurar propiedades (mismo estilo que btnEstLliga y btnEstEquips)
				btnEstJugadors->Text = L"Estadistiques Jugadors";
				btnEstJugadors->Size = System::Drawing::Size(220, 60);
				btnEstJugadors->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
				btnEstJugadors->Cursor = System::Windows::Forms::Cursors::Hand;
				btnEstJugadors->BackColor = System::Drawing::SystemColors::Control;
				btnEstJugadors->ForeColor = System::Drawing::Color::Black;

				// 3. Agregar el evento Click (handler específico para estadísticas de jugadores)
				btnEstJugadors->Click += gcnew System::EventHandler(this, &Form1::btnEstJugadors_Click);

				// 4. Añadir al panel de estadísticas
				pnlEstadistiques->Controls->Add(btnEstJugadors);

				// 5. Recalcular el layout para posicionar el botón correctamente
				Form1_Resize(nullptr, nullptr);
			}
		}
	}

	System::Void Form1::btnEstTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlMain->Visible = true;
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
				MessageBox::Show(L"L'equip existeix, però no té cap lliga associada.", L"Sense lligues", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
				MessageBox::Show(L"No hi ha estadístiques per aquest equip en la lliga i temporada seleccionades.", L"Sense dades", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			dgvEstEquipStats->DataSource = estadistiques;
			dgvEstEquipStats->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les estadístiques de l'equip: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

		Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
		String^ idLligaFound = nullptr;

		// 1. Comprovem si és un Administrador fent servir la teva variable de sessió
		if (currentUsuariTipus != nullptr && currentUsuariTipus == "Administrador") {
			lblEstLligaBuscar->Visible = false;
			txtEstLligaBuscar->Visible = false;
			btnEstLligaExecutarCerca->Visible = false;

			// Passem el correu (o el que tinguis guardat) per buscar la seva lliga
			idLligaFound = ctrl->ObtenirIdLligaAdmin(currentUsuariCorreu);
		}
		// 2. Comprovem si és un Capità
		else if (currentUsuariTipus != nullptr && currentUsuariTipus == "Capita") {
			lblEstLligaBuscar->Visible = false;
			txtEstLligaBuscar->Visible = false;
			btnEstLligaExecutarCerca->Visible = false;

			// Passem el correu per buscar la lliga del seu equip
			idLligaFound = ctrl->ObtenirIdLligaCapita(currentUsuariCorreu);
		}
		// 3. Si és Estudiant (o no hi ha sessió)
		else {
			lblEstLligaBuscar->Visible = true;
			txtEstLligaBuscar->Visible = true;
			btnEstLligaExecutarCerca->Visible = true;

			lblEstLligaTemporada->Visible = false;
			cmbEstLligaTemporades->Visible = false;
			dgvEstLligaClassificacio->Visible = false;

			return; // Parem aquí perquè l'estudiant ha de teclejar i buscar manualment
		}

		// Si hem arribat aquí (sent Admin o Capità), carreguem la taula automàticament
		if (idLligaFound != nullptr) {
			currentIdLligaEstadistiques = idLligaFound;
			CarregarDadesLligaDirecte(ctrl, idLligaFound);
		}
		else {
			MessageBox::Show(L"No s'ha trobat cap lliga vinculada al teu compte.", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void Form1::CarregarDadesLligaDirecte(Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl, String^ idLliga) {
		DataTable^ dtTemp = ctrl->ObtenirTemporadesLliga(idLliga);
		cmbEstLligaTemporades->Items->Clear();
		for (int i = 0; i < dtTemp->Rows->Count; i++) {
			DataRow^ row = dtTemp->Rows[i];
			cmbEstLligaTemporades->Items->Add(row["NomTemporada"]->ToString());
		}

		if (cmbEstLligaTemporades->Items->Count > 0) {
			cmbEstLligaTemporades->SelectedIndex = 0;
			cmbEstLligaTemporades->Visible = true;
			lblEstLligaTemporada->Visible = true;
		}

		dgvEstLligaClassificacio->DataSource = ctrl->ObtenirClassificacioLliga(idLliga);
		dgvEstLligaClassificacio->Visible = true;
	}

	System::Void Form1::btnEstLligaExecutarCerca_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtEstLligaBuscar->Text->Trim();
		if (nom == "") return;

		Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
		String^ id = ctrl->ObtenirIdLligaPerNom(nom);

		if (id != nullptr) {
			currentIdLligaEstadistiques = id;
			CarregarDadesLligaDirecte(ctrl, id);
		}
		else {
			MessageBox::Show(L"Lliga no trobada.");
		}
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
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitResultat->Text = L"";

		try {
			Playcampus::Domini::CtrlEstadistiquesPartit^ ctrl = gcnew Playcampus::Domini::CtrlEstadistiquesPartit();
			DataTable^ lligues = ctrl->ObtenirTotesLligues();

			for (int i = 0; i < lligues->Rows->Count; i++) {
				estPartitLligaIds->Add(lligues->Rows[i]["idLliga"]->ToString());
				cmbEstPartitLligues->Items->Add(lligues->Rows[i]["nom"]->ToString());
			}

			if (cmbEstPartitLligues->Items->Count > 0) {
				cmbEstPartitLligues->SelectedIndex = 0;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant lligues: " + ex->Message);
		}
		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::cmbEstPartitLligues_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEstPartitLligues->SelectedIndex < 0) return;

		cmbEstPartitTemporades->Items->Clear();
		estPartitTemporadaIds->Clear();
		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
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
		if (cmbEstPartitTemporades->SelectedIndex < 0) return;

		cmbEstPartitPartits->Items->Clear();
		estPartitIds->Clear();
		dgvEstPartitDetalls->DataSource = nullptr;
		lblEstPartitResultat->Text = L"";

		try {
			String^ idTemporada = estPartitTemporadaIds[cmbEstPartitTemporades->SelectedIndex];
			Playcampus::Domini::CtrlEstadistiquesPartit^ ctrl = gcnew Playcampus::Domini::CtrlEstadistiquesPartit();
			DataTable^ partits = ctrl->ObtenirPartitsFinalitzats(idTemporada);

			for (int i = 0; i < partits->Rows->Count; i++) {
				estPartitIds->Add(partits->Rows[i]["idPartit"]->ToString());
				String^ display = partits->Rows[i]["EquipLocal"]->ToString() + " vs " + partits->Rows[i]["EquipVisitant"]->ToString();
				cmbEstPartitPartits->Items->Add(display);
			}

			if (cmbEstPartitPartits->Items->Count > 0) {
				cmbEstPartitPartits->SelectedIndex = 0;
			}
			else {
				lblEstPartitResultat->Text = L"No s'han jugat partits en aquesta temporada.";
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant partits: " + ex->Message);
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

			// Cargar DataGridView con las estadísticas
			DataTable^ stats = ctrl->ObtenirEstadistiquesPartit(idPartit);
			dgvEstPartitDetalls->DataSource = stats;
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
			MessageBox::Show(L"Error obrint las estadístiques dels jugadors: " + ex->Message, 
						   L"Error", 
						   MessageBoxButtons::OK, 
						   MessageBoxIcon::Error);
		}
	}

}
