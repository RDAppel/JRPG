#include "Editor.h"


Editor::Editor()
{
	SetScreenSize(Vector2(1280, 720));
	SetWindowTitle("JRPG Editor");
	SetDisplayResizable(true);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
}

Editor::~Editor()
{
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
}

void Editor::InitializeDisplay()
{
	Game::InitializeDisplay();

	ImGui_ImplAllegro5_Init(m_pDisplay);
}


void Editor::HandleEvent(ALLEGRO_EVENT& event)
{
	ImGui_ImplAllegro5_ProcessEvent(&event);

	if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
	{
		ImGui_ImplAllegro5_InvalidateDeviceObjects();
		al_acknowledge_resize(m_pDisplay);
		ImGui_ImplAllegro5_CreateDeviceObjects();
	}
}

void Editor::Update(const GameTime& gameTime)
{
	Game::Update(gameTime);

	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();

	static bool s_isDemoVisible = false;
	if (s_isDemoVisible) ImGui::ShowDemoWindow(&s_isDemoVisible);


	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File##MenuItem"))
	{
		if (ImGui::MenuItem("New Project...##MenuItem", "Ctrl+N", nullptr, false)) {}
		if (ImGui::MenuItem("Open Project...##MenuItem", "Ctrl+O", nullptr, false)) {}
		if (ImGui::MenuItem("Close Project##MenuItem", nullptr, nullptr, false)) {}
		ImGui::Separator();
		if (ImGui::MenuItem("Exit##MenuItem", "Alt+F4")) Quit();

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit##MenuItem"))
	{
		if (ImGui::MenuItem("Undo##MenuItem", nullptr, nullptr, false)) {}
		if (ImGui::MenuItem("Redo##MenuItem", nullptr, nullptr, false)) {}
		ImGui::Separator();
		if (ImGui::MenuItem("Cut##MenuItem", nullptr, nullptr, false)) {}
		if (ImGui::MenuItem("Copy##MenuItem", nullptr, nullptr, false)) {}
		if (ImGui::MenuItem("Paste##MenuItem", nullptr, nullptr, false)) {}

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View##MenuItem"))
	{
		if (ImGui::MenuItem("Demo##MenuItem", "Alt+D")) s_isDemoVisible = true;

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();



	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

	al_flip_display();
	al_clear_to_color(GetClearColor().GetAllegroColor());
}
