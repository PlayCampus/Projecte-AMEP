#include "pch.h"
#include "Form1.h"
#include "EstilInterficie.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	Form1::Form1(void) {
		InitializeComponent(); // IMPORTANT: NO ESBORRAR

		// 1. Creació d'objectes
		this->pnlConvocatoria = gcnew System::Windows::Forms::Panel();
		this->btnGestionarConvocatoria = gcnew System::Windows::Forms::Button();
		this->btnTornarConvocatoria = gcnew System::Windows::Forms::Button();
		this->cbPartitsConvocatoria = gcnew System::Windows::Forms::ComboBox();
		this->lblConvocatoriaInfo = gcnew System::Windows::Forms::Label();
		this->dgvConvocatoria = gcnew System::Windows::Forms::DataGridView();
		this->convocatoriaPartitIds = gcnew System::Collections::Generic::List<System::String^>();
		this->convocatoriaObertaDesDeGestionarEquip = false;

		// 2. Propietats i Events
		this->btnGestionarConvocatoria->Text = L"Gestionar Convocat\u00F2ries";
		this->btnGestionarConvocatoria->Click += gcnew System::EventHandler(this, &Form1::btnGestionarConvocatoria_Click);

		this->btnTornarConvocatoria->Text = L"Tornar";
		this->btnTornarConvocatoria->Click += gcnew System::EventHandler(this, &Form1::btnTornarConvocatoria_Click);

		this->cbPartitsConvocatoria->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbPartitsConvocatoria->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbPartitsConvocatoria_SelectedIndexChanged);

		this->lblConvocatoriaInfo->Text = L"Selecciona un partit i fes clic a un jugador per canviar-ne l'estat.";
		this->lblConvocatoriaInfo->AutoSize = false;
		this->lblConvocatoriaInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

		this->dgvConvocatoria->AllowUserToAddRows = false;
		this->dgvConvocatoria->ReadOnly = true;
		this->dgvConvocatoria->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvConvocatoria->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
		this->dgvConvocatoria->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dgvConvocatoria_CellClick);

		// 3. Jerarquia (Afegir-los a la pantalla)
		// La gestió de convocatòries només s'obre des de Gestionar Equip.
		this->Controls->Add(this->pnlConvocatoria);
		this->pnlConvocatoria->Controls->Add(this->btnTornarConvocatoria);
		this->pnlConvocatoria->Controls->Add(this->cbPartitsConvocatoria);
		this->pnlConvocatoria->Controls->Add(this->lblConvocatoriaInfo);
		this->pnlConvocatoria->Controls->Add(this->dgvConvocatoria);

		// 4. Estat Inicial
		this->pnlConvocatoria->Visible = false;
		this->btnGestionarConvocatoria->Visible = false;

		// --- INICI ESTADÍSTIQUES PARTIT ---
		this->btnEstPartit = gcnew System::Windows::Forms::Button();
		this->btnEstJugadors = gcnew System::Windows::Forms::Button();
		this->pnlEstadistiquesPartitDetail = gcnew System::Windows::Forms::Panel();
		this->lblEstPartitTitle = gcnew System::Windows::Forms::Label();
		this->lblEstPartitLliga = gcnew System::Windows::Forms::Label();
		this->cmbEstPartitLligues = gcnew System::Windows::Forms::ComboBox();
		this->lblEstPartitTemporada = gcnew System::Windows::Forms::Label();
		this->cmbEstPartitTemporades = gcnew System::Windows::Forms::ComboBox();
		this->lblEstPartitBuscar = gcnew System::Windows::Forms::Label();
		this->txtEstPartitBuscar = gcnew System::Windows::Forms::TextBox();
		this->btnEstPartitCercar = gcnew System::Windows::Forms::Button();
		this->btnEstPartitNetejar = gcnew System::Windows::Forms::Button();
		this->lblEstPartitPartits = gcnew System::Windows::Forms::Label();
		this->cmbEstPartitPartits = gcnew System::Windows::Forms::ComboBox();
		this->lblEstPartitInfo = gcnew System::Windows::Forms::Label();
		this->lblEstPartitResultat = gcnew System::Windows::Forms::Label();
		this->dgvEstPartitDetalls = gcnew System::Windows::Forms::DataGridView();
		this->btnEstPartitTornar = gcnew System::Windows::Forms::Button();

		this->estPartitLligaIds = gcnew System::Collections::Generic::List<String^>();
		this->estPartitTemporadaIds = gcnew System::Collections::Generic::List<String^>();
		this->estPartitIds = gcnew System::Collections::Generic::List<String^>();

		this->btnEstPartit->Text = L"Estad\u00EDstiques Partit";
		this->btnEstPartit->Click += gcnew System::EventHandler(this, &Form1::btnEstPartit_Click);
		this->btnEstPartitTornar->Text = L"Tornar";
		this->btnEstPartitTornar->Size = System::Drawing::Size(145, 38);
		this->btnEstPartitTornar->Click += gcnew System::EventHandler(this, &Form1::btnEstPartitTornar_Click);

		this->lblEstPartitTitle->Text = L"ESTAD\u00CDSTIQUES DE PARTIT";
		this->lblEstPartitTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold);
		this->lblEstPartitTitle->AutoSize = true;

		this->lblEstPartitLliga->Text = L"Selecciona Lliga:";
		this->lblEstPartitTemporada->Text = L"Selecciona Temporada:";
		this->lblEstPartitBuscar->Text = L"Cercar partit:";
		this->btnEstPartitCercar->Text = L"Cercar";
		this->btnEstPartitNetejar->Text = L"Netejar";
		this->lblEstPartitPartits->Text = L"Selecciona Partit:";
		this->lblEstPartitInfo->Text = L"";
		this->lblEstPartitResultat->Text = L"";

		this->lblEstPartitLliga->AutoSize = true;
		this->lblEstPartitTemporada->AutoSize = true;
		this->lblEstPartitBuscar->AutoSize = true;
		this->lblEstPartitPartits->AutoSize = true;
		this->lblEstPartitInfo->AutoSize = false;
		this->lblEstPartitResultat->AutoSize = false;
		this->lblEstPartitInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		this->lblEstPartitResultat->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

		this->lblEstPartitLliga->Visible = false;
		this->cmbEstPartitLligues->Visible = false;
		this->lblEstPartitTemporada->Visible = false;
		this->cmbEstPartitTemporades->Visible = false;
		this->lblEstPartitPartits->Visible = false;
		this->cmbEstPartitPartits->Visible = false;

		this->cmbEstPartitLligues->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstPartitTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstPartitPartits->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstPartitPartits->DropDownWidth = 900;

		this->cmbEstPartitLligues->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitLligues_SelectedIndexChanged);
		this->cmbEstPartitTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitTemporades_SelectedIndexChanged);
		this->cmbEstPartitPartits->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstPartitPartits_SelectedIndexChanged);
		this->btnEstPartitCercar->Click += gcnew System::EventHandler(this, &Form1::btnEstPartitCercar_Click);
		this->btnEstPartitNetejar->Click += gcnew System::EventHandler(this, &Form1::btnEstPartitNetejar_Click);
		this->txtEstPartitBuscar->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::txtEstPartitBuscar_KeyDown);

		this->dgvEstPartitDetalls->AllowUserToAddRows = false;
		this->dgvEstPartitDetalls->ReadOnly = true;
		this->dgvEstPartitDetalls->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;

		this->dgvEstPartitDetalls->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;

		// Configuración del botón Estadístiques Jugadors
		this->btnEstJugadors->Text = L"Estad\u00EDstiques Jugadors";
		this->btnEstJugadors->Click += gcnew System::EventHandler(this, &Form1::btnEstJugadors_Click);

		// Jerarquia
		this->pnlEstadistiques->Controls->Add(this->btnEstPartit);
		this->pnlEstadistiques->Controls->Add(this->btnEstJugadors);

		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitTitle);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitLliga);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitLligues);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitTemporada);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitTemporades);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitBuscar);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->txtEstPartitBuscar);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->btnEstPartitCercar);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->btnEstPartitNetejar);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitPartits);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->cmbEstPartitPartits);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitInfo);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->lblEstPartitResultat);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->dgvEstPartitDetalls);
		this->pnlEstadistiquesPartitDetail->Controls->Add(this->btnEstPartitTornar);

		this->Controls->Add(this->pnlEstadistiquesPartitDetail);
		this->pnlEstadistiquesPartitDetail->Visible = false;
		// --- FI ESTADÍSTIQUES PARTIT ---

		// --- INICI SEGUIR LLIGA (MENÚ PRINCIPAL) ---
		this->btnSeguirLligaMainMenu = gcnew System::Windows::Forms::Button();
		this->btnSeguirLligaMainMenu->Text = L"Seguir Lliga";
		this->btnSeguirLligaMainMenu->Size = System::Drawing::Size(170, 42);
		this->btnSeguirLligaMainMenu->Visible = false;
		this->btnSeguirLligaMainMenu->Click += gcnew System::EventHandler(this, &Form1::btnSeguirLligaMainMenu_Click);
		this->pnlMain->Controls->Add(this->btnSeguirLligaMainMenu);

		this->pnlDashboardLliga = gcnew System::Windows::Forms::Panel();
		this->pnlDashboardLliga->Visible = false;
		this->pnlDashboardLliga->BackColor = System::Drawing::Color::White;
		this->pnlDashboardLliga->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pnlDashboardLliga->Location = System::Drawing::Point(50, 245);
		this->pnlDashboardLliga->Size = System::Drawing::Size(550, 220);
		this->pnlMain->Controls->Add(this->pnlDashboardLliga);

		this->lblDashboardLliga = gcnew System::Windows::Forms::Label();
		this->lblDashboardLliga->Text = L"";
		this->lblDashboardLliga->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Bold);
		this->lblDashboardLliga->AutoSize = true;
		this->pnlDashboardLliga->Controls->Add(this->lblDashboardLliga);

		this->lblDashboardClassificacio = gcnew System::Windows::Forms::Label();
		this->lblDashboardClassificacio->Text = L"Classificaci\u00F3";
		this->lblDashboardClassificacio->AutoSize = true;
		this->pnlDashboardLliga->Controls->Add(this->lblDashboardClassificacio);

		this->dgvDashboardClassificacio = gcnew System::Windows::Forms::DataGridView();
		this->dgvDashboardClassificacio->AllowUserToAddRows = false;
		this->dgvDashboardClassificacio->ReadOnly = true;
		this->dgvDashboardClassificacio->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvDashboardClassificacio->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
		this->pnlDashboardLliga->Controls->Add(this->dgvDashboardClassificacio);

		this->lblDashboardProximsPartits = gcnew System::Windows::Forms::Label();
		this->lblDashboardProximsPartits->Text = L"Pr\u00F2xims partits";
		this->lblDashboardProximsPartits->AutoSize = true;
		this->pnlDashboardLliga->Controls->Add(this->lblDashboardProximsPartits);

		this->dgvDashboardProximsPartits = gcnew System::Windows::Forms::DataGridView();
		this->dgvDashboardProximsPartits->AllowUserToAddRows = false;
		this->dgvDashboardProximsPartits->ReadOnly = true;
		this->dgvDashboardProximsPartits->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvDashboardProximsPartits->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
		this->pnlDashboardLliga->Controls->Add(this->dgvDashboardProximsPartits);

		this->lblDashboardUltimsResultats = gcnew System::Windows::Forms::Label();
		this->lblDashboardUltimsResultats->Text = L"\u00DAltims resultats";
		this->lblDashboardUltimsResultats->AutoSize = true;
		this->pnlDashboardLliga->Controls->Add(this->lblDashboardUltimsResultats);

		this->dgvDashboardUltimsResultats = gcnew System::Windows::Forms::DataGridView();
		this->dgvDashboardUltimsResultats->AllowUserToAddRows = false;
		this->dgvDashboardUltimsResultats->ReadOnly = true;
		this->dgvDashboardUltimsResultats->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvDashboardUltimsResultats->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
		this->pnlDashboardLliga->Controls->Add(this->dgvDashboardUltimsResultats);
		// --- FI SEGUIR LLIGA ---

		InicialitzarSelectorIdioma();
		AplicarIdioma();
		Form1_Resize(nullptr, nullptr);
		EstilInterficie::Aplicar(this);
		if (this->lblIdioma != nullptr) this->lblIdioma->BringToFront();
		if (this->cmbIdioma != nullptr) this->cmbIdioma->BringToFront();
	}

	Form1::~Form1() {
		if (components)
		{
			delete components;
		}
	}


	void Form1::InicialitzarSelectorIdioma() {
		// Crea el selector d'idioma de la interfície.
		if (this->cmbIdioma == nullptr) {
			this->lblIdioma = gcnew System::Windows::Forms::Label();
			this->cmbIdioma = gcnew System::Windows::Forms::ComboBox();
			this->lblIdioma->AutoSize = true;
			this->lblIdioma->BackColor = System::Drawing::Color::White;
			this->lblIdioma->ForeColor = System::Drawing::Color::FromArgb(21, 48, 79);
			this->cmbIdioma->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbIdioma->Items->AddRange(gcnew cli::array<System::Object^>(3) { L"Català", L"Castellano", L"English" });
			this->cmbIdioma->SelectedIndex = 0;
			this->cmbIdioma->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbIdioma_SelectedIndexChanged);
			this->Controls->Add(this->lblIdioma);
			this->Controls->Add(this->cmbIdioma);
		}
	}

	System::String^ Form1::Tr(System::String^ textCa) {
		// Retorna el text traduït segons l'idioma seleccionat.
		System::String^ resultat = textCa;
		int indexIdioma = 0;
		if (this->cmbIdioma != nullptr) indexIdioma = this->cmbIdioma->SelectedIndex;
		if (indexIdioma == 1) {
			if (textCa == L"Iniciar Sessió") resultat = L"Iniciar sesión";
			if (textCa == L"Registrar-se") resultat = L"Registrarse";
			if (textCa == L"Correu") resultat = L"Correo";
			if (textCa == L"Contrasenya") resultat = L"Contraseña";
			if (textCa == L"Nom") resultat = L"Nombre";
			if (textCa == L"Tipus") resultat = L"Tipo";
			if (textCa == L"Telèfon") resultat = L"Teléfono";
			if (textCa == L"Tornar") resultat = L"Volver";
			if (textCa == L"Programació de partits") resultat = L"Programación de partidos";
			if (textCa == L"Estat de les Lligues") resultat = L"Estado de las ligas";
			if (textCa == L"Estadístiques") resultat = L"Estadísticas";
			if (textCa == L"Consultar calendari") resultat = L"Consultar calendario";
			if (textCa == L"Consultar telèfons") resultat = L"Consultar teléfonos";
			if (textCa == L"Últims fitxatges") resultat = L"Últimos fichajes";
			if (textCa == L"Tancar Sessió") resultat = L"Cerrar sesión";
			if (textCa == L"Crear Lliga") resultat = L"Crear liga";
			if (textCa == L"Accés ràpid") resultat = L"Acceso rápido";
			if (textCa == L"Veure calendari de la lliga seguida") resultat = L"Ver calendario de la liga seguida";
			if (textCa == L"Nom de la lliga") resultat = L"Nombre de la liga";
			if (textCa == L"Veure calendari") resultat = L"Ver calendario";
			if (textCa == L"Crear Nova Lliga") resultat = L"Crear nueva liga";
			if (textCa == L"Nom de la Lliga:") resultat = L"Nombre de la liga:";
			if (textCa == L"Esport:") resultat = L"Deporte:";
			if (textCa == L"Enregistrar Equip") resultat = L"Registrar equipo";
			if (textCa == L"Unir equip a lliga") resultat = L"Unir equipo a liga";
			if (textCa == L"Gestionar Lliga") resultat = L"Gestionar liga";
			if (textCa == L"Crear partit") resultat = L"Crear partido";
			if (textCa == L"Editar partit") resultat = L"Editar partido";
			if (textCa == L"Mostrar equips") resultat = L"Mostrar equipos";
			if (textCa == L"Esborrar equip") resultat = L"Borrar equipo";
			if (textCa == L"Estadístiques equips") resultat = L"Estadísticas de equipos";
			if (textCa == L"Esborrar partit") resultat = L"Borrar partido";
			if (textCa == L"Esborrar jornada") resultat = L"Borrar jornada";
			if (textCa == L"Crear Partit") resultat = L"Crear partido";
			if (textCa == L"Nom Lliga:") resultat = L"Nombre liga:";
			if (textCa == L"Validar Lliga") resultat = L"Validar liga";
			if (textCa == L"Data del partit:") resultat = L"Fecha del partido:";
			if (textCa == L"Ubicació:") resultat = L"Ubicación:";
			if (textCa == L"Equip Local:") resultat = L"Equipo local:";
			if (textCa == L"Equip Visitant:") resultat = L"Equipo visitante:";
			if (textCa == L"Cancel·lar") resultat = L"Cancelar";
			if (textCa == L"Crear Temporada") resultat = L"Crear temporada";
			if (textCa == L"Data d'Inici:") resultat = L"Fecha de inicio:";
			if (textCa == L"Data de Fi:") resultat = L"Fecha de fin:";
			if (textCa == L"Crear Jornada") resultat = L"Crear jornada";
			if (textCa == L"Cercar Temporades") resultat = L"Buscar temporadas";
			if (textCa == L"Número Jornada:") resultat = L"Número jornada:";
			if (textCa == L"Nom de l'Equip:") resultat = L"Nombre del equipo:";
			if (textCa == L"Data Fundació:") resultat = L"Fecha de fundación:";
			if (textCa == L"Enregistrar") resultat = L"Registrar";
			if (textCa == L"Gestionar Equip") resultat = L"Gestionar equipo";
			if (textCa == L"Afegir jugador") resultat = L"Añadir jugador";
			if (textCa == L"Editar Jugador") resultat = L"Editar jugador";
			if (textCa == L"Afegir Jugador") resultat = L"Añadir jugador";
			if (textCa == L"Correu Estudiant:") resultat = L"Correo estudiante:";
			if (textCa == L"Posició (Opcional):") resultat = L"Posición (opcional):";
			if (textCa == L"Data Naixement:") resultat = L"Fecha nacimiento:";
			if (textCa == L"Unir Equip a Lliga") resultat = L"Unir equipo a liga";
			if (textCa == L"Comprovar") resultat = L"Comprobar";
			if (textCa == L"Esborrar Partit - Selecció") resultat = L"Borrar partido - Selección";
			if (textCa == L"Tria una Temporada:") resultat = L"Elige una temporada:";
			if (textCa == L"Tria una Jornada:") resultat = L"Elige una jornada:";
			if (textCa == L"Tria el Partit a esborrar:") resultat = L"Elige el partido a borrar:";
			if (textCa == L"Esborrar Partit Seleccionat") resultat = L"Borrar partido seleccionado";
			if (textCa == L"Esborrar Jornada - Selecció") resultat = L"Borrar jornada - Selección";
			if (textCa == L"Tria la Jornada a esborrar:") resultat = L"Elige la jornada a borrar:";
			if (textCa == L"Esborrar Jornada") resultat = L"Borrar jornada";
			if (textCa == L"Estadístiques d'equip") resultat = L"Estadísticas de equipo";
			if (textCa == L"Nom de l'equip:") resultat = L"Nombre del equipo:";
			if (textCa == L"Cercar") resultat = L"Buscar";
			if (textCa == L"Lliga:") resultat = L"Liga:";
			if (textCa == L"Estadístiques Lliga") resultat = L"Estadísticas liga";
			if (textCa == L"Cercar lliga:") resultat = L"Buscar liga:";
			if (textCa == L"Selecciona una lliga:") resultat = L"Selecciona una liga:";
			if (textCa == L"<- Tornar") resultat = L"<- Volver";
			if (textCa == L"Editar Partit i Estadístiques") resultat = L"Editar partido y estadísticas";
			if (textCa == L"Selecciona un partit:") resultat = L"Selecciona un partido:";
			if (textCa == L"Marcador visitant:") resultat = L"Marcador visitante:";
			if (textCa == L"Estat:") resultat = L"Estado:";
			if (textCa == L"Nova data:") resultat = L"Nueva fecha:";
			if (textCa == L"Guardar Canvis") resultat = L"Guardar cambios";
			if (textCa == L"Gestionar Convocatòries") resultat = L"Gestionar convocatorias";
			if (textCa == L"Selecciona un partit i fes clic a un jugador per canviar-ne l'estat.") resultat = L"Selecciona un partido y haz clic en un jugador para cambiar su estado.";
			if (textCa == L"Estadístiques Partit") resultat = L"Estadísticas partido";
			if (textCa == L"ESTADÍSTIQUES DE PARTIT") resultat = L"ESTADÍSTICAS DE PARTIDO";
			if (textCa == L"Selecciona Lliga:") resultat = L"Selecciona liga:";
			if (textCa == L"Selecciona Temporada:") resultat = L"Selecciona temporada:";
			if (textCa == L"Cercar partit:") resultat = L"Buscar partido:";
			if (textCa == L"Netejar") resultat = L"Limpiar";
			if (textCa == L"Selecciona Partit:") resultat = L"Selecciona partido:";
			if (textCa == L"Estadístiques Jugadors") resultat = L"Estadísticas jugadores";
			if (textCa == L"Seguir Lliga") resultat = L"Seguir liga";
			if (textCa == L"Classificació") resultat = L"Clasificación";
			if (textCa == L"Pròxims partits") resultat = L"Próximos partidos";
			if (textCa == L"Últims resultats") resultat = L"Últimos resultados";
			if (textCa == L"Abandonar Lliga") resultat = L"Abandonar liga";
			if (textCa == L"Deixar de seguir lliga actual") resultat = L"Dejar de seguir la liga actual";
			if (textCa == L"Unir-se a una Lliga") resultat = L"Unirse a una liga";
			if (textCa == L"Tornar a Gestionar Equip") resultat = L"Volver a gestionar equipo";
			if (textCa == L"Tornar al Menú") resultat = L"Volver al menú";
			if (textCa == L"D'acord") resultat = L"De acuerdo";
			if (textCa == L"Sí, hi aniré") resultat = L"Sí, iré";
			if (textCa == L"No puc") resultat = L"No puedo";
			if (textCa == L"Tancar") resultat = L"Cerrar";
			if (textCa == L"Calendari: ") resultat = L"Calendario: ";
			if (textCa == L"Lliga: ") resultat = L"Liga: ";
			if (textCa == L"Confirmació") resultat = L"Confirmación";
			if (textCa == L"Avís") resultat = L"Aviso";
			if (textCa == L"Informació") resultat = L"Información";
			if (textCa == L"Èxit") resultat = L"Éxito";
			if (textCa == L"Credencials incorrectes.") resultat = L"Credenciales incorrectas.";
			if (textCa == L"Error en iniciar sessi\u00F3: ") resultat = L"Error al iniciar sesi\u00F3n: ";
			if (textCa == L"Omple tots els camps.") resultat = L"Rellena todos los campos.";
			if (textCa == L"Cal introduir el tel\u00E8fon per al capit\u00E0 i administrador.") resultat = L"Hay que introducir el tel\u00E9fono para el capit\u00E1n y el administrador.";
			if (textCa == L"Usuari registrat correctament!") resultat = L"Usuario registrado correctamente!";
			if (textCa == L"Error al registrar: ") resultat = L"Error al registrar: ";
			if (textCa == L"Est\u00E0s segur que vols deixar de seguir la lliga?") resultat = L"\u00BFSeguro que quieres dejar de seguir la liga?";
			if (textCa == L"Introdueix el nom de la lliga que vols seguir:") resultat = L"Introduce el nombre de la liga que quieres seguir:";
			if (textCa == L"Error: ") resultat = L"Error: ";
			if (textCa == L"Idioma:") resultat = L"Idioma:";
			if (textCa == L"Entrar") resultat = L"Entrar";
			if (textCa == L"Registrar") resultat = L"Registrar";
			if (textCa == L"Contrasenya:") resultat = L"Contraseña:";
			if (textCa == L"Crear") resultat = L"Crear";
			if (textCa == L"Confirmar") resultat = L"Confirmar";
			if (textCa == L"Temporada:") resultat = L"Temporada:";
			if (textCa == L"Jornada:") resultat = L"Jornada:";
			if (textCa == L"Dorsal:") resultat = L"Dorsal:";
			if (textCa == L"Unir") resultat = L"Unir";
			if (textCa == L"Eliminar jugador") resultat = L"Eliminar jugador";
			if (textCa == L"Convocar jugador") resultat = L"Convocar jugador";
			if (textCa == L"Crear jornada") resultat = L"Crear jornada";
			if (textCa == L"Crear temporada") resultat = L"Crear temporada";
			if (textCa == L"Retirar temporada") resultat = L"Retirar temporada";
			if (textCa == L"Marcador local:") resultat = L"Marcador local:";
			if (textCa == L"Esborrar") resultat = L"Borrar";
			if (textCa == L"Esborrar equip de la lliga") resultat = L"Borrar equipo de la liga";
			if (textCa == L"Selecciona l'equip:") resultat = L"Selecciona el equipo:";
			if (textCa == L"Vols treure l'equip ") resultat = L"¿Quieres quitar el equipo ";
			if (textCa == L" de la lliga?") resultat = L" de la liga?";
			if (textCa == L"Equip tret de la lliga correctament.") resultat = L"Equipo quitado de la liga correctamente.";
			if (textCa == L"No tens cap lliga activa associada.") resultat = L"No tienes ninguna liga activa asociada.";
			if (textCa == L"No hi ha equips dins de la teva lliga activa.") resultat = L"No hay equipos dentro de tu liga activa.";
			if (textCa == L"Error carregant els equips: ") resultat = L"Error cargando los equipos: ";
			if (textCa == L"Error en esborrar l'equip de la lliga: ") resultat = L"Error al borrar el equipo de la liga: ";
			if (textCa == L"Funcionalitat en desenvolupament.") resultat = L"Funcionalidad en desarrollo.";
			if (textCa == L"Lliga creada correctament!") resultat = L"¡Liga creada correctamente!";
			if (textCa == L"Error al crear lliga: ") resultat = L"Error al crear liga: ";
			if (textCa == L"Estàs segur que vols retirar la temporada activa respecte a la teva Lliga?") resultat = L"¿Seguro que quieres retirar la temporada activa de tu liga?";
			if (textCa == L"La temporada i les seves jornades han estat retirades correctament!") resultat = L"¡La temporada y sus jornadas se han retirado correctamente!";
			if (textCa == L"Error al retirar la temporada: ") resultat = L"Error al retirar la temporada: ";
			if (textCa == L"Error") resultat = L"Error";
			if (textCa == L"Error BD") resultat = L"Error BD";
			if (textCa == L"OK") resultat = L"OK";
			if (textCa == L"PlayCampus") resultat = L"PlayCampus";
			if (textCa == L"Calendari") resultat = L"Calendario";
			if (textCa == L"Convocatòries") resultat = L"Convocatorias";
			if (textCa == L"No hi ha fitxatges recents.") resultat = L"No hay fichajes recientes.";
			if (textCa == L"No s'han pogut carregar els fitxatges.") resultat = L"No se han podido cargar los fichajes.";
			if (textCa == L"No estàs seguint cap lliga.") resultat = L"No estás siguiendo ninguna liga.";
			if (textCa == L"Error carregant el calendari: ") resultat = L"Error cargando el calendario: ";
			if (textCa == L"Aquesta lliga no existeix") resultat = L"Esta liga no existe";
			if (textCa == L"No hi ha dades per mostrar.") resultat = L"No hay datos para mostrar.";
			if (textCa == L"No hi ha partits pendents per gestionar convocatòries.") resultat = L"No hay partidos pendientes para gestionar convocatorias.";
			if (textCa == L"S'ha guardat la teva resposta correctament.") resultat = L"Se ha guardado tu respuesta correctamente.";
		}
		else if (indexIdioma == 2) {
			if (textCa == L"Idioma:") resultat = L"Language:";
			if (textCa == L"Iniciar Sessió") resultat = L"Log in";
			if (textCa == L"Registrar-se") resultat = L"Sign up";
			if (textCa == L"Correu") resultat = L"Email";
			if (textCa == L"Contrasenya") resultat = L"Password";
			if (textCa == L"Entrar") resultat = L"Enter";
			if (textCa == L"Nom") resultat = L"Name";
			if (textCa == L"Tipus") resultat = L"Type";
			if (textCa == L"Telèfon") resultat = L"Phone";
			if (textCa == L"Registrar") resultat = L"Register";
			if (textCa == L"Tornar") resultat = L"Back";
			if (textCa == L"Programació de partits") resultat = L"Match schedule";
			if (textCa == L"Estat de les Lligues") resultat = L"League status";
			if (textCa == L"Estadístiques") resultat = L"Statistics";
			if (textCa == L"Consultar calendari") resultat = L"View calendar";
			if (textCa == L"Consultar telèfons") resultat = L"View phones";
			if (textCa == L"Últims fitxatges") resultat = L"Latest signings";
			if (textCa == L"Tancar Sessió") resultat = L"Log out";
			if (textCa == L"Crear Lliga") resultat = L"Create league";
			if (textCa == L"Accés ràpid") resultat = L"Quick access";
			if (textCa == L"Veure calendari de la lliga seguida") resultat = L"View followed league calendar";
			if (textCa == L"Nom de la lliga") resultat = L"League name";
			if (textCa == L"Veure calendari") resultat = L"View calendar";
			if (textCa == L"Crear Nova Lliga") resultat = L"Create new league";
			if (textCa == L"Nom de la Lliga:") resultat = L"League name:";
			if (textCa == L"Esport:") resultat = L"Sport:";
			if (textCa == L"Crear") resultat = L"Create";
			if (textCa == L"Enregistrar Equip") resultat = L"Register team";
			if (textCa == L"Unir equip a lliga") resultat = L"Join team to league";
			if (textCa == L"Gestionar Lliga") resultat = L"Manage league";
			if (textCa == L"Crear partit") resultat = L"Create match";
			if (textCa == L"Editar partit") resultat = L"Edit match";
			if (textCa == L"Mostrar equips") resultat = L"Show teams";
			if (textCa == L"Esborrar equip") resultat = L"Delete team";
			if (textCa == L"Crear jornada") resultat = L"Create matchday";
			if (textCa == L"Crear temporada") resultat = L"Create season";
			if (textCa == L"Retirar temporada") resultat = L"Retire season";
			if (textCa == L"Estadístiques equips") resultat = L"Team statistics";
			if (textCa == L"Esborrar partit") resultat = L"Delete match";
			if (textCa == L"Esborrar jornada") resultat = L"Delete matchday";
			if (textCa == L"Crear Partit") resultat = L"Create match";
			if (textCa == L"Nom Lliga:") resultat = L"League name:";
			if (textCa == L"Validar Lliga") resultat = L"Validate league";
			if (textCa == L"Temporada:") resultat = L"Season:";
			if (textCa == L"Jornada:") resultat = L"Matchday:";
			if (textCa == L"Data del partit:") resultat = L"Match date:";
			if (textCa == L"Ubicació:") resultat = L"Location:";
			if (textCa == L"Equip Local:") resultat = L"Home team:";
			if (textCa == L"Equip Visitant:") resultat = L"Away team:";
			if (textCa == L"Confirmar") resultat = L"Confirm";
			if (textCa == L"Cancel·lar") resultat = L"Cancel";
			if (textCa == L"Crear Temporada") resultat = L"Create season";
			if (textCa == L"Data d'Inici:") resultat = L"Start date:";
			if (textCa == L"Data de Fi:") resultat = L"End date:";
			if (textCa == L"Crear Jornada") resultat = L"Create matchday";
			if (textCa == L"Cercar Temporades") resultat = L"Search seasons";
			if (textCa == L"Número Jornada:") resultat = L"Matchday number:";
			if (textCa == L"Nom de l'Equip:") resultat = L"Team name:";
			if (textCa == L"Data Fundació:") resultat = L"Foundation date:";
			if (textCa == L"Enregistrar") resultat = L"Register";
			if (textCa == L"Gestionar Equip") resultat = L"Manage team";
			if (textCa == L"Afegir jugador") resultat = L"Add player";
			if (textCa == L"Eliminar jugador") resultat = L"Remove player";
			if (textCa == L"Convocar jugador") resultat = L"Call up player";
			if (textCa == L"Editar Jugador") resultat = L"Edit player";
			if (textCa == L"Afegir Jugador") resultat = L"Add player";
			if (textCa == L"Correu Estudiant:") resultat = L"Student email:";
			if (textCa == L"Dorsal:") resultat = L"Shirt number:";
			if (textCa == L"Posició (Opcional):") resultat = L"Position (optional):";
			if (textCa == L"Data Naixement:") resultat = L"Birth date:";
			if (textCa == L"Unir Equip a Lliga") resultat = L"Join team to league";
			if (textCa == L"Comprovar") resultat = L"Check";
			if (textCa == L"Unir") resultat = L"Join";
			if (textCa == L"Esborrar Partit - Selecció") resultat = L"Delete match - Selection";
			if (textCa == L"Tria una Temporada:") resultat = L"Choose a season:";
			if (textCa == L"Tria una Jornada:") resultat = L"Choose a matchday:";
			if (textCa == L"Tria el Partit a esborrar:") resultat = L"Choose the match to delete:";
			if (textCa == L"Esborrar Partit Seleccionat") resultat = L"Delete selected match";
			if (textCa == L"Esborrar Jornada - Selecció") resultat = L"Delete matchday - Selection";
			if (textCa == L"Tria la Jornada a esborrar:") resultat = L"Choose the matchday to delete:";
			if (textCa == L"Esborrar Jornada") resultat = L"Delete matchday";
			if (textCa == L"Estadístiques d'equip") resultat = L"Team statistics";
			if (textCa == L"Nom de l'equip:") resultat = L"Team name:";
			if (textCa == L"Cercar") resultat = L"Search";
			if (textCa == L"Lliga:") resultat = L"League:";
			if (textCa == L"Estadístiques Lliga") resultat = L"League statistics";
			if (textCa == L"Cercar lliga:") resultat = L"Search league:";
			if (textCa == L"Selecciona una lliga:") resultat = L"Select a league:";
			if (textCa == L"<- Tornar") resultat = L"<- Back";
			if (textCa == L"Editar Partit i Estadístiques") resultat = L"Edit match and statistics";
			if (textCa == L"Selecciona un partit:") resultat = L"Select a match:";
			if (textCa == L"Marcador local:") resultat = L"Home score:";
			if (textCa == L"Marcador visitant:") resultat = L"Away score:";
			if (textCa == L"Estat:") resultat = L"Status:";
			if (textCa == L"Nova data:") resultat = L"New date:";
			if (textCa == L"Guardar Canvis") resultat = L"Save changes";
			if (textCa == L"Gestionar Convocatòries") resultat = L"Manage call-ups";
			if (textCa == L"Selecciona un partit i fes clic a un jugador per canviar-ne l'estat.") resultat = L"Select a match and click a player to change their status.";
			if (textCa == L"Estadístiques Partit") resultat = L"Match statistics";
			if (textCa == L"ESTADÍSTIQUES DE PARTIT") resultat = L"MATCH STATISTICS";
			if (textCa == L"Selecciona Lliga:") resultat = L"Select league:";
			if (textCa == L"Selecciona Temporada:") resultat = L"Select season:";
			if (textCa == L"Cercar partit:") resultat = L"Search match:";
			if (textCa == L"Netejar") resultat = L"Clear";
			if (textCa == L"Selecciona Partit:") resultat = L"Select match:";
			if (textCa == L"Estadístiques Jugadors") resultat = L"Player statistics";
			if (textCa == L"Seguir Lliga") resultat = L"Follow league";
			if (textCa == L"Classificació") resultat = L"Standings";
			if (textCa == L"Pròxims partits") resultat = L"Upcoming matches";
			if (textCa == L"Últims resultats") resultat = L"Latest results";
			if (textCa == L"Abandonar Lliga") resultat = L"Leave league";
			if (textCa == L"Deixar de seguir lliga actual") resultat = L"Unfollow current league";
			if (textCa == L"Unir-se a una Lliga") resultat = L"Join a league";
			if (textCa == L"Tornar a Gestionar Equip") resultat = L"Back to manage team";
			if (textCa == L"Tornar al Menú") resultat = L"Back to menu";
			if (textCa == L"D'acord") resultat = L"OK";
			if (textCa == L"Sí, hi aniré") resultat = L"Yes, I will go";
			if (textCa == L"No puc") resultat = L"I can't";
			if (textCa == L"Tancar") resultat = L"Close";
			if (textCa == L"Calendari: ") resultat = L"Calendar: ";
			if (textCa == L"Lliga: ") resultat = L"League: ";
			if (textCa == L"Confirmació") resultat = L"Confirmation";
			if (textCa == L"Avís") resultat = L"Warning";
			if (textCa == L"Informació") resultat = L"Information";
			if (textCa == L"Èxit") resultat = L"Success";

			if (textCa == L"Credencials incorrectes.") resultat = L"Incorrect credentials.";
			if (textCa == L"Error en iniciar sessi\u00F3: ") resultat = L"Error while logging in: ";
			if (textCa == L"Omple tots els camps.") resultat = L"Fill in all fields.";
			if (textCa == L"Cal introduir el tel\u00E8fon per al capit\u00E0 i administrador.") resultat = L"The phone number is required for captains and administrators.";
			if (textCa == L"Usuari registrat correctament!") resultat = L"User registered successfully!";
			if (textCa == L"Error al registrar: ") resultat = L"Error while registering: ";
			if (textCa == L"Est\u00E0s segur que vols deixar de seguir la lliga?") resultat = L"Are you sure you want to unfollow the league?";
			if (textCa == L"Introdueix el nom de la lliga que vols seguir:") resultat = L"Enter the name of the league you want to follow:";
			if (textCa == L"Error: ") resultat = L"Error: ";
			if (textCa == L"Error BD") resultat = L"Database error";
			if (textCa == L"Contrasenya:") resultat = L"Password:";
			if (textCa == L"Esborrar") resultat = L"Delete";
			if (textCa == L"Esborrar equip de la lliga") resultat = L"Delete team from league";
			if (textCa == L"Selecciona l'equip:") resultat = L"Select the team:";
			if (textCa == L"Vols treure l'equip ") resultat = L"Do you want to remove team ";
			if (textCa == L" de la lliga?") resultat = L" from the league?";
			if (textCa == L"Equip tret de la lliga correctament.") resultat = L"Team removed from the league successfully.";
			if (textCa == L"No tens cap lliga activa associada.") resultat = L"You do not have any active league associated.";
			if (textCa == L"No hi ha equips dins de la teva lliga activa.") resultat = L"There are no teams in your active league.";
			if (textCa == L"Error carregant els equips: ") resultat = L"Error loading teams: ";
			if (textCa == L"Error en esborrar l'equip de la lliga: ") resultat = L"Error deleting the team from the league: ";
			if (textCa == L"Funcionalitat en desenvolupament.") resultat = L"Feature under development.";
			if (textCa == L"Lliga creada correctament!") resultat = L"League created successfully!";
			if (textCa == L"Error al crear lliga: ") resultat = L"Error creating league: ";
			if (textCa == L"Estàs segur que vols retirar la temporada activa respecte a la teva Lliga?") resultat = L"Are you sure you want to retire the active season from your league?";
			if (textCa == L"La temporada i les seves jornades han estat retirades correctament!") resultat = L"The season and its matchdays have been retired successfully!";
			if (textCa == L"Error al retirar la temporada: ") resultat = L"Error retiring season: ";
			if (textCa == L"Error") resultat = L"Error";
			if (textCa == L"OK") resultat = L"OK";
			if (textCa == L"PlayCampus") resultat = L"PlayCampus";
			if (textCa == L"Calendari") resultat = L"Calendar";
			if (textCa == L"Convocatòries") resultat = L"Call-ups";
			if (textCa == L"No hi ha fitxatges recents.") resultat = L"There are no recent signings.";
			if (textCa == L"No s'han pogut carregar els fitxatges.") resultat = L"The signings could not be loaded.";
			if (textCa == L"No estàs seguint cap lliga.") resultat = L"You are not following any league.";
			if (textCa == L"Error carregant el calendari: ") resultat = L"Error loading calendar: ";
			if (textCa == L"Aquesta lliga no existeix") resultat = L"This league does not exist";
			if (textCa == L"No hi ha dades per mostrar.") resultat = L"There is no data to display.";
			if (textCa == L"No hi ha partits pendents per gestionar convocatòries.") resultat = L"There are no pending matches to manage call-ups.";
			if (textCa == L"S'ha guardat la teva resposta correctament.") resultat = L"Your answer has been saved successfully.";
		}
		return resultat;
	}

	void Form1::AplicarIdioma() {
		// Aplica l'idioma seleccionat als textos principals de la interfície.
		if (this->lblIdioma != nullptr) this->lblIdioma->Text = Tr(L"Idioma:");
		if (this->btnShowLogin != nullptr) this->btnShowLogin->Text = Tr(L"Iniciar Sessió");
		if (this->btnShowRegister != nullptr) this->btnShowRegister->Text = Tr(L"Registrar-se");
		if (this->lblLoginTitle != nullptr) this->lblLoginTitle->Text = Tr(L"Iniciar Sessió");
		if (this->lblLoginUsuari != nullptr) this->lblLoginUsuari->Text = Tr(L"Correu");
		if (this->lblLoginPass != nullptr) this->lblLoginPass->Text = Tr(L"Contrasenya");
		if (this->btnLoginAct != nullptr) this->btnLoginAct->Text = Tr(L"Entrar");
		if (this->btnLoginBack != nullptr) this->btnLoginBack->Text = Tr(L"Registrar-se");
		if (this->lblRegTitle != nullptr) this->lblRegTitle->Text = Tr(L"Registrar-se");
		if (this->lblRegNom != nullptr) this->lblRegNom->Text = Tr(L"Nom");
		if (this->lblRegCorreu != nullptr) this->lblRegCorreu->Text = Tr(L"Correu");
		if (this->lblRegPass != nullptr) this->lblRegPass->Text = Tr(L"Contrasenya");
		if (this->lblRegTipus != nullptr) this->lblRegTipus->Text = Tr(L"Tipus");
		if (this->lblRegTelefon != nullptr) this->lblRegTelefon->Text = Tr(L"Telèfon");
		if (this->btnRegAct != nullptr) this->btnRegAct->Text = Tr(L"Registrar");
		if (this->btnRegBack != nullptr) this->btnRegBack->Text = Tr(L"Tornar");
		if (this->lblMainTitle != nullptr) this->lblMainTitle->Text = Tr(L"PlayCampus");
		if (this->btnProgPartits != nullptr) this->btnProgPartits->Text = Tr(L"Programació de partits");
		if (this->btnEstatLligues != nullptr) this->btnEstatLligues->Text = Tr(L"Estat de les Lligues");
		if (this->btnEstadistiques != nullptr) this->btnEstadistiques->Text = Tr(L"Estadístiques");
		if (this->btnConsultar != nullptr) this->btnConsultar->Text = Tr(L"Consultar calendari");
		if (this->btnMenuConsultarTelefons != nullptr) this->btnMenuConsultarTelefons->Text = Tr(L"Consultar telèfons");
		if (this->lblNoticies != nullptr) this->lblNoticies->Text = Tr(L"Últims fitxatges");
		if (this->btnLogoutMainMenu != nullptr) this->btnLogoutMainMenu->Text = Tr(L"Tancar Sessió");
		if (this->lblConsultarTitle != nullptr) this->lblConsultarTitle->Text = Tr(L"Consultar calendari");
		if (this->btnTornarConsultar != nullptr) this->btnTornarConsultar->Text = Tr(L"Tornar");
		if (this->lblAccesRapidCalendari != nullptr) this->lblAccesRapidCalendari->Text = Tr(L"Accés ràpid");
		if (this->lblNomLliga != nullptr) this->lblNomLliga->Text = Tr(L"Nom de la lliga");
		if (this->btnComprovarLliga != nullptr) this->btnComprovarLliga->Text = Tr(L"Veure calendari");
		if (this->lblCLTitle != nullptr) this->lblCLTitle->Text = Tr(L"Crear Nova Lliga");
		if (this->lblCLNom != nullptr) this->lblCLNom->Text = Tr(L"Nom de la Lliga:");
		if (this->lblCLPass != nullptr) this->lblCLPass->Text = Tr(L"Contrasenya:");
		if (this->lblCLEsport != nullptr) this->lblCLEsport->Text = Tr(L"Esport:");
		if (this->btnCLGuarda != nullptr) this->btnCLGuarda->Text = Tr(L"Crear");
		if (this->btnCLTornar != nullptr) this->btnCLTornar->Text = Tr(L"Tornar");
		if (this->lblGLTitle != nullptr) this->lblGLTitle->Text = Tr(L"Gestionar Lliga");
		if (this->btnGLAfegirPartit != nullptr) this->btnGLAfegirPartit->Text = Tr(L"Crear partit");
		if (this->btnGLEditarPartit != nullptr) this->btnGLEditarPartit->Text = Tr(L"Editar partit");
		if (this->btnGLMostrarEquips != nullptr) this->btnGLMostrarEquips->Text = Tr(L"Mostrar equips");
		if (this->btnGLEsborrarEquip != nullptr) this->btnGLEsborrarEquip->Text = Tr(L"Esborrar equip");
		if (this->btnGLCrearJornada != nullptr) this->btnGLCrearJornada->Text = Tr(L"Crear jornada");
		if (this->btnGLCrearTemporada != nullptr) this->btnGLCrearTemporada->Text = Tr(L"Crear temporada");
		if (this->btnGLRetirarTemporada != nullptr) this->btnGLRetirarTemporada->Text = Tr(L"Retirar temporada");
		if (this->btnGLConsultarTelefons != nullptr) this->btnGLConsultarTelefons->Text = Tr(L"Consultar telèfons");
		if (this->btnGLTornar != nullptr) this->btnGLTornar->Text = Tr(L"Tornar");
		if (this->lblEstTitle != nullptr) this->lblEstTitle->Text = Tr(L"Estadístiques");
		if (this->btnEstEquips != nullptr) this->btnEstEquips->Text = Tr(L"Estadístiques equips");
		if (this->btnEstTornar != nullptr) this->btnEstTornar->Text = Tr(L"Tornar");
		if (this->btnGLEsborrarPartit != nullptr) this->btnGLEsborrarPartit->Text = Tr(L"Esborrar partit");
		if (this->btnGLEsborrarJornada != nullptr) this->btnGLEsborrarJornada->Text = Tr(L"Esborrar jornada");
		if (this->lblCPTitle != nullptr) this->lblCPTitle->Text = Tr(L"Crear Partit");
		if (this->lblCPNomLliga != nullptr) this->lblCPNomLliga->Text = Tr(L"Nom Lliga:");
		if (this->btnCPValidarLliga != nullptr) this->btnCPValidarLliga->Text = Tr(L"Validar Lliga");
		if (this->lblCPTemporada != nullptr) this->lblCPTemporada->Text = Tr(L"Temporada:");
		if (this->lblCPJornada != nullptr) this->lblCPJornada->Text = Tr(L"Jornada:");
		if (this->lblCPData != nullptr) this->lblCPData->Text = Tr(L"Data del partit:");
		if (this->lblCPUbicacio != nullptr) this->lblCPUbicacio->Text = Tr(L"Ubicació:");
		if (this->lblCPEquipLocal != nullptr) this->lblCPEquipLocal->Text = Tr(L"Equip Local:");
		if (this->lblCPEquipVisitant != nullptr) this->lblCPEquipVisitant->Text = Tr(L"Equip Visitant:");
		if (this->btnCPConfirmar != nullptr) this->btnCPConfirmar->Text = Tr(L"Confirmar");
		if (this->btnCPCancellar != nullptr) this->btnCPCancellar->Text = Tr(L"Cancel·lar");
		if (this->lblCTTitle != nullptr) this->lblCTTitle->Text = Tr(L"Crear Temporada");
		if (this->lblCTNomLliga != nullptr) this->lblCTNomLliga->Text = Tr(L"Nom de la Lliga:");
		if (this->lblCTDataInici != nullptr) this->lblCTDataInici->Text = Tr(L"Data d'Inici:");
		if (this->lblCTDataFi != nullptr) this->lblCTDataFi->Text = Tr(L"Data de Fi:");
		if (this->btnCTConfirmar != nullptr) this->btnCTConfirmar->Text = Tr(L"Confirmar");
		if (this->btnCTCancellar != nullptr) this->btnCTCancellar->Text = Tr(L"Cancel·lar");
		if (this->lblCJTitle != nullptr) this->lblCJTitle->Text = Tr(L"Crear Jornada");
		if (this->lblCJNomLliga != nullptr) this->lblCJNomLliga->Text = Tr(L"Nom Lliga:");
		if (this->btnCJBuscarTemporades != nullptr) this->btnCJBuscarTemporades->Text = Tr(L"Cercar Temporades");
		if (this->lblCJTemporada != nullptr) this->lblCJTemporada->Text = Tr(L"Temporada:");
		if (this->lblCJNumero != nullptr) this->lblCJNumero->Text = Tr(L"Número Jornada:");
		if (this->lblCJDataInici != nullptr) this->lblCJDataInici->Text = Tr(L"Data d'Inici:");
		if (this->lblCJDataFi != nullptr) this->lblCJDataFi->Text = Tr(L"Data de Fi:");
		if (this->btnCJConfirmar != nullptr) this->btnCJConfirmar->Text = Tr(L"Confirmar");
		if (this->btnCJCancellar != nullptr) this->btnCJCancellar->Text = Tr(L"Cancel·lar");
		if (this->lblEETitle != nullptr) this->lblEETitle->Text = Tr(L"Enregistrar Equip");
		if (this->lblEENom != nullptr) this->lblEENom->Text = Tr(L"Nom de l'Equip:");
		if (this->lblEEData != nullptr) this->lblEEData->Text = Tr(L"Data Fundació:");
		if (this->lblEEEscollirEsport != nullptr) this->lblEEEscollirEsport->Text = Tr(L"Esport:");
		if (this->btnEEEnregistrar != nullptr) this->btnEEEnregistrar->Text = Tr(L"Enregistrar");
		if (this->btnEETornar != nullptr) this->btnEETornar->Text = Tr(L"Tornar");
		if (this->lblGETitle != nullptr) this->lblGETitle->Text = Tr(L"Gestionar Equip");
		if (this->btnGEEsborrarEquip != nullptr) this->btnGEEsborrarEquip->Text = Tr(L"Esborrar equip");
		if (this->btnGEAfegirJugador != nullptr) this->btnGEAfegirJugador->Text = Tr(L"Afegir jugador");
		if (this->btnGEEliminarJugador != nullptr) this->btnGEEliminarJugador->Text = Tr(L"Eliminar jugador");
		if (this->btnGEConvocarJugador != nullptr) this->btnGEConvocarJugador->Text = Tr(L"Convocar jugador");
		if (this->btnGEEditarJugador != nullptr) this->btnGEEditarJugador->Text = Tr(L"Editar Jugador");
		if (this->btnGEConsultarTelefons != nullptr) this->btnGEConsultarTelefons->Text = Tr(L"Consultar telèfons");
		if (this->btnGETornar != nullptr) this->btnGETornar->Text = Tr(L"Tornar");
		if (this->lblAJTitle != nullptr) this->lblAJTitle->Text = Tr(L"Afegir Jugador");
		if (this->lblAJCorreu != nullptr) this->lblAJCorreu->Text = Tr(L"Correu Estudiant:");
		if (this->lblAJDorsal != nullptr) this->lblAJDorsal->Text = Tr(L"Dorsal:");
		if (this->lblAJPosicio != nullptr) this->lblAJPosicio->Text = Tr(L"Posició (Opcional):");
		if (this->lblAJDataNaixement != nullptr) this->lblAJDataNaixement->Text = Tr(L"Data Naixement:");
		if (this->btnAJConfirmar != nullptr) this->btnAJConfirmar->Text = Tr(L"Confirmar");
		if (this->btnAJCancellar != nullptr) this->btnAJCancellar->Text = Tr(L"Cancel·lar");
		if (this->lblUELTitle != nullptr) this->lblUELTitle->Text = Tr(L"Unir Equip a Lliga");
		if (this->lblUELNom != nullptr) this->lblUELNom->Text = Tr(L"Nom de la Lliga:");
		if (this->btnUELComprovar != nullptr) this->btnUELComprovar->Text = Tr(L"Comprovar");
		if (this->lblUELPass != nullptr) this->lblUELPass->Text = Tr(L"Contrasenya:");
		if (this->btnUELUnir != nullptr) this->btnUELUnir->Text = Tr(L"Unir");
		if (this->btnUELTornar != nullptr) this->btnUELTornar->Text = Tr(L"Tornar");
		if (this->lblEPTitle != nullptr) this->lblEPTitle->Text = Tr(L"Esborrar Partit - Selecció");
		if (this->btnEPTornar != nullptr) this->btnEPTornar->Text = Tr(L"Tornar");
		if (this->lblEPTemporada != nullptr) this->lblEPTemporada->Text = Tr(L"Tria una Temporada:");
		if (this->lblEPJornada != nullptr) this->lblEPJornada->Text = Tr(L"Tria una Jornada:");
		if (this->lblEPPartit != nullptr) this->lblEPPartit->Text = Tr(L"Tria el Partit a esborrar:");
		if (this->btnEPEsborrarFinal != nullptr) this->btnEPEsborrarFinal->Text = Tr(L"Esborrar Partit Seleccionat");
		if (this->lblEJTitle != nullptr) this->lblEJTitle->Text = Tr(L"Esborrar Jornada - Selecció");
		if (this->btnEJTornar != nullptr) this->btnEJTornar->Text = Tr(L"Tornar");
		if (this->lblEJTemporada != nullptr) this->lblEJTemporada->Text = Tr(L"Tria una Temporada:");
		if (this->lblEJJornada != nullptr) this->lblEJJornada->Text = Tr(L"Tria la Jornada a esborrar:");
		if (this->btnEJEsborrarFinal != nullptr) this->btnEJEsborrarFinal->Text = Tr(L"Esborrar Jornada");
		if (this->lblEstEquipTitle != nullptr) this->lblEstEquipTitle->Text = Tr(L"Estadístiques d'equip");
		if (this->lblEstEquipBuscar != nullptr) this->lblEstEquipBuscar->Text = Tr(L"Nom de l'equip:");
		if (this->btnEstEquipCercar != nullptr) this->btnEstEquipCercar->Text = Tr(L"Cercar");
		if (this->lblEstEquipLliga != nullptr) this->lblEstEquipLliga->Text = Tr(L"Lliga:");
		if (this->lblEstEquipTemporada != nullptr) this->lblEstEquipTemporada->Text = Tr(L"Temporada:");
		if (this->btnEstEquipTornar != nullptr) this->btnEstEquipTornar->Text = Tr(L"Tornar");
		if (this->btnEstLliga != nullptr) this->btnEstLliga->Text = Tr(L"Estadístiques Lliga");
		if (this->lblEstLligaBuscar != nullptr) this->lblEstLligaBuscar->Text = Tr(L"Cercar lliga:");
		if (this->btnEstLligaExecutarCerca != nullptr) this->btnEstLligaExecutarCerca->Text = Tr(L"Cercar");
		if (this->lblEstLligaSeleccionar != nullptr) this->lblEstLligaSeleccionar->Text = Tr(L"Selecciona una lliga:");
		if (this->lblEstLligaTemporada != nullptr) this->lblEstLligaTemporada->Text = Tr(L"Temporada:");
		if (this->btnEstLligaTornar != nullptr) this->btnEstLligaTornar->Text = Tr(L"<- Tornar");
		if (this->lblEditarPartitTitle != nullptr) this->lblEditarPartitTitle->Text = Tr(L"Editar Partit i Estadístiques");
		if (this->lblPartitsAEditar != nullptr) this->lblPartitsAEditar->Text = Tr(L"Selecciona un partit:");
		if (this->lblResultatLocal != nullptr) this->lblResultatLocal->Text = Tr(L"Marcador local:");
		if (this->lblResultatVisitant != nullptr) this->lblResultatVisitant->Text = Tr(L"Marcador visitant:");
		if (this->lblEstatPartit != nullptr) this->lblEstatPartit->Text = Tr(L"Estat:");
		if (this->lblDataPartit != nullptr) this->lblDataPartit->Text = Tr(L"Nova data:");
		if (this->btnGuardarEstadistiques != nullptr) this->btnGuardarEstadistiques->Text = Tr(L"Guardar Canvis");
		if (this->btnTornarEditarPartit != nullptr) this->btnTornarEditarPartit->Text = Tr(L"Tornar");
		if (this->btnGestionarConvocatoria != nullptr) this->btnGestionarConvocatoria->Text = Tr(L"Gestionar Convocatòries");
		if (this->btnTornarConvocatoria != nullptr) this->btnTornarConvocatoria->Text = Tr(L"Tornar");
		if (this->lblConvocatoriaInfo != nullptr) this->lblConvocatoriaInfo->Text = Tr(L"Selecciona un partit i fes clic a un jugador per canviar-ne l'estat.");
		if (this->btnEstPartit != nullptr) this->btnEstPartit->Text = Tr(L"Estadístiques Partit");
		if (this->btnEstPartitTornar != nullptr) this->btnEstPartitTornar->Text = Tr(L"Tornar");
		if (this->lblEstPartitTitle != nullptr) this->lblEstPartitTitle->Text = Tr(L"ESTADÍSTIQUES DE PARTIT");
		if (this->lblEstPartitLliga != nullptr) this->lblEstPartitLliga->Text = Tr(L"Selecciona Lliga:");
		if (this->lblEstPartitTemporada != nullptr) this->lblEstPartitTemporada->Text = Tr(L"Selecciona Temporada:");
		if (this->lblEstPartitBuscar != nullptr) this->lblEstPartitBuscar->Text = Tr(L"Cercar partit:");
		if (this->btnEstPartitCercar != nullptr) this->btnEstPartitCercar->Text = Tr(L"Cercar");
		if (this->btnEstPartitNetejar != nullptr) this->btnEstPartitNetejar->Text = Tr(L"Netejar");
		if (this->lblEstPartitPartits != nullptr) this->lblEstPartitPartits->Text = Tr(L"Selecciona Partit:");
		if (this->btnEstJugadors != nullptr) this->btnEstJugadors->Text = Tr(L"Estadístiques Jugadors");
		if (this->lblDashboardClassificacio != nullptr) this->lblDashboardClassificacio->Text = Tr(L"Classificació");
		if (this->lblDashboardProximsPartits != nullptr) this->lblDashboardProximsPartits->Text = Tr(L"Pròxims partits");
		if (this->lblDashboardUltimsResultats != nullptr) this->lblDashboardUltimsResultats->Text = Tr(L"Últims resultats");

		if (this->btnCrearLligaMainMenu != nullptr) {
			System::String^ textBase = this->btnCrearLligaMainMenu->Tag == nullptr ? L"Crear Lliga" : System::Convert::ToString(this->btnCrearLligaMainMenu->Tag);
			this->btnCrearLligaMainMenu->Text = Tr(textBase);
		}
		if (this->btnEnregistrarEquip != nullptr) {
			System::String^ textBase = this->btnEnregistrarEquip->Tag == nullptr ? L"Enregistrar Equip" : System::Convert::ToString(this->btnEnregistrarEquip->Tag);
			this->btnEnregistrarEquip->Text = Tr(textBase);
		}
		if (this->btnUnirEquipLliga != nullptr) {
			System::String^ textBase = this->btnUnirEquipLliga->Tag == nullptr ? L"Unir equip a lliga" : System::Convert::ToString(this->btnUnirEquipLliga->Tag);
			this->btnUnirEquipLliga->Text = Tr(textBase);
		}
		if (this->btnSeguirLligaMainMenu != nullptr) {
			System::String^ textBase = this->btnSeguirLligaMainMenu->Tag == nullptr ? L"Seguir Lliga" : System::Convert::ToString(this->btnSeguirLligaMainMenu->Tag);
			this->btnSeguirLligaMainMenu->Text = Tr(textBase);
		}
		if (this->btnCalendariLligaSeguida != nullptr && this->btnCalendariLligaSeguida->Tag != nullptr) {
			System::String^ textBase = System::Convert::ToString(this->btnCalendariLligaSeguida->Tag);
			if (textBase->StartsWith(L"Calendari: ")) {
				this->btnCalendariLligaSeguida->Text = Tr(L"Calendari: ") + textBase->Substring(11);
			}
			else {
				this->btnCalendariLligaSeguida->Text = Tr(textBase);
			}
		}
	}

	System::Void Form1::cmbIdioma_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// Canvia l'idioma de la interfície quan l'usuari selecciona una opció.
		AplicarIdioma();
		Form1_Resize(nullptr, nullptr);
	}

}
