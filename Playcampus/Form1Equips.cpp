#include "pch.h"
#include "Form1Equips.h"
#include "EditarJugadorForm.h"
#include "Domini/CtrlAbandonarLliga.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::btnUnirEquipLligaAct_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnUnirEquipLliga->Text == L"Abandonar Lliga") {
			System::Windows::Forms::DialogResult result = MessageBox::Show(L"Estàs segur que vols abandonar la lliga? Les estadístiques de l'equip es reiniciaran.", L"Abandonar Lliga", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
			if (result == System::Windows::Forms::DialogResult::Yes) {
				try {
					Playcampus::Domini::CtrlAbandonarLliga^ ctrl = gcnew Playcampus::Domini::CtrlAbandonarLliga();
					String^ missatgeExit = ctrl->AbandonarLliga(currentUsuariCorreu);
					MessageBox::Show(missatgeExit, L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

					btnUnirEquipLliga->Text = L"Unir-se a una Lliga";

					pnlMain->Visible = false;
					pnlMain->Visible = true;
				}
				catch (Exception^ ex) {
					MessageBox::Show(L"Error al abandonar la lliga: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			return;
		}

		pnlMain->Visible = false;
		pnlUnirEquipLliga->Visible = true;
		
		txtUELNom->Text = L"";
		txtUELPass->Text = L"";
		txtUELNom->Enabled = true;
		btnUELComprovar->Visible = true;
		lblUELPass->Visible = false;
		txtUELPass->Visible = false;
		btnUELUnir->Visible = false;
	}

System::Void Form1::btnUELTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlUnirEquipLliga->Visible = false;
		pnlMain->Visible = true;
	}

System::Void Form1::btnUELComprovar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtUELNom->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) { 
			MessageBox::Show(L"Introdueix nom de la lliga", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return; 
		}

		try {
			Playcampus::Domini::CtrlUnirEquipLliga^ ctrl = gcnew Playcampus::Domini::CtrlUnirEquipLliga();
			String^ lligaTroba = ctrl->ComprovarSiLligaExisteix(nomLliga);
			
			if (lligaTroba != nullptr) {
				txtUELNom->Enabled = false;
				btnUELComprovar->Visible = false;
				
				lblUELPass->Visible = true;
				txtUELPass->Visible = true;
				btnUELUnir->Visible = true;
			}
			else {
				MessageBox::Show(L"La lliga no existeix, si us plau, introdueix una d'existent.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtUELNom->Text = L""; 
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error de BD: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnUELUnir_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtUELNom->Text;
		String^ passLliga = txtUELPass->Text;

		if(String::IsNullOrWhiteSpace(passLliga)) return;

		try {
			Playcampus::Domini::CtrlUnirEquipLliga^ ctrl = gcnew Playcampus::Domini::CtrlUnirEquipLliga();
			
			if (ctrl->ValidarContrasenyaLliga(nomLliga, passLliga)) {
				String^ missatgeExit = ctrl->VincularEquip(currentUsuariCorreu, nomLliga);
				MessageBox::Show(missatgeExit, L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				btnUnirEquipLliga->Text = L"Abandonar Lliga";

				pnlUnirEquipLliga->Visible = false;
				pnlMain->Visible = true;
			}
			else {
				MessageBox::Show(L"Contrasenya incorrecta. Torna a intentar-ho.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				txtUELPass->Text = L""; 
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"No s'ha pogut vincular: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			txtUELNom->Enabled = true;
			btnUELComprovar->Visible = true;
			lblUELPass->Visible = false;
			txtUELPass->Visible = false;
			btnUELUnir->Visible = false;
			txtUELNom->Text = L"";
			txtUELPass->Text = L"";
		}
	}

System::Void Form1::btnEnregistrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnEnregistrarEquip->Text == L"Gestionar Equip") {
			pnlMain->Visible = false;
			pnlGestionarEquip->Visible = true;
			try {
				Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
				dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
               if (dgvPlantilla->Columns->Contains("IdJugador")) {
					dgvPlantilla->Columns["IdJugador"]->Visible = false;
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar la plantilla: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return;
		}

		pnlMain->Visible = false;
		pnlEnregistrarEquip->Visible = true;
		txtEENom->Text = L"";
		dtpEEData->Value = DateTime::Now;
		cmbEEEscollirEsport->SelectedIndex = -1;
	}

System::Void Form1::btnGETornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarEquip->Visible = false;
		pnlMain->Visible = true;
	}

System::Void Form1::btnGEEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult result = MessageBox::Show(L"Estàs segur que vols esborrar l'equip?", L"Esborrar Equip", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (result == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarEquip^ ctrlEsborrar = gcnew Playcampus::Domini::CtrlEsborrarEquip();
				ctrlEsborrar->EsborrarEquip(currentUsuariCorreu);

				MessageBox::Show(L"Equip esborrat correctament!", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				btnEnregistrarEquip->Text = L"Enregistrar Equip";
				pnlGestionarEquip->Visible = false;
				pnlMain->Visible = true;
			} catch (Exception^ ex) {
				MessageBox::Show(L"Error a l'esborrar l'equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

System::Void Form1::btnGEAssignarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
			MessageBox::Show(L"Només els capitans poden accedir a aquesta funcionalitat.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlAssignarJugador^ ctrlAssignar = gcnew Playcampus::Domini::CtrlAssignarJugador();
			auto partits = ctrlAssignar->ObtenirPartitsDisponibles(currentUsuariCorreu);
			if (partits->Count == 0) {
				MessageBox::Show(L"No hi ha partits no finalitzats disponibles per al teu equip.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			auto jugadors = ctrlAssignar->ObtenirJugadorsEquip(currentUsuariCorreu);
			if (jugadors->Count == 0) {
				MessageBox::Show(L"El teu equip no té jugadors disponibles.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			Form^ frmAssignar = gcnew Form();
			frmAssignar->Text = L"Assignar jugador a partit";
			frmAssignar->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			frmAssignar->StartPosition = FormStartPosition::CenterParent;
			frmAssignar->ClientSize = System::Drawing::Size(720, 220);
			frmAssignar->MinimizeBox = false;
			frmAssignar->MaximizeBox = false;

			Label^ lblPartit = gcnew Label();
			lblPartit->Text = L"Selecciona el partit:";
			lblPartit->Location = System::Drawing::Point(20, 22);
			lblPartit->AutoSize = true;

			ComboBox^ cmbPartits = gcnew ComboBox();
			cmbPartits->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbPartits->Location = System::Drawing::Point(20, 48);
			cmbPartits->Size = System::Drawing::Size(680, 24);

			for each (auto p in partits) {
				String^ ubicacio = String::IsNullOrWhiteSpace(p["ubicacio"]) ? L"" : L" - " + p["ubicacio"];
				String^ display = p["dataHora"] + L" - " + p["equipLocal"] + L" vs " + p["equipVisitant"] + L" [" + p["estat"] + L"]" + ubicacio;
				cmbPartits->Items->Add(display);
			}
			cmbPartits->SelectedIndex = 0;

			Label^ lblJugador = gcnew Label();
			lblJugador->Text = L"Selecciona el jugador:";
			lblJugador->Location = System::Drawing::Point(20, 92);
			lblJugador->AutoSize = true;

			ComboBox^ cmbJugadors = gcnew ComboBox();
			cmbJugadors->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbJugadors->Location = System::Drawing::Point(20, 118);
			cmbJugadors->Size = System::Drawing::Size(680, 24);

			for each (auto j in jugadors) {
				String^ dorsal = String::IsNullOrWhiteSpace(j["dorsal"]) ? L"S/D" : j["dorsal"];
				String^ posicio = String::IsNullOrWhiteSpace(j["posicio"]) ? L"" : L" - " + j["posicio"];
				String^ display = L"#" + dorsal + L" " + j["nom"] + posicio;
				cmbJugadors->Items->Add(display);
			}
			cmbJugadors->SelectedIndex = 0;

			Button^ btnConfirmar = gcnew Button();
			btnConfirmar->Text = L"Assignar";
			btnConfirmar->DialogResult = System::Windows::Forms::DialogResult::OK;
			btnConfirmar->Location = System::Drawing::Point(520, 170);
			btnConfirmar->Size = System::Drawing::Size(85, 30);

			Button^ btnCancelar = gcnew Button();
			btnCancelar->Text = L"Cancel·lar";
			btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			btnCancelar->Location = System::Drawing::Point(615, 170);
			btnCancelar->Size = System::Drawing::Size(85, 30);

			frmAssignar->Controls->Add(lblPartit);
			frmAssignar->Controls->Add(cmbPartits);
			frmAssignar->Controls->Add(lblJugador);
			frmAssignar->Controls->Add(cmbJugadors);
			frmAssignar->Controls->Add(btnConfirmar);
			frmAssignar->Controls->Add(btnCancelar);
			frmAssignar->AcceptButton = btnConfirmar;
			frmAssignar->CancelButton = btnCancelar;

			if (frmAssignar->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
				if (cmbPartits->SelectedIndex < 0 || cmbJugadors->SelectedIndex < 0) {
					MessageBox::Show(L"Cal seleccionar un partit i un jugador.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				else {
					String^ idPartit = partits[cmbPartits->SelectedIndex]->default["idPartit"];
					String^ idJugador = jugadors[cmbJugadors->SelectedIndex]->default["idJugador"];
					String^ resultat = ctrlAssignar->AssignarJugador(currentUsuariCorreu, idPartit, idJugador);
					MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en assignar jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGEAfegirJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarEquip->Visible = false;
		pnlAfegirJugador->Visible = true;
		txtAJCorreu->Text = L"";
		txtAJDorsal->Text = L"";
		txtAJPosicio->Text = L"";
	}

System::Void Form1::btnGEEliminarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
			MessageBox::Show(L"Només els capitans poden accedir a aquesta funcionalitat.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dgvPlantilla->SelectedRows == nullptr || dgvPlantilla->SelectedRows->Count == 0) {
			MessageBox::Show(L"Selecciona un jugador de la plantilla.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		DataGridViewRow^ row = dgvPlantilla->SelectedRows[0];
		String^ idJugador = nullptr;
		if (dgvPlantilla->Columns->Contains("IdJugador") && row->Cells["IdJugador"]->Value != nullptr) {
			idJugador = row->Cells["IdJugador"]->Value->ToString();
		}

		if (String::IsNullOrWhiteSpace(idJugador)) {
			MessageBox::Show(L"No s'ha pogut obtenir l'IdJugador de la fila seleccionada.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		String^ nomJugador = L"";
		if (dgvPlantilla->Columns->Contains("Nom") && row->Cells["Nom"]->Value != nullptr) {
			nomJugador = row->Cells["Nom"]->Value->ToString();
		}

		System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
			L"Vols eliminar/expulsar el jugador '" + nomJugador + L"' de l'equip?",
			L"Confirmació",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning);

		if (confirmacio != System::Windows::Forms::DialogResult::Yes) {
			return;
		}

		try {
			Playcampus::Domini::CtrlEliminarJugador^ ctrlEliminar = gcnew Playcampus::Domini::CtrlEliminarJugador();
			String^ resultat = ctrlEliminar->EliminarJugador(currentUsuariCorreu, idJugador);
			MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
			dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
           if (dgvPlantilla->Columns->Contains("IdJugador")) {
				dgvPlantilla->Columns["IdJugador"]->Visible = false;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en expulsar el jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnGEEditarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
	if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
		MessageBox::Show(L"Només els capitans poden accedir a aquesta funcionalitat.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (dgvPlantilla->SelectedRows == nullptr || dgvPlantilla->SelectedRows->Count == 0) {
		MessageBox::Show(L"Selecciona un jugador de la plantilla per editar.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	DataGridViewRow^ row = dgvPlantilla->SelectedRows[0];

	// Obtener los datos del jugador de la fila seleccionada
	String^ idJugador = nullptr;
	String^ nomJugador = nullptr;
	int dorsal = 0;
	String^ posicio = nullptr;

	try {
		if (dgvPlantilla->Columns->Contains("IdJugador") && row->Cells["IdJugador"]->Value != nullptr) {
			idJugador = row->Cells["IdJugador"]->Value->ToString();
		}

		if (dgvPlantilla->Columns->Contains("Nom") && row->Cells["Nom"]->Value != nullptr) {
			nomJugador = row->Cells["Nom"]->Value->ToString();
		}

		if (dgvPlantilla->Columns->Contains("Dorsal") && row->Cells["Dorsal"]->Value != nullptr) {
			dorsal = Convert::ToInt32(row->Cells["Dorsal"]->Value);
		}

		if (dgvPlantilla->Columns->Contains("Posició") && row->Cells["Posició"]->Value != nullptr) {
			posicio = row->Cells["Posició"]->Value->ToString();
		}

		// Validar datos mínimos
		if (String::IsNullOrWhiteSpace(idJugador) || String::IsNullOrWhiteSpace(nomJugador)) {
			MessageBox::Show(L"No s'ha pogut obtenir l'informació del jugador seleccionat.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Crear y mostrar el formulario de edición
		EditarJugadorForm^ frmEditar = gcnew EditarJugadorForm(idJugador, nomJugador, dorsal, posicio);
		frmEditar->CorreuCapita = currentUsuariCorreu;

		if (frmEditar->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			// Obtener los valores editados del formulario
			int dorsalEditat = frmEditar->JugadorDorsal;
			String^ posicioEditada = frmEditar->JugadorPosicio;

			try {
				// Recargar la plantilla para mostrar los cambios actualizados
				Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
				dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
				if (dgvPlantilla->Columns->Contains("IdJugador")) {
					dgvPlantilla->Columns["IdJugador"]->Visible = false;
				}

				MessageBox::Show(L"Jugador actualitzat correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al actualitzar la plantilla: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			// }
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show(L"Error al editar el jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void Form1::btnAJConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ correuEstudiant = txtAJCorreu->Text;
		String^ dorsalText = txtAJDorsal->Text;
		String^ posicioText = txtAJPosicio->Text;
		DateTime dataNaixement = dtpAJDataNaixement->Value;

		if (String::IsNullOrWhiteSpace(correuEstudiant) || String::IsNullOrWhiteSpace(dorsalText)) {
			MessageBox::Show(L"Si us plau, omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int dorsal = 0;
		if (!Int32::TryParse(dorsalText, dorsal) || dorsal <= 0 || dorsal > 99) {
			MessageBox::Show(L"El dorsal ha de ser més gran que 0 i menor o igual que 99.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlAfegirJugador^ ctrlAfegir = gcnew Playcampus::Domini::CtrlAfegirJugador();
			String^ resultat = ctrlAfegir->AfegirJugador(correuEstudiant, dorsal, posicioText, currentUsuariCorreu, dataNaixement);

			MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

          Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
			dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
			if (dgvPlantilla->Columns->Contains("IdJugador")) {
				dgvPlantilla->Columns["IdJugador"]->Visible = false;
			}

			pnlAfegirJugador->Visible = false;
			pnlGestionarEquip->Visible = true;
			txtAJCorreu->Text = L"";
			txtAJDorsal->Text = L"";
			txtAJPosicio->Text = L"";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al afegir jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnAJCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlAfegirJugador->Visible = false;
		pnlGestionarEquip->Visible = true;
		txtAJCorreu->Text = L"";
		txtAJDorsal->Text = L"";
		txtAJPosicio->Text = L"";
		dtpAJDataNaixement->Value = System::DateTime::Now.AddYears(-20);
	}

System::Void Form1::btnEETornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEnregistrarEquip->Visible = false;
		pnlMain->Visible = true;
	}

System::Void Form1::btnEEEnregistrar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtEENom->Text;
		DateTime data = dtpEEData->Value;
		String^ esport = cmbEEEscollirEsport->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(esport)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlEnregistrarEquip^ ctrlEE = gcnew Playcampus::Domini::CtrlEnregistrarEquip();
			String^ idEquip = "E-" + Guid::NewGuid().ToString()->Substring(0, 8);
			ctrlEE->EnregistrarEquip(idEquip, nom, data, esport, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Equip enregistrat correctament!", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			btnEnregistrarEquip->Text = L"Gestionar Equip";

			pnlEnregistrarEquip->Visible = false;
			pnlMain->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al enregistrar equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

}
