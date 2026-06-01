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
		if (btnUnirEquipLliga->Tag != nullptr && System::Convert::ToString(btnUnirEquipLliga->Tag) == L"Abandonar Lliga") {
			System::Windows::Forms::DialogResult result = MessageBox::Show(L"Est\u00E0s segur que vols abandonar la lliga? Les estad\u00EDstiques de l'equip es reiniciaran.", L"Abandonar Lliga", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
			if (result == System::Windows::Forms::DialogResult::Yes) {
				try {
					Playcampus::Domini::CtrlAbandonarLliga^ ctrl = gcnew Playcampus::Domini::CtrlAbandonarLliga();
					String^ missatgeExit = ctrl->AbandonarLliga(currentUsuariCorreu);
					MessageBox::Show(missatgeExit, L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);

					btnUnirEquipLliga->Tag = L"Unir-se a una Lliga";
					btnUnirEquipLliga->Text = Tr(L"Unir-se a una Lliga");

					pnlMain->Visible = false;
					pnlMain->Visible = true;
					ActualitzarEstatSeguirLliga();
					Form1_Resize(nullptr, nullptr);
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
		ActualitzarEstatSeguirLliga();
		Form1_Resize(nullptr, nullptr);
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

		if (String::IsNullOrWhiteSpace(passLliga)) return;

		try {
			Playcampus::Domini::CtrlUnirEquipLliga^ ctrl = gcnew Playcampus::Domini::CtrlUnirEquipLliga();

			if (ctrl->ValidarContrasenyaLliga(nomLliga, passLliga)) {
				String^ missatgeExit = ctrl->VincularEquip(currentUsuariCorreu, nomLliga);
				MessageBox::Show(missatgeExit, L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				btnUnirEquipLliga->Tag = L"Abandonar Lliga";
				btnUnirEquipLliga->Text = Tr(L"Abandonar Lliga");

				pnlUnirEquipLliga->Visible = false;
				pnlMain->Visible = true;
				ActualitzarEstatSeguirLliga();
				Form1_Resize(nullptr, nullptr);
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
		if (btnEnregistrarEquip->Tag != nullptr && System::Convert::ToString(btnEnregistrarEquip->Tag) == L"Gestionar Equip") {
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
		ActualitzarEstatSeguirLliga();
		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::btnGEEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult result = MessageBox::Show(L"Est\u00E0s segur que vols esborrar l'equip?", L"Esborrar Equip", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (result == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarEquip^ ctrlEsborrar = gcnew Playcampus::Domini::CtrlEsborrarEquip();
				ctrlEsborrar->EsborrarEquip(currentUsuariCorreu);

				MessageBox::Show(L"Equip esborrat correctament!", L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				btnEnregistrarEquip->Tag = L"Enregistrar Equip";
				btnEnregistrarEquip->Text = Tr(L"Enregistrar Equip");
				pnlGestionarEquip->Visible = false;
				pnlMain->Visible = true;
				ActualitzarEstatSeguirLliga();
				Form1_Resize(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error a l'esborrar l'equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	System::Void Form1::btnGEConvocarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
			MessageBox::Show(L"Nom\u00E9s els capitans poden accedir a aquesta funcionalitat.", L"Acc\u00E9s denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else {
			try {
				convocatoriaObertaDesDeGestionarEquip = true;
				btnTornarConvocatoria->Text = Tr(L"Tornar a Gestionar Equip");
				pnlGestionarEquip->Visible = false;
				pnlMain->Visible = false;
				pnlConvocatoria->Visible = true;
				pnlConvocatoria->BringToFront();
				CarregarPartitsConvocatoria();
				Form1_Resize(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error en obrir la gesti\u00F3 de convocat\u00F2ria: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
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
			MessageBox::Show(L"Nom\u00E9s els capitans poden accedir a aquesta funcionalitat.", L"Acc\u00E9s denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dgvPlantilla->SelectedRows == nullptr || dgvPlantilla->SelectedRows->Count == 0) {
			MessageBox::Show(L"Selecciona un jugador de la plantilla.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
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
			L"Confirmaci\u00F3",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning);

		if (confirmacio != System::Windows::Forms::DialogResult::Yes) {
			return;
		}

		try {
			Playcampus::Domini::CtrlEliminarJugador^ ctrlEliminar = gcnew Playcampus::Domini::CtrlEliminarJugador();
			String^ resultat = ctrlEliminar->EliminarJugador(currentUsuariCorreu, idJugador);
			MessageBox::Show(resultat, L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);

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
			MessageBox::Show(L"Nom\u00E9s els capitans poden accedir a aquesta funcionalitat.", L"Acc\u00E9s denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dgvPlantilla->SelectedRows == nullptr || dgvPlantilla->SelectedRows->Count == 0) {
			MessageBox::Show(L"Selecciona un jugador de la plantilla per editar.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
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

			if (dgvPlantilla->Columns->Contains(L"Posici\u00F3") && row->Cells[L"Posici\u00F3"]->Value != nullptr) {
				posicio = row->Cells[L"Posici\u00F3"]->Value->ToString();
			}

			// Validar datos mínimos
			if (String::IsNullOrWhiteSpace(idJugador) || String::IsNullOrWhiteSpace(nomJugador)) {
				MessageBox::Show(L"No s'ha pogut obtenir l'informaci\u00F3 del jugador seleccionat.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

					MessageBox::Show(L"Jugador actualitzat correctament.", L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
			MessageBox::Show(L"El dorsal ha de ser m\u00E9s gran que 0 i menor o igual que 99.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlAfegirJugador^ ctrlAfegir = gcnew Playcampus::Domini::CtrlAfegirJugador();
			String^ resultat = ctrlAfegir->AfegirJugador(correuEstudiant, dorsal, posicioText, currentUsuariCorreu, dataNaixement);

			MessageBox::Show(resultat, L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);

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
		ActualitzarEstatSeguirLliga();
		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::btnEEEnregistrar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtEENom->Text;
		DateTime data = dtpEEData->Value;
		String^ esport = cmbEEEscollirEsport->Text;
		String^ esportGuardar = esport;
		if (esport == L"B\u00E0squet") esportGuardar = L"Basquet";
		else if (esport == L"V\u00F2lei") esportGuardar = L"Voley";

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(esport)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlEnregistrarEquip^ ctrlEE = gcnew Playcampus::Domini::CtrlEnregistrarEquip();
			String^ idEquip = "E-" + Guid::NewGuid().ToString()->Substring(0, 8);
			ctrlEE->EnregistrarEquip(idEquip, nom, data, esportGuardar, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Equip enregistrat correctament!", L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			btnEnregistrarEquip->Tag = L"Gestionar Equip";
			btnEnregistrarEquip->Text = Tr(L"Gestionar Equip");

			pnlEnregistrarEquip->Visible = false;
			pnlMain->Visible = true;
			ActualitzarEstatSeguirLliga();
			Form1_Resize(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al enregistrar equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

}
