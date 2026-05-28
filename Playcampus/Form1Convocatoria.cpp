#include "pch.h"
#include "Form1Convocatoria.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Void Form1::btnGestionarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlConvocatoria->Visible = true;
		pnlConvocatoria->BringToFront();
		CarregarPartitsConvocatoria();
		Form1_Resize(nullptr, nullptr);
	}

	System::Void Form1::btnTornarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlConvocatoria->Visible = false;
		pnlMain->Visible = true;
	}

	System::Void Form1::CarregarPartitsConvocatoria() {
		try {
			cbPartitsConvocatoria->Items->Clear();
			convocatoriaPartitIds->Clear();

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			auto partits = ctrl->ObtenirPartitsCapita(currentUsuariCorreu);

			if (partits != nullptr && partits->Count > 0) {
				for each (auto p in partits) {
					cbPartitsConvocatoria->Items->Add(p["nomMostrar"]);
					convocatoriaPartitIds->Add(p["id_partit"]);
				}
				cbPartitsConvocatoria->SelectedIndex = 0;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error: " + ex->Message);
		}
	}

	System::Void Form1::cbPartitsConvocatoria_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cbPartitsConvocatoria->SelectedIndex < 0) return;

		try {
			String^ idPartit = convocatoriaPartitIds[cbPartitsConvocatoria->SelectedIndex];

			// Necessitem l'equip del capità
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			String^ idEquip = ctrlInici->ObtenirIdEquipDeCapita(currentUsuariCorreu);

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			auto jugadors = ctrl->ObtenirEstatConvocatoria(idPartit, idEquip);

			dgvConvocatoria->Columns->Clear();
			dgvConvocatoria->Columns->Add("ID", "ID Jugador");
			dgvConvocatoria->Columns->Add("Nom", "Nom");
			dgvConvocatoria->Columns->Add("Pos", "Posició");
			dgvConvocatoria->Columns->Add("Estat", "Estat Convocatòria");
			dgvConvocatoria->Columns->Add("Conf", "Confirmació");

			dgvConvocatoria->Columns["ID"]->Visible = false; // Ocultem l'ID

			if (jugadors != nullptr) {
				for each (auto j in jugadors) {
					dgvConvocatoria->Rows->Add(j["id_jugador"], j["nom"], j["posicio"], j["estat_convocatoria"], j["confirmacio"]);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error taula: " + ex->Message);
		}
	}

	System::Void Form1::dgvConvocatoria_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex < 0) return;

		try {
			String^ idJugador = dgvConvocatoria->Rows[e->RowIndex]->Cells["ID"]->Value->ToString();
			String^ estatActual = dgvConvocatoria->Rows[e->RowIndex]->Cells["Estat"]->Value->ToString();
			String^ idPartit = convocatoriaPartitIds[cbPartitsConvocatoria->SelectedIndex];

			Nullable<bool> nouEstat;

			// NUEVA LÓGICA CÍCLICA: Sense establir -> No Convocat -> Convocat -> Sense establir
			if (estatActual == "Sense establir" || estatActual == "") {
				nouEstat = false; // Pasa de NULL a 'No Convocat' (0)
			}
			else if (estatActual == "No Convocat") {
				nouEstat = true;  // Pasa de 'No Convocat' a 'Convocat' (1)
			}
			else {
				nouEstat = Nullable<bool>(); // Pasa de 'Convocat' de vuelta a 'Sense establir' (NULL)
			}

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ActualitzarConvocatoria(idPartit, idJugador, nouEstat);

			// Recarreguem la taula per veure els canvis reflectits immediatament
			cbPartitsConvocatoria_SelectedIndexChanged(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al canviar estat: " + ex->Message);
		}
	}

	System::Void Form1::MostrarAvisJugador(String^ missatge, String^ tipus) {
		// El cartell s'ha de mostrar per sobre de qualsevol element del menú principal
		// (p.ex. el dashboard de la lliga seguida). Per això el pengem directament del
		// Form en lloc de pnlMain.
		if (pnlAvisJugador != nullptr) this->Controls->Remove(pnlAvisJugador);

		pnlAvisJugador = gcnew System::Windows::Forms::Panel();
		pnlAvisJugador->Size = System::Drawing::Size(500, 220);
		pnlAvisJugador->BackColor = System::Drawing::Color::LightYellow;
		pnlAvisJugador->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		int x = (this->ClientSize.Width - pnlAvisJugador->Width) / 2;
		int y = (this->ClientSize.Height - pnlAvisJugador->Height) / 2;
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		pnlAvisJugador->Location = System::Drawing::Point(x, y);

		System::Windows::Forms::Label^ lblMissatge = gcnew System::Windows::Forms::Label();
		lblMissatge->Text = missatge;
		lblMissatge->Size = System::Drawing::Size(480, 140);
		lblMissatge->Location = System::Drawing::Point(10, 10);
		lblMissatge->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblMissatge->Font = gcnew System::Drawing::Font("Arial", 11, System::Drawing::FontStyle::Bold);
		pnlAvisJugador->Controls->Add(lblMissatge);

		// EVALUAMOS EL TIPO DE AVISO
		if (tipus == "no_convocat") {
			// Un único botón de aceptación para los no convocados
			System::Windows::Forms::Button^ btnOk = gcnew System::Windows::Forms::Button();
			btnOk->Text = L"D'acord";
			btnOk->Size = System::Drawing::Size(120, 35);
			btnOk->Location = System::Drawing::Point(190, 160); // Centrado horizontalmente
			btnOk->BackColor = System::Drawing::Color::LightGray;
			// Reutiliza tu lógica existente: al hacer clic guardará un '0' quitando el estado Pendent
			btnOk->Click += gcnew System::EventHandler(this, &Form1::btnConfirmarNo_Click);

			pnlAvisJugador->Controls->Add(btnOk);
		}
		else {
			// El diseño original de Sí/No para los jugadores que SÍ están convocados
			System::Windows::Forms::Button^ btnSi = gcnew System::Windows::Forms::Button();
			btnSi->Text = L"Sí, hi aniré";
			btnSi->Size = System::Drawing::Size(100, 35);
			btnSi->Location = System::Drawing::Point(140, 160);
			btnSi->BackColor = System::Drawing::Color::LightGreen;
			btnSi->Click += gcnew System::EventHandler(this, &Form1::btnConfirmarSi_Click);

			System::Windows::Forms::Button^ btnNo = gcnew System::Windows::Forms::Button();
			btnNo->Text = L"No puc";
			btnNo->Size = System::Drawing::Size(100, 35);
			btnNo->Location = System::Drawing::Point(260, 160);
			btnNo->BackColor = System::Drawing::Color::Salmon;
			btnNo->Click += gcnew System::EventHandler(this, &Form1::btnConfirmarNo_Click);

			pnlAvisJugador->Controls->Add(btnSi);
			pnlAvisJugador->Controls->Add(btnNo);
		}

		this->Controls->Add(pnlAvisJugador);
		pnlAvisJugador->BringToFront();
	}

	System::Void Form1::btnConfirmarSi_Click(System::Object^ sender, System::EventArgs^ e) {
		ProcessarConfirmacio(true);
	}

	System::Void Form1::btnConfirmarNo_Click(System::Object^ sender, System::EventArgs^ e) {
		ProcessarConfirmacio(false);
	}

	System::Void Form1::ProcessarConfirmacio(bool assisteix) {
		try {
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			String^ idJugador = ctrlInici->ObtenirIdUsuari(currentUsuariCorreu);

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ConfirmarAssistencia(idPartitPendentConfirmar, idJugador, assisteix);

			MessageBox::Show(L"S'ha guardat la teva resposta correctament.");
			this->Controls->Remove(pnlAvisJugador);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al confirmar: " + ex->Message);
		}
	}

}