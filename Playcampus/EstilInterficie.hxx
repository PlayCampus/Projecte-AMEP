#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public ref class EstilInterficie abstract sealed
	{
	public:
		static Color ColorFons() {
			return Color::FromArgb(245, 247, 250);
		}

		static Color ColorTargeta() {
			return Color::White;
		}

		static Color ColorPrimari() {
			return Color::FromArgb(0, 120, 215);
		}

		static Color ColorPrimariFosc() {
			return Color::FromArgb(21, 48, 79);
		}

		static Color ColorText() {
			return Color::FromArgb(35, 39, 47);
		}

		static Color ColorTextSuau() {
			return Color::FromArgb(90, 99, 115);
		}

		static Color ColorLinia() {
			return Color::FromArgb(215, 221, 230);
		}

		static Font^ FontBase() {
			return gcnew Font(L"Segoe UI", 9.75F, FontStyle::Regular);
		}

		static Font^ FontTitol() {
			return gcnew Font(L"Segoe UI", 16.0F, FontStyle::Bold);
		}

		static Font^ FontSubtitol() {
			return gcnew Font(L"Segoe UI", 11.0F, FontStyle::Bold);
		}

		static Font^ FontTaula() {
			return gcnew Font(L"Segoe UI", 9.0F, FontStyle::Regular);
		}

		static void Aplicar(Control^ control) {
			if (control != nullptr) {
				Form^ formulari = dynamic_cast<Form^>(control);
				if (formulari != nullptr) {
					formulari->BackColor = ColorFons();
					formulari->Font = FontBase();
				}

				Panel^ panel = dynamic_cast<Panel^>(control);
				if (panel != nullptr) {
					panel->BackColor = ColorFons();
				}

				Label^ etiqueta = dynamic_cast<Label^>(control);
				if (etiqueta != nullptr) {
					String^ nom = String::Empty;
					String^ text = String::Empty;
					if (etiqueta->Name != nullptr) {
						nom = etiqueta->Name->ToLowerInvariant();
					}
					if (etiqueta->Text != nullptr) {
						text = etiqueta->Text->ToLowerInvariant();
					}
					bool esTitol = nom->Contains(L"title") || text->Contains(L"estad") || text->Contains(L"playcampus") || text->Contains(L"editar partit") || text->Contains(L"editar jugador");

					etiqueta->BackColor = Color::Transparent;
					etiqueta->ForeColor = esTitol ? ColorPrimariFosc() : ColorText();
					etiqueta->Font = esTitol ? FontTitol() : FontBase();
				}

				Button^ boto = dynamic_cast<Button^>(control);
				if (boto != nullptr) {
					String^ text = String::Empty;
					if (boto->Text != nullptr) {
						text = boto->Text->ToLowerInvariant();
					}
					bool esSecundari = text->Contains(L"tornar") || text->Contains(L"netejar") || text->Contains(L"cancel") || text->Contains(L"registrar-se");

					boto->Font = FontBase();
					boto->Cursor = Cursors::Hand;
					boto->FlatStyle = FlatStyle::Flat;
					boto->FlatAppearance->BorderSize = 1;
					boto->FlatAppearance->BorderColor = esSecundari ? ColorLinia() : ColorPrimari();
					boto->BackColor = esSecundari ? ColorTargeta() : ColorPrimari();
					boto->ForeColor = esSecundari ? ColorPrimariFosc() : Color::White;
				}

				TextBox^ textBox = dynamic_cast<TextBox^>(control);
				if (textBox != nullptr) {
					textBox->Font = FontBase();
					textBox->BackColor = ColorTargeta();
					textBox->ForeColor = ColorText();
					textBox->BorderStyle = BorderStyle::FixedSingle;
				}

				ComboBox^ combo = dynamic_cast<ComboBox^>(control);
				if (combo != nullptr) {
					combo->Font = FontBase();
					combo->BackColor = ColorTargeta();
					combo->ForeColor = ColorText();
					combo->FlatStyle = FlatStyle::Flat;
				}

				DateTimePicker^ data = dynamic_cast<DateTimePicker^>(control);
				if (data != nullptr) {
					data->Font = FontBase();
					data->CalendarMonthBackground = ColorTargeta();
					data->CalendarTitleBackColor = ColorPrimari();
					data->CalendarTitleForeColor = Color::White;
					data->CalendarForeColor = ColorText();
				}

				ListBox^ llista = dynamic_cast<ListBox^>(control);
				if (llista != nullptr) {
					llista->Font = FontBase();
					llista->BackColor = ColorTargeta();
					llista->ForeColor = ColorText();
					llista->BorderStyle = BorderStyle::FixedSingle;
				}

				DataGridView^ taula = dynamic_cast<DataGridView^>(control);
				if (taula != nullptr) {
					AplicarTaula(taula);
				}

				for (int i = 0; i < control->Controls->Count; i++) {
					Aplicar(control->Controls[i]);
				}
			}
		}

		static void AplicarTaula(DataGridView^ taula) {
			if (taula != nullptr) {
				taula->Font = FontTaula();
				taula->BackgroundColor = ColorTargeta();
				taula->BorderStyle = BorderStyle::FixedSingle;
				taula->GridColor = ColorLinia();
				taula->EnableHeadersVisualStyles = false;
				taula->RowHeadersVisible = false;
				taula->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
				taula->AllowUserToAddRows = false;

				taula->ColumnHeadersDefaultCellStyle->BackColor = ColorPrimariFosc();
				taula->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
				taula->ColumnHeadersDefaultCellStyle->Font = gcnew Font(L"Segoe UI", 9.0F, FontStyle::Bold);
				taula->ColumnHeadersDefaultCellStyle->SelectionBackColor = ColorPrimariFosc();
				taula->ColumnHeadersDefaultCellStyle->SelectionForeColor = Color::White;
				taula->ColumnHeadersHeight = 32;

				taula->DefaultCellStyle->BackColor = ColorTargeta();
				taula->DefaultCellStyle->ForeColor = ColorText();
				taula->DefaultCellStyle->SelectionBackColor = Color::FromArgb(220, 235, 250);
				taula->DefaultCellStyle->SelectionForeColor = ColorText();
				taula->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(250, 252, 255);
			}
		}
	};
}
