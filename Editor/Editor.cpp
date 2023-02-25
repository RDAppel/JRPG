
#include <Windows.h>

#include "Editor.h"


bool StartProcess(const std::wstring fileName, const std::wstring path,
	const std::wstring parameters = L"")
{
	DWORD exitCode = 0;
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = L"open";
	ShExecInfo.lpFile = fileName.c_str();
	ShExecInfo.lpParameters = parameters.c_str();
	ShExecInfo.lpDirectory = path.c_str();
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);

	if (!ShExecInfo.hProcess) return false;

	if (WaitForSingleObject(ShExecInfo.hProcess, INFINITE) == 0)
	{
		GetExitCodeProcess(ShExecInfo.hProcess, &exitCode);
		if (exitCode != 0) return false;
		else return true;
	}
	else return false;
}

Editor::Editor()
{
	Game::SetScreenSize(1280, 720);
	SetWindowTitle("JRPG Editor");
	SetDisplayFrameRate(false);
	SetDisplayResizable();
}

Editor::~Editor()
{
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
}

void Editor::InitializeDisplay()
{
	Game::InitializeDisplay();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;        // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplAllegro5_Init(GetDisplay());

	al_init_primitives_addon();
}

void Editor::Update()
{
	Game::Update();

	// Start the ImGui frame
	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	if (m_isDemoVisible) ImGui::ShowDemoWindow(&m_isDemoVisible);


	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("New Project", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
		ImGui::Separator();
		//ImGui::Text("Project Name:");
		//ImGui::InputText("Name: ", nullptr, 0, 0, 0);
		ImGui::EndPopup();
	}

	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Project..."))
		{
			ImGui::OpenPopup("New Project");
		}

		//ImGui::MenuItem("Open Project");
		ImGui::Separator();
		if (ImGui::MenuItem("Exit")) Quit();

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("test1");
		ImGui::MenuItem("test2");

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("ImGui Demo")) m_isDemoVisible = true;
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Run"))
	{
		if (ImGui::MenuItem("Run with Current Settings"))
		{
			StartProcess(L"JRPG.exe", L"C:\\Users\\Ryan\\Desktop\\JRPG\\Debug");
		}
		ImGui::MenuItem("Edit Run Settings");

		ImGui::EndMenu();
	}

	if (ImGui::ArrowButton("RunArrow", ImGuiDir_Right))
	{
		StartProcess(L"JRPG.exe", L"C:\\Users\\Ryan\\Desktop\\JRPG\\Debug");
	}

	ImGui::EndMainMenuBar();

	// create our own dockspace on the main window
	bool open = true;
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking
		| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::Begin("DockSpace", &open, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}



	ImGui::End();


	// example window
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Text("This is some useful text.");

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	if (ImGui::Button("Button")) counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	

	// Maps window
	ImVec2 size = io.DisplaySize;

	ImGui::Begin("Maps", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::GetStyle().WindowRounding = 0.0f;

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_FittingPolicyScroll
		| ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_TabListPopupButton;
	ImGui::BeginTabBar("MapsTabBar", tab_bar_flags);


	ImGui::EndTabBar();
	ImGui::End();


	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

	ImVec4 c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
	SetClearColor(Color(c.x, c.y, c.x, c.w));

	al_flip_display();
	al_clear_to_color(GetClearColor().GetAllegroColor());
}

void Editor::Resize()
{
	ImGui_ImplAllegro5_InvalidateDeviceObjects();
	Game::Resize();
	ImGui_ImplAllegro5_CreateDeviceObjects();
}


void Editor::HandleEvent(ALLEGRO_EVENT& event)
{
	ImGui_ImplAllegro5_ProcessEvent(&event);
}
