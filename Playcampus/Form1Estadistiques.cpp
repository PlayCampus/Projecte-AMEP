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
	}

System::Void Form1::btnEstadistiques_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Estadístiques equips", ctrl->ObtenirEstadistiquesEquips());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les estadistiques: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
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
		for (int i = 0; i < dtTemp->Rows->Count; i++)
			cmbEstLligaTemporades->Items->Add(dtTemp->Rows[i]["NomTemporada"]->ToString());

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


}
