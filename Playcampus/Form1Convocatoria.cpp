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

			// Necessitem l'equip del capit�
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			String^ idEquip = ctrlInici->ObtenirIdEquipDeCapita(currentUsuariCorreu);

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			auto jugadors = ctrl->ObtenirEstatConvocatoria(idPartit, idEquip);

			dgvConvocatoria->Columns->Clear();
			dgvConvocatoria->Columns->Add("ID", "ID Jugador");
			dgvConvocatoria->Columns->Add("Nom", "Nom");
			dgvConvocatoria->Columns->Add("Pos", "Posici�");
			dgvConvocatoria->Columns->Add("Estat", "Estat Convocat�ria");
			dgvConvocatoria->Columns->Add("Conf", "Confirmaci�");

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

			bool nouEstat = (estatActual == "No Convocat"); // Invertim l'estat

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ActualitzarConvocatoria(idPartit, idJugador, nouEstat);

			// Recarreguem la taula
			cbPartitsConvocatoria_SelectedIndexChanged(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al canviar estat: " + ex->Message);
		}
	}

System::Void Form1::MostrarAvisJugador(String^ missatge) {
		if (pnlAvisJugador != nullptr) pnlMain->Controls->Remove(pnlAvisJugador);

		pnlAvisJugador = gcnew System::Windows::Forms::Panel();
		// 1. FEM EL PANELL M�S ALT (Abans era 150, ara 220)
		pnlAvisJugador->Size = System::Drawing::Size(500, 220);
		pnlAvisJugador->BackColor = System::Drawing::Color::LightYellow;
		pnlAvisJugador->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

		// 2. EL POSEM A DALT A L'ESQUERRA (Marge de 20 p�xels perqu� no toqui la vora)
		pnlAvisJugador->Location = System::Drawing::Point(20, 20);

		System::Windows::Forms::Label^ lblMissatge = gcnew System::Windows::Forms::Label();
		lblMissatge->Text = missatge;
		// 3. FEM L'ESPAI DEL TEXT M�S GRAN (Abans era 80, ara 140)
		lblMissatge->Size = System::Drawing::Size(480, 140);
		lblMissatge->Location = System::Drawing::Point(10, 10); // Una mica m�s amunt
		lblMissatge->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblMissatge->Font = gcnew System::Drawing::Font("Arial", 11, System::Drawing::FontStyle::Bold);

		System::Windows::Forms::Button^ btnSi = gcnew System::Windows::Forms::Button();
		btnSi->Text = L"S�, hi anir�";
		btnSi->Size = System::Drawing::Size(100, 35);
		// 4. BAIXEM ELS BOTONS PERQU� NO TREPITGIN EL TEXT (Abans Y era 100, ara 160)
		btnSi->Location = System::Drawing::Point(140, 160);
		btnSi->BackColor = System::Drawing::Color::LightGreen;
		btnSi->Click += gcnew System::EventHandler(this, &Form1::btnConfirmarSi_Click);

		System::Windows::Forms::Button^ btnNo = gcnew System::Windows::Forms::Button();
		btnNo->Text = L"No puc";
		btnNo->Size = System::Drawing::Size(100, 35);
		// BAIXEM TAMB� AQUEST BOT� (Y = 160)
		btnNo->Location = System::Drawing::Point(260, 160);
		btnNo->BackColor = System::Drawing::Color::Salmon;
		btnNo->Click += gcnew System::EventHandler(this, &Form1::btnConfirmarNo_Click);

		pnlAvisJugador->Controls->Add(lblMissatge);
		pnlAvisJugador->Controls->Add(btnSi);
		pnlAvisJugador->Controls->Add(btnNo);

		pnlMain->Controls->Add(pnlAvisJugador);
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
			String^ idJugador = ctrlInici->ObtenirIdUsuari(currentUsuariCorreu); // Necessites aquest m�tode

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ConfirmarAssistencia(idPartitPendentConfirmar, idJugador, assisteix);

			MessageBox::Show(L"S'ha guardat la teva resposta correctament.");
			pnlMain->Controls->Remove(pnlAvisJugador); // Amaguem el cartell
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al confirmar: " + ex->Message);
		}
	}


}
