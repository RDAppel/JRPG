
#include "Editor.h"
#include "ExterntalExe.h"
#include "TexturesWindow.h"

Editor::Editor()
{
	SetWindowTitle("JRPG Editor");
	SetDisplayResizable();
	SetUseImGui();

	m_windows["TexturesWindow"] = new TexturesWindow;

}

Editor::~Editor()
{
	if (m_pGameHandle) ExternalExe::Close(m_pGameHandle);
}

void Editor::LoadContent(ResourceManager& resourceManager)
{
	m_windows["TexturesWindow"]->LoadContent(resourceManager);
}

void Editor::Update(const GameTime& gameTime)
{
	Game::Update(gameTime);

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
	if (ImGui::BeginMenu("Run##MenuItem"))
	{
		if (ImGui::MenuItem("Game##MenuItem", "F5"))
		{
			if (m_pGameHandle) ExternalExe::Close(m_pGameHandle);
			m_pGameHandle = ExternalExe::Run(L"JRPG.exe", L"C:\\Users\\Ryan\\Desktop\\JRPG\\Debug");
		}

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	//dockspace
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus;

	ImGui::Begin("DockSpace", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceID = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	ImGui::End();

	m_windows["TexturesWindow"]->Update(gameTime);
}

void Editor::Draw(SpriteBatch& spriteBatch)
{
	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
}