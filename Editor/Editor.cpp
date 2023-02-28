
#include "Editor.h"
#include "ExterntalExe.h"

Editor::Editor()
{
	SetWindowTitle("JRPG Editor");
	SetDisplayResizable();
	SetUseImGui();
}

Editor::~Editor()
{
	if (m_pGameHandle) ExternalExe::Close(m_pGameHandle);
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
	if (ImGui::BeginMenu("Run##MenuItem"))
	{
		if (ImGui::MenuItem("Game##MenuItem", "F5", nullptr, !m_pGameHandle))
		{
			m_pGameHandle = ExternalExe::Run(L"JRPG.exe", L"C:\\Users\\Ryan\\Desktop\\JRPG\\Debug");
		}

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	ForceRedraw();
}

void Editor::Draw(SpriteBatch& spriteBatch)
{
	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
}