#include "pch.h"
#include "Form1Partits.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

System::Void Form1::cmbPartitsAEditar_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbPartitsAEditar->SelectedIndex == -1) return;

		String^ selectedDisplayText = cmbPartitsAEditar->SelectedItem->ToString();
		String^ idPartit = partitPerId[selectedDisplayText];

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			auto detallPartit = ctrl->ObtenirDetallPartit(idPartit, currentUsuariCorreu);

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
			dt->Columns->Add("Gols", System::Int32::typeid);
			dt->Columns->Add("Assistencies", System::Int32::typeid);
			dt->Columns->Add("Targetes Grogues", System::Int32::typeid);
			dt->Columns->Add("Targetes Vermelles", System::Int32::typeid);

			for each (auto jugador in jugadors) {
				dt->Rows->Add(jugador["idJugador"], jugador["nomJugador"], jugador["nomEquip"], 0, 0, 0, 0);
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
		if (cmbPartitsAEditar->SelectedIndex == -1) {
			MessageBox::Show(L"Selecciona un partit primer.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ selectedDisplayText = cmbPartitsAEditar->SelectedItem->ToString();
		String^ idPartit = partitPerId[selectedDisplayText];
		String^ nouEstat = cmbEstatPartit->SelectedItem->ToString();
		int golsLocal;
		int golsVisitant;

		if (!Int32::TryParse(txtResultatLocal->Text, golsLocal) || !Int32::TryParse(txtResultatVisitant->Text, golsVisitant)) {
			MessageBox::Show(L"Els resultats han de ser números enters.", L"Error de validació", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		System::Text::StringBuilder^ statsCsv = gcnew System::Text::StringBuilder();
		statsCsv->AppendLine("idJugador;NomJugador;equip;gols;assistencies;targetesGrogues;targetesVermelles");

		for each (DataGridViewRow^ row in dgvEstadistiquesJugadors->Rows) {
			if (row->IsNewRow) continue;
			String^ idJugador = row->Cells["idJugador"]->Value->ToString();
			String^ nom = row->Cells["Nom Jugador"]->Value->ToString();
			String^ equip = row->Cells["Equip"]->Value->ToString();
			int gols = Convert::ToInt32(row->Cells["Gols"]->Value);
			int assist = Convert::ToInt32(row->Cells["Assistencies"]->Value);
			int tg = Convert::ToInt32(row->Cells["Targetes Grogues"]->Value);
			int tv = Convert::ToInt32(row->Cells["Targetes Vermelles"]->Value);
			statsCsv->AppendFormat("{0};{1};{2};{3};{4};{5};{6}\n", idJugador, nom, equip, gols, assist, tg, tv);
		}

		Nullable<DateTime> novaData;
		if (nouEstat == "Aplaçat") {
			novaData = dtpDataPartit->Value;
		}

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			ctrl->ActualitzarPartitIStats(idPartit, nouEstat, golsLocal, golsVisitant, statsCsv->ToString(), currentUsuariCorreu, novaData);
			MessageBox::Show(L"Partit i estadístiques actualitzats correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			btnTornarEditarPartit_Click(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al guardar les dades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::btnTornarEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEditarPartit->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

System::Void Form1::cmbEstatPartit_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		bool esAplacat = cmbEstatPartit->SelectedItem->ToString() == "Aplaçat";
		lblDataPartit->Visible = esAplacat;
		dtpDataPartit->Visible = esAplacat;
	}

System::Void Form1::btnGLAfegirPartit_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearPartit->Visible = true;

			// Netejem tot 
			txtCPNomLliga->Text = L"";
			cmbCPTemporada->Items->Clear();
			cmbCPJornada->Items->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();
			txtCPUbicacio->Text = L"";
			dtpCPData->Value = DateTime::Now;

			// Deshabilitem combos fins que es validi la lliga
			cmbCPTemporada->Enabled = false;
			cmbCPJornada->Enabled = false;
			cmbCPEquipLocal->Enabled = false;
			cmbCPEquipVisitant->Enabled = false;
		}

System::Void Form1::btnGLEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
           MostrarPantallaEditarPartit();
			return;
			try {
                Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();

				String^ nomLliga = ctrl->ObtenirNomLligaAdmin(currentUsuariCorreu);
				if (String::IsNullOrWhiteSpace(nomLliga)) {
					MessageBox::Show(L"No s'ha trobat cap lliga associada a aquest administrador.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

				auto partits = ctrl->ObtenirPartitsPerLliga(nomLliga, currentUsuariCorreu);
				if (partits->Count == 0) {
					MessageBox::Show(L"No s'han trobat partits per a aquesta lliga.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return;
				}

				Form^ frmPartit = gcnew Form();
				frmPartit->Text = L"Editar partit - Selecció de partit";
              frmPartit->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				frmPartit->StartPosition = FormStartPosition::CenterParent;
				frmPartit->ClientSize = System::Drawing::Size(720, 170);
				frmPartit->MinimizeBox = false;
				frmPartit->MaximizeBox = false;

				Label^ lblPartit = gcnew Label();
				lblPartit->Text = L"Selecciona el partit:";
				lblPartit->Location = System::Drawing::Point(20, 22);
				lblPartit->AutoSize = true;

				ComboBox^ cmbPartits = gcnew ComboBox();
				cmbPartits->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbPartits->Location = System::Drawing::Point(20, 48);
				cmbPartits->Size = System::Drawing::Size(680, 24);

				for each (auto p in partits) {
					String^ display = p["dataHora"] + L" - " + p["equipLocal"] + L" vs " + p["equipVisitant"] + L" [" + p["estat"] + L"]";
					cmbPartits->Items->Add(display);
				}

				if (cmbPartits->Items->Count > 0) {
					cmbPartits->SelectedIndex = 0;
				}

				Button^ btnOkPartit = gcnew Button();
				btnOkPartit->Text = L"Editar";
				btnOkPartit->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnOkPartit->Location = System::Drawing::Point(520, 110);
				btnOkPartit->Size = System::Drawing::Size(85, 30);

				Button^ btnCancelPartit = gcnew Button();
				btnCancelPartit->Text = L"Cancel·lar";
				btnCancelPartit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelPartit->Location = System::Drawing::Point(615, 110);
				btnCancelPartit->Size = System::Drawing::Size(85, 30);

				frmPartit->Controls->Add(lblPartit);
				frmPartit->Controls->Add(cmbPartits);
				frmPartit->Controls->Add(btnOkPartit);
				frmPartit->Controls->Add(btnCancelPartit);
				frmPartit->AcceptButton = btnOkPartit;
				frmPartit->CancelButton = btnCancelPartit;

				if (frmPartit->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) {
					return;
				}

				if (cmbPartits->SelectedIndex < 0) {
					MessageBox::Show(L"Selecciona un partit.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

		
				String^ idPartit = partits[cmbPartits->SelectedIndex]->default["idPartit"];

				auto detall = ctrl->ObtenirDetallPartit(idPartit, currentUsuariCorreu);

				String^ disciplina = detall["disciplina"];
				String^ disciplinaLower = disciplina->ToLowerInvariant();
               array<String^>^ campsStats;
				if (disciplinaLower->Contains(L"fut")) {
					campsStats = gcnew array<String^>{ L"gols", L"assistencies", L"targetesGrogues", L"targetesVermelles" };
				}
				else if (disciplinaLower->Contains(L"basq")) {
					campsStats = gcnew array<String^>{ L"punts", L"rebots", L"assistencies", L"faltes" };
				}
				else {
					campsStats = gcnew array<String^>{ L"punts", L"aces", L"blocs", L"errors" };
				}

				Form^ frmEditar = gcnew Form();
				frmEditar->Text = L"Editar partit";
              frmEditar->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				frmEditar->StartPosition = FormStartPosition::CenterParent;
				frmEditar->ClientSize = System::Drawing::Size(760, 540);
				frmEditar->MinimizeBox = false;
				frmEditar->MaximizeBox = false;

				Label^ lblEstat = gcnew Label();
				lblEstat->Text = L"Estat del partit:";
				lblEstat->Location = System::Drawing::Point(20, 20);
				lblEstat->AutoSize = true;

				ComboBox^ cmbEstat = gcnew ComboBox();
				cmbEstat->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbEstat->Items->AddRange(gcnew cli::array<System::Object^>(4) { L"Pendent", L"En joc", L"Finalitzat", L"Aplaçat" });
				cmbEstat->Location = System::Drawing::Point(150, 18);
				cmbEstat->Size = System::Drawing::Size(160, 24);

				int idxEstat = cmbEstat->FindStringExact(detall["estat"]);
				cmbEstat->SelectedIndex = (idxEstat >= 0) ? idxEstat : 0;

				Label^ lblNovaData = gcnew Label();
             lblNovaData->Text = L"Nova data i hora (si Aplaçat):";
				lblNovaData->Location = System::Drawing::Point(340, 20);
				lblNovaData->AutoSize = true;

				DateTimePicker^ dtpNovaData = gcnew DateTimePicker();
              dtpNovaData->Format = DateTimePickerFormat::Custom;
				dtpNovaData->CustomFormat = L"dd/MM/yyyy HH:mm";
				dtpNovaData->ShowUpDown = true;
				dtpNovaData->Location = System::Drawing::Point(500, 18);
             dtpNovaData->Size = System::Drawing::Size(150, 22);
				dtpNovaData->Value = DateTime::Now.AddDays(1);

				Label^ lblResLocal = gcnew Label();
				lblResLocal->Text = L"Resultat local:";
				lblResLocal->Location = System::Drawing::Point(20, 62);
				lblResLocal->AutoSize = true;

				NumericUpDown^ numLocal = gcnew NumericUpDown();
				numLocal->Location = System::Drawing::Point(150, 60);
				numLocal->Size = System::Drawing::Size(100, 22);
				numLocal->Minimum = 0;
				numLocal->Maximum = 300;

				Label^ lblResVisit = gcnew Label();
				lblResVisit->Text = L"Resultat visitant:";
				lblResVisit->Location = System::Drawing::Point(280, 62);
				lblResVisit->AutoSize = true;

				NumericUpDown^ numVisit = gcnew NumericUpDown();
				numVisit->Location = System::Drawing::Point(420, 60);
				numVisit->Size = System::Drawing::Size(100, 22);
				numVisit->Minimum = 0;
				numVisit->Maximum = 300;

				int golsLocal = 0;
				int golsVisitant = 0;
				Int32::TryParse(detall["golsLocal"], golsLocal);
				Int32::TryParse(detall["golsVisitant"], golsVisitant);
				numLocal->Value = golsLocal;
				numVisit->Value = golsVisitant;

				Label^ lblDisc = gcnew Label();
				lblDisc->Text = L"Disciplina de la lliga: " + disciplina;
				lblDisc->Location = System::Drawing::Point(20, 104);
				lblDisc->AutoSize = true;

				Label^ lblStatsInfo = gcnew Label();
                lblStatsInfo->Text = L"Estadístiques individuals (taula per jugadors):";
				lblStatsInfo->Location = System::Drawing::Point(20, 132);
				lblStatsInfo->AutoSize = true;

                DataGridView^ dgvStats = gcnew DataGridView();
				dgvStats->Location = System::Drawing::Point(20, 160);
				dgvStats->Size = System::Drawing::Size(720, 310);
                dgvStats->AllowUserToAddRows = false;
				dgvStats->AllowUserToDeleteRows = true;
				dgvStats->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
				dgvStats->RowHeadersVisible = false;
				dgvStats->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

				DataGridViewCheckBoxColumn^ colIncloure = gcnew DataGridViewCheckBoxColumn();
				colIncloure->HeaderText = L"Incloure";
				colIncloure->Name = L"Incloure";
				colIncloure->Width = 70;
				dgvStats->Columns->Add(colIncloure);

				DataGridViewTextBoxColumn^ colNom = gcnew DataGridViewTextBoxColumn();
				colNom->HeaderText = L"NomJugador";
				colNom->Name = L"NomJugador";
				dgvStats->Columns->Add(colNom);

				DataGridViewComboBoxColumn^ colEquip = gcnew DataGridViewComboBoxColumn();
				colEquip->HeaderText = L"equip";
				colEquip->Name = L"equip";
				colEquip->Items->Add(L"Local");
				colEquip->Items->Add(L"Visitant");
				dgvStats->Columns->Add(colEquip);

				for each (String ^ camp in campsStats) {
					DataGridViewTextBoxColumn^ col = gcnew DataGridViewTextBoxColumn();
					col->HeaderText = camp;
					col->Name = camp;
					dgvStats->Columns->Add(col);
				}

				auto jugadorsPartit = ctrl->ObtenirJugadorsPartit(idPartit, currentUsuariCorreu);
				if (jugadorsPartit->Count == 0) {
                    dgvStats->AllowUserToAddRows = false;
				}

				for each (auto j in jugadorsPartit) {
					String^ nomJ = j["nomJugador"];
					String^ equipJ = j["equip"];
					array<Object^>^ fila = gcnew array<Object^>(3 + campsStats->Length);
					fila[0] = false;
					fila[1] = nomJ;
					fila[2] = equipJ;
					for (int i = 0; i < campsStats->Length; ++i) {
						fila[3 + i] = L"0";
					}

					dgvStats->Rows->Add(fila);
				}

				Button^ btnGuardar = gcnew Button();
				btnGuardar->Text = L"Guardar canvis";
				btnGuardar->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnGuardar->Location = System::Drawing::Point(548, 490);
				btnGuardar->Size = System::Drawing::Size(95, 32);

				Button^ btnCancelEditar = gcnew Button();
				btnCancelEditar->Text = L"Cancel·lar";
				btnCancelEditar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelEditar->Location = System::Drawing::Point(648, 490);
				btnCancelEditar->Size = System::Drawing::Size(92, 32);

				frmEditar->Controls->Add(lblEstat);
				frmEditar->Controls->Add(cmbEstat);
              frmEditar->Controls->Add(lblNovaData);
				frmEditar->Controls->Add(dtpNovaData);
				frmEditar->Controls->Add(lblResLocal);
				frmEditar->Controls->Add(numLocal);
				frmEditar->Controls->Add(lblResVisit);
				frmEditar->Controls->Add(numVisit);
				frmEditar->Controls->Add(lblDisc);
				frmEditar->Controls->Add(lblStatsInfo);
             frmEditar->Controls->Add(dgvStats);
				frmEditar->Controls->Add(btnGuardar);
				frmEditar->Controls->Add(btnCancelEditar);
				frmEditar->AcceptButton = btnGuardar;
				frmEditar->CancelButton = btnCancelEditar;

				if (frmEditar->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) {
					return;
				}

				if (String::IsNullOrWhiteSpace(cmbEstat->Text)) {
					MessageBox::Show(L"Selecciona un estat del partit.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

                bool esAplacat = (cmbEstat->Text == L"Aplaçat");
				if (esAplacat) {
					numLocal->Value = 0;
					numVisit->Value = 0;
				}

				String^ statsSerialitzades = L"";
				if (!esAplacat) {
					String^ capcalera = L"NomJugador;equip";
					for each (String ^ camp in campsStats) {
						capcalera += L";" + camp;
					}

					System::Text::StringBuilder^ sbStats = gcnew System::Text::StringBuilder();
					sbStats->AppendLine(capcalera);

					for each (DataGridViewRow ^ row in dgvStats->Rows) {
						if (row->IsNewRow) continue;

						bool incloure = false;
						if (row->Cells[0]->Value != nullptr) {
							incloure = Convert::ToBoolean(row->Cells[0]->Value);
						}
						if (!incloure) continue;

						String^ nomJugador = (row->Cells[1]->Value == nullptr) ? L"" : row->Cells[1]->Value->ToString()->Trim();
						String^ equipJugador = (row->Cells[2]->Value == nullptr) ? L"" : row->Cells[2]->Value->ToString()->Trim();

						if (String::IsNullOrWhiteSpace(nomJugador) && String::IsNullOrWhiteSpace(equipJugador)) {
							continue;
						}

						if (String::IsNullOrWhiteSpace(nomJugador) || String::IsNullOrWhiteSpace(equipJugador)) {
							MessageBox::Show(L"Cada fila de estadístiques ha de tenir NomJugador i Equip.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						}

						String^ liniaStats = nomJugador + L";" + equipJugador;
						for (int i = 0; i < campsStats->Length; ++i) {
							Object^ valor = row->Cells[3 + i]->Value;
							String^ txtValor = (valor == nullptr) ? L"0" : valor->ToString()->Trim();

							int valorNumeric = 0;
							if (!Int32::TryParse(txtValor, valorNumeric) || valorNumeric < 0) {
								MessageBox::Show(L"Els camps estadístics han de ser números enters positius o zero.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
								return;
							}

							liniaStats += L";" + valorNumeric.ToString();
						}

						sbStats->AppendLine(liniaStats);
					}

                   statsSerialitzades = sbStats->ToString();
				}
				Nullable<DateTime> novaDataPartit = Nullable<DateTime>();
				if (esAplacat) {
					novaDataPartit = dtpNovaData->Value;
				}

				ctrl->ActualitzarPartitIStats(
					idPartit,
					cmbEstat->Text,
					Convert::ToInt32(numLocal->Value),
					Convert::ToInt32(numVisit->Value),
                    statsSerialitzades,
					currentUsuariCorreu,
					novaDataPartit
				);

				MessageBox::Show(L"Partit actualitzat correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error en editar el partit: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

System::Void Form1::btnCPValidarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtCPNomLliga->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) {
			MessageBox::Show(L"Introdueix el nom de la Lliga a validar", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();

			// 1. Validar que la liga existe y somos dueños
			if (!ctrl->ValidarAdministradorLliga(nomLliga, currentUsuariCorreu)) {
				MessageBox::Show(L"No ets administrador d'aquesta lliga o no existeix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// 2. Obtener Temporadas
			auto temporades = ctrl->ObtenirTemporadesLliga(nomLliga);
			cmbCPTemporada->Items->Clear();
			cpTemporadesIds->Clear();

			for each(auto temp in temporades) {
				String^ txt = temp["dataInici"] + L" a " + temp["dataFi"];
				cmbCPTemporada->Items->Add(txt);
				cpTemporadesIds->Add(temp["idTemporada"]); // Guardar ID Oculto
			}

			// 3. Cargar Equipos (se hace por liga, así que los cargamos ya)
			auto equips = ctrl->ObtenirNomsEquipsPerLliga(nomLliga);
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();

			for each(String ^ nom in equips) {
				cmbCPEquipLocal->Items->Add(nom);
				cmbCPEquipVisitant->Items->Add(nom);
			}

			// Habilitar los combos porque la liga es válida
			cmbCPTemporada->Enabled = true;
			cmbCPEquipLocal->Enabled = true;
			cmbCPEquipVisitant->Enabled = true;

			if (cmbCPTemporada->Items->Count > 0) cmbCPTemporada->SelectedIndex = 0;

			MessageBox::Show(L"Lliga carregada correctament. Selecciona temporada i equips.", L"Lliga Trobada", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al validar la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

System::Void Form1::cmbCPTemporada_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbCPTemporada->SelectedIndex == -1) return;

		try {
			Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();
			String^ idTempSeleccionada = cpTemporadesIds[cmbCPTemporada->SelectedIndex];

			auto jornades = ctrl->ObtenirJornadesTemporada(idTempSeleccionada);

			cmbCPJornada->Items->Clear();
			cpJornadesIds->Clear();

			for each(auto jorn in jornades) {
				String^ text = L"Jornada " + jorn["numero"] + L" (" + jorn["dataInici"] + L")";
				cmbCPJornada->Items->Add(text);
				cpJornadesIds->Add(jorn["idJornada"]); // Guardar la ID
			}

			cmbCPJornada->Enabled = true;
			if (cmbCPJornada->Items->Count > 0) cmbCPJornada->SelectedIndex = 0;
			else MessageBox::Show(L"Aquesta temporada no té jornades.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);

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
			if (cmbCPJornada->SelectedIndex == -1 || cmbCPEquipLocal->SelectedIndex == -1 || cmbCPEquipVisitant->SelectedIndex == -1 || String::IsNullOrWhiteSpace(txtCPUbicacio->Text) || String::IsNullOrWhiteSpace(txtCPNomLliga->Text)) {
				MessageBox::Show(L"Si us plau, valida la lliga i omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ equipLocal = cmbCPEquipLocal->SelectedItem->ToString();
			String^ equipVisit = cmbCPEquipVisitant->SelectedItem->ToString();

			if (equipLocal == equipVisit) {
				MessageBox::Show(L"L'equip local i visitant no poden ser el mateix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			DateTime dataPartit = dtpCPData->Value;
			String^ ubicacioStr = txtCPUbicacio->Text;
			String^ lligaStr = txtCPNomLliga->Text;

			// Agafar la ID de la jornada que hem guardat prèviament al omplir el ComboBox
			int indexJornada = cmbCPJornada->SelectedIndex;
			if (indexJornada < 0 || indexJornada >= cpJornadesIds->Count) {
				MessageBox::Show(L"No s'ha pogut determinar la jornada seleccionada", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ idJornada = cpJornadesIds[indexJornada];

			try {
				Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();

				// Passem l'ID de la jornada (String) en el 5è paràmetre
				ctrl->CrearPartit(dataPartit, ubicacioStr, equipLocal, equipVisit, idJornada, currentUsuariTipus);

				MessageBox::Show(L"Partit creat i desat a la base de dades correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
			MessageBox::Show(L"Si us plau, selecciona una temporada, una jornada i finalment un partit per a esborrar.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ idPartit = epPartitIds[cmbEPPartits->SelectedIndex];
		String^ displayPartit = cmbEPPartits->SelectedItem->ToString();

		System::Windows::Forms::DialogResult confirm = MessageBox::Show(
			L"Estàs segur d'eliminar definitivament el partit: \n\n" + displayPartit + L"?",
			L"Confirmació de Borrat",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Exclamation);

		if (confirm == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				ctrl->EsborrarPartit(idPartit);

				MessageBox::Show(L"Partit eliminat de la Base de Dades correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				// Refresquem el desplegable recarregant la jornada seleccionada en comptes de tancar 
				cmbEPJornades_SelectedIndexChanged(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Hi ha hagut una fallada: " + ex->Message, L"Error Crític", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

}
