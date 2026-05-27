#include "pch.h"
#include "Form1Partits.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

void Form1::ConfigurarLabelsEditarPartitSegonsEsport(System::String^ disciplina) {
		// Pre: disciplina indica l'esport del partit seleccionat o pot ser buida.
		// Post: les etiquetes visibles del panell d'editar partit queden adaptades a l'esport.
		etiquetesEditarPartitActual = Playcampus::Domini::EtiquetesEditarPartit::ObtenirEtiquetesEditarPartit(disciplina);
		disciplinaPartitEditarActual = etiquetesEditarPartitActual["disciplinaNormalitzada"];

		lblEditarPartitTitle->Text = etiquetesEditarPartitActual["titol"];
		lblResultatLocal->Text = etiquetesEditarPartitActual["marcadorLocal"];
		lblResultatVisitant->Text = etiquetesEditarPartitActual["marcadorVisitant"];
	}

	System::String^ Form1::ObtenirIdPartitEditarSeleccionat() {
		// Pre: el combo de partits pot tenir o no una selecci\u00F3 activa.
		// Post: retorna l'id del partit seleccionat o nullptr si no es pot determinar.
		String^ idPartit = nullptr;

		if (cmbPartitsAEditar->SelectedIndex >= 0 && cmbPartitsAEditar->SelectedItem != nullptr) {
			String^ selectedDisplayText = cmbPartitsAEditar->SelectedItem->ToString();
			if (partitPerId != nullptr && partitPerId->ContainsKey(selectedDisplayText)) {
				idPartit = partitPerId[selectedDisplayText];
			}
		}

		return idPartit;
	}

	System::Boolean Form1::ValidarEnterNoNegatiuEditarPartit(System::String^ textValor, System::String^ etiquetaCamp, int% valorNumeric) {
		// Pre: textValor \u00E9s el text introdu\u00EFt en un camp num\u00E8ric del formulari.
		// Post: retorna true si el valor \u00E9s un enter >= 0; en cas contrari mostra un missatge coherent amb l'etiqueta visible.
		bool esValid = false;
		valorNumeric = 0;
		String^ etiquetaNeta = etiquetaCamp;

		if (!String::IsNullOrWhiteSpace(etiquetaNeta)) {
			etiquetaNeta = etiquetaNeta->Replace(L":", L"")->Trim();
		}
		else {
			etiquetaNeta = L"camp num\u00E8ric";
		}

		if (String::IsNullOrWhiteSpace(textValor)) {
			MessageBox::Show(L"El camp '" + etiquetaNeta + L"' no pot estar buit.", L"Error de validaci\u00F3", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (!Int32::TryParse(textValor->Trim(), valorNumeric)) {
			MessageBox::Show(L"El camp '" + etiquetaNeta + L"' ha de ser un n\u00FAmero enter.", L"Error de validaci\u00F3", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (valorNumeric < 0) {
			MessageBox::Show(L"El camp '" + etiquetaNeta + L"' no pot ser negatiu.", L"Error de validaci\u00F3", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			esValid = true;
		}

		return esValid;
	}

	System::Void Form1::cmbPartitsAEditar_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbPartitsAEditar->SelectedIndex == -1) return;

		String^ idPartit = ObtenirIdPartitEditarSeleccionat();
		if (String::IsNullOrWhiteSpace(idPartit)) {
			MessageBox::Show(L"No s'ha pogut determinar el partit seleccionat.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			auto detallPartit = ctrl->ObtenirDetallPartit(idPartit, currentUsuariCorreu);
			String^ disciplina = detallPartit->ContainsKey("disciplina") ? detallPartit["disciplina"] : L"";
			ConfigurarLabelsEditarPartitSegonsEsport(disciplina);

			txtResultatLocal->Text = detallPartit["golsLocal"];
			txtResultatVisitant->Text = detallPartit["golsVisitant"];
			int idxEstat = cmbEstatPartit->FindStringExact(detallPartit["estat"]);
			cmbEstatPartit->SelectedIndex = (idxEstat >= 0) ? idxEstat : -1;

			auto jugadors = ctrl->ObtenirJugadorsPartit(idPartit, currentUsuariCorreu);
			dgvEstadistiquesJugadors->Columns->Clear();
			dgvEstadistiquesJugadors->DataSource = nullptr;

			DataTable^ dt = gcnew DataTable();
			dt->Columns->Add("idJugador");
			dt->Columns->Add("Nom Jugador");
			dt->Columns->Add("Equip");
			dt->Columns->Add(etiquetesEditarPartitActual["estadistica1"], System::Int32::typeid);
			dt->Columns->Add(etiquetesEditarPartitActual["estadistica2"], System::Int32::typeid);
			dt->Columns->Add(etiquetesEditarPartitActual["estadistica3"], System::Int32::typeid);
			dt->Columns->Add(etiquetesEditarPartitActual["estadistica4"], System::Int32::typeid);

			for each (auto jugador in jugadors) {
				int estadistica1 = 0;
				int estadistica2 = 0;
				int estadistica3 = 0;
				int estadistica4 = 0;

				if (jugador->ContainsKey("estadistica1") && !String::IsNullOrWhiteSpace(jugador["estadistica1"])) {
					Int32::TryParse(jugador["estadistica1"], estadistica1);
				}
				if (jugador->ContainsKey("estadistica2") && !String::IsNullOrWhiteSpace(jugador["estadistica2"])) {
					Int32::TryParse(jugador["estadistica2"], estadistica2);
				}
				if (jugador->ContainsKey("estadistica3") && !String::IsNullOrWhiteSpace(jugador["estadistica3"])) {
					Int32::TryParse(jugador["estadistica3"], estadistica3);
				}
				if (jugador->ContainsKey("estadistica4") && !String::IsNullOrWhiteSpace(jugador["estadistica4"])) {
					Int32::TryParse(jugador["estadistica4"], estadistica4);
				}

				dt->Rows->Add(jugador["idJugador"], jugador["nomJugador"], jugador["nomEquip"], safe_cast<System::Object^>(estadistica1), safe_cast<System::Object^>(estadistica2), safe_cast<System::Object^>(estadistica3), safe_cast<System::Object^>(estadistica4));
			}

			dgvEstadistiquesJugadors->DataSource = dt;
			dgvEstadistiquesJugadors->Columns["idJugador"]->Visible = false;
			dgvEstadistiquesJugadors->Columns["Nom Jugador"]->ReadOnly = true;
			dgvEstadistiquesJugadors->Columns["Equip"]->ReadOnly = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar els detalls del partit: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::btnGuardarEstadistiques_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ idPartit = ObtenirIdPartitEditarSeleccionat();
		bool dadesValides = true;

		if (String::IsNullOrWhiteSpace(idPartit)) {
			MessageBox::Show(L"Selecciona un partit abans de guardar els canvis.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dadesValides = false;
		}

		String^ nouEstat = L"";
		if (dadesValides) {
			if (cmbEstatPartit->SelectedItem == nullptr || String::IsNullOrWhiteSpace(cmbEstatPartit->Text)) {
				MessageBox::Show(L"Selecciona un estat del partit.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				dadesValides = false;
			}
			else {
				nouEstat = cmbEstatPartit->SelectedItem->ToString();
			}
		}

		int marcadorLocal = 0;
		int marcadorVisitant = 0;
		if (dadesValides) {
			bool localValid = ValidarEnterNoNegatiuEditarPartit(txtResultatLocal->Text, lblResultatLocal->Text, marcadorLocal);
			bool visitantValid = ValidarEnterNoNegatiuEditarPartit(txtResultatVisitant->Text, lblResultatVisitant->Text, marcadorVisitant);
			dadesValides = localValid && visitantValid;
		}

		System::Text::StringBuilder^ statsCsv = gcnew System::Text::StringBuilder();
		bool estadistiquesValides = true;
		statsCsv->AppendLine("idJugador;NomJugador;equip;anotacions;assistencies;sancionsLleus;sancionsGreus");

		if (dadesValides && dgvEstadistiquesJugadors->Columns->Count < 7) {
			MessageBox::Show(L"Selecciona un partit v\u00E0lid perqu\u00E8 es carreguin les estad\u00EDstiques abans de guardar.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dadesValides = false;
		}

		if (dadesValides) {
			for each (DataGridViewRow^ row in dgvEstadistiquesJugadors->Rows) {
				if (!row->IsNewRow && estadistiquesValides) {
					String^ idJugador = row->Cells[0]->Value == nullptr ? L"" : row->Cells[0]->Value->ToString();
					String^ nom = row->Cells[1]->Value == nullptr ? L"" : row->Cells[1]->Value->ToString();
					String^ equip = row->Cells[2]->Value == nullptr ? L"" : row->Cells[2]->Value->ToString();
					array<int>^ valors = gcnew array<int>(4);

					for (int i = 0; i < 4; ++i) {
						String^ etiquetaColumna = dgvEstadistiquesJugadors->Columns[3 + i]->HeaderText;
						String^ textValor = row->Cells[3 + i]->Value == nullptr ? L"" : row->Cells[3 + i]->Value->ToString();
						int valorNumeric = 0;
						bool valorValid = ValidarEnterNoNegatiuEditarPartit(textValor, etiquetaColumna, valorNumeric);
						if (valorValid) {
							valors[i] = valorNumeric;
						}
						else {
							estadistiquesValides = false;
						}
					}

					if (estadistiquesValides) {
						statsCsv->AppendFormat("{0};{1};{2};{3};{4};{5};{6}\n", idJugador, nom, equip, valors[0], valors[1], valors[2], valors[3]);
					}
				}
			}
		}

		Nullable<DateTime> novaData = Nullable<DateTime>();
		if (dadesValides && estadistiquesValides && nouEstat == "Apla\u00E7at") {
			novaData = dtpDataPartit->Value;
			marcadorLocal = 0;
			marcadorVisitant = 0;
		}

		if (dadesValides && estadistiquesValides) {
			try {
				Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
				ctrl->ActualitzarPartitIStats(idPartit, nouEstat, marcadorLocal, marcadorVisitant, statsCsv->ToString(), currentUsuariCorreu, novaData);
				MessageBox::Show(L"Partit i estad\u00EDstiques actualitzats correctament.", L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				btnTornarEditarPartit_Click(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al guardar les dades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	System::Void Form1::btnTornarEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEditarPartit->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

	System::Void Form1::cmbEstatPartit_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		bool esAplacat = false;
		if (cmbEstatPartit->SelectedItem != nullptr) {
			esAplacat = cmbEstatPartit->SelectedItem->ToString() == "Apla\u00E7at";
		}
		lblDataPartit->Visible = esAplacat;
		dtpDataPartit->Visible = esAplacat;
	}

	System::Void Form1::btnGLAfegirPartit_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearPartit->Visible = true;

			// Netejem tot 
			// txtCPNomLliga is no longer required
			cmbCPTemporada->Items->Clear();
			cmbCPJornada->Items->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();
			txtCPUbicacio->Text = L"";
			dtpCPData->Value = DateTime::Now;

			cmbCPTemporada->Enabled = false;
			cmbCPJornada->Enabled = false;
			cmbCPEquipLocal->Enabled = false;
			cmbCPEquipVisitant->Enabled = false;

			try {
				Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();
				String^ nomLliga = ctrl->ObtenirNomLligaAdministrador(currentUsuariCorreu);

				if (String::IsNullOrEmpty(nomLliga)) {
					MessageBox::Show(L"No ets administrador de cap lliga.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				auto temporades = ctrl->ObtenirTemporadesLliga(nomLliga);
				cmbCPTemporada->Items->Clear();
				cpTemporadesIds->Clear();

				for each(auto temp in temporades) {
					String^ txt = temp["dataInici"] + L" a " + temp["dataFi"];
					cmbCPTemporada->Items->Add(txt);
					cpTemporadesIds->Add(temp["idTemporada"]);
				}

				cmbCPTemporada->Enabled = true;

				if (cmbCPTemporada->Items->Count > 0) cmbCPTemporada->SelectedIndex = 0;

			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar les dades de la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

System::Void Form1::btnGLEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		MostrarPantallaEditarPartit();
	}

System::Void Form1::btnCPValidarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		// Aquest botó ja no fa res, l'obtenció és automàtica en obrir el panel
	}

System::Void Form1::cmbCPTemporada_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbCPTemporada->SelectedIndex == -1) return;

		try {
			Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();
			String^ idTempSeleccionada = cpTemporadesIds[cmbCPTemporada->SelectedIndex];

			auto jornades = ctrl->ObtenirJornadesTemporada(idTempSeleccionada);

			cmbCPJornada->Items->Clear();
			cpJornadesIds->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();

			for each(auto jorn in jornades) {
				String^ text = L"Jornada " + jorn["numero"] + L" (" + jorn["dataInici"] + L")";
				cmbCPJornada->Items->Add(text);
				cpJornadesIds->Add(jorn["idJornada"]); // Guardar la ID
			}

			auto equips = ctrl->ObtenirNomsEquipsPerTemporada(idTempSeleccionada);
			for each(String ^ nom in equips) {
				cmbCPEquipLocal->Items->Add(nom);
				cmbCPEquipVisitant->Items->Add(nom);
			}

			cmbCPJornada->Enabled = true;
			cmbCPEquipLocal->Enabled = cmbCPEquipLocal->Items->Count > 0;
			cmbCPEquipVisitant->Enabled = cmbCPEquipVisitant->Items->Count > 0;

			if (cmbCPJornada->Items->Count > 0) cmbCPJornada->SelectedIndex = 0;
			else MessageBox::Show(L"Aquesta temporada no t\u00E9 jornades.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);

			if (cmbCPEquipLocal->Items->Count == 0) {
				MessageBox::Show(L"Aquesta temporada no t\u00E9 equips inscrits.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}

		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant jornades: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnCPCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlCrearPartit->Visible = false;

			// Netegem els combos quan marxem
			cmbCPJornada->Items->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();
			txtCPUbicacio->Text = L"";

			if (btnCrearLligaMainMenu->Text == L"Gestionar Lliga") {
				pnlGestionarLliga->Visible = true;
			}
			else {
				pnlMain->Visible = true;
			}
		}

System::Void Form1::btnCPConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
			// Validar dades
			if (cmbCPJornada->SelectedIndex == -1 || cmbCPEquipLocal->SelectedIndex == -1 || cmbCPEquipVisitant->SelectedIndex == -1 || String::IsNullOrWhiteSpace(txtCPUbicacio->Text)) {
				MessageBox::Show(L"Si us plau, valida la lliga i omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ equipLocal = cmbCPEquipLocal->SelectedItem->ToString();
			String^ equipVisit = cmbCPEquipVisitant->SelectedItem->ToString();

			if (String::Equals(equipLocal, equipVisit, StringComparison::Ordinal)) {
				MessageBox::Show(L"L'equip local i visitant no poden ser el mateix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			DateTime dataPartit = dtpCPData->Value;
			String^ ubicacioStr = txtCPUbicacio->Text;

			// Agafar la ID de la jornada que hem guardat prèviament al omplir el ComboBox
			int indexJornada = cmbCPJornada->SelectedIndex;
			if (indexJornada < 0 || indexJornada >= cpJornadesIds->Count) {
				MessageBox::Show(L"No s'ha pogut determinar la jornada seleccionada", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ idJornada = cpJornadesIds[indexJornada];

			try {
				Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();

				// Passem l'ID de la jornada (String) en el 5\u00E8 par\u00E0metre
				ctrl->CrearPartit(dataPartit, ubicacioStr, equipLocal, equipVisit, idJornada, currentUsuariTipus);

				MessageBox::Show(L"Partit creat i desat a la base de dades correctament!", L"\u00C8xit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				pnlCrearPartit->Visible = false;
				pnlGestionarLliga->Visible = true;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al desar el partit: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

System::Void Form1::btnGLEsborrarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarLliga->Visible = false;
		pnlEsborrarPartit->Visible = true;
		CarregarTemporadesEsborrar();
	}

System::Void Form1::btnEPTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEsborrarPartit->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

void Form1::CarregarTemporadesEsborrar() {
		cmbEPTemporades->Items->Clear();
		epTemporadaIds->Clear();
		cmbEPJornades->Items->Clear();
		epJornadaIds->Clear();
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		try {
			Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
			auto temporades = ctrl->ObtenirTemporadesAdmin(currentUsuariCorreu);

			for each(auto dict in temporades) {
				String^ display = dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
				cmbEPTemporades->Items->Add(display);
				epTemporadaIds->Add(dict["idTemporada"]);
			}

			if (cmbEPTemporades->Items->Count > 0) cmbEPTemporades->SelectedIndex = 0;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar temporades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::cmbEPTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cmbEPJornades->Items->Clear();
		epJornadaIds->Clear();
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		if (cmbEPTemporades->SelectedIndex >= 0) {
			String^ idTemporadaStr = epTemporadaIds[cmbEPTemporades->SelectedIndex];

			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				auto jornades = ctrl->ObtenirJornadesPerTemporada(idTemporadaStr);

				for each(auto dict in jornades) {
					// AFEGIM dataFi i estat per Jornada
					String^ display = L"Jornada " + dict["numero"] + L" | " + dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
					cmbEPJornades->Items->Add(display);
					epJornadaIds->Add(dict["idJornada"]);
				}

				if (cmbEPJornades->Items->Count > 0) cmbEPJornades->SelectedIndex = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar jornades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

System::Void Form1::cmbEPJornades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		if (cmbEPJornades->SelectedIndex >= 0) {
			String^ idJornadaStr = epJornadaIds[cmbEPJornades->SelectedIndex];

			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				auto partits = ctrl->ObtenirPartitsPerJornada(idJornadaStr);

				for each(auto dict in partits) {
					String^ ubicacio = String::IsNullOrWhiteSpace(dict["ubicacio"]) ? L"Sense ubi" : dict["ubicacio"];
					// AFEGIM Els noms dels equips: local vs visitant
					String^ display = dict["dataHora"] + L" | " + dict["equipLocal"] + L" vs " + dict["equipVisitant"] + L" (Ubi: " + ubicacio + L") [" + dict["estat"] + L"]";
					cmbEPPartits->Items->Add(display);
					epPartitIds->Add(dict["idPartit"]);
				}

				if (cmbEPPartits->Items->Count > 0) cmbEPPartits->SelectedIndex = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar partits: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

System::Void Form1::btnEPEsborrarFinal_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEPPartits->SelectedIndex < 0) {
			MessageBox::Show(L"Si us plau, selecciona una temporada, una jornada i finalment un partit per a esborrar.", L"Av\u00EDs", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ idPartit = epPartitIds[cmbEPPartits->SelectedIndex];
		String^ displayPartit = cmbEPPartits->SelectedItem->ToString();
			System::Windows::Forms::DialogResult confirm = MessageBox::Show(
				L"Est\u00E0s segur d'eliminar definitivament el partit: \n\n" + displayPartit +
				L"?\n\nTamb\u00E9 s'eliminaran les estad\u00EDstiques individuals del partit i es restaran de les estad\u00EDstiques acumulades dels equips i jugadors.",
				L"Confirmaci\u00F3 de borrat",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Exclamation);

		if (confirm == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				ctrl->EsborrarPartit(idPartit);

				MessageBox::Show(L"Partit eliminat correctament.", L"", MessageBoxButtons::OK, MessageBoxIcon::Information);

				// Refresquem el desplegable recarregant la jornada seleccionada en comptes de tancar 
				cmbEPJornades_SelectedIndexChanged(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Hi ha hagut una fallada: " + ex->Message, L"Error Cr\u00EDtic", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

}
