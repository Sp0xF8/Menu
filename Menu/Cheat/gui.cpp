#include "gui.h"
#include "Config.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx9.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imguipp.h"



Config config;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
		return true;

	switch (message)
	{
		case WM_SIZE: {
			if (gui::device && wParam != SIZE_MINIMIZED)
			{
				gui::presentParameters.BackBufferWidth = LOWORD(lParam);
				gui::presentParameters.BackBufferHeight = HIWORD(lParam);
				gui::ResetDevice();
			}
		} return 0;
		
		case WM_SYSCOMMAND: {
			if ((wParam & 0xfff0) == SC_KEYMENU)
				return 0;
		} break;
			

		case WM_DESTROY: {
			PostQuitMessage(0);
		} return 0;
			
		case WM_LBUTTONDOWN: {
			gui::position = MAKEPOINTS(lParam);
		} return 0;
		
		case WM_MOUSEMOVE: {
			if (wParam == MK_LBUTTON)
			{
				const auto points = MAKEPOINTS(lParam);
				auto rect = ::RECT{};

				GetWindowRect(gui::window, &rect);

				rect.left += points.x - gui::position.x;
				rect.top += points.y - gui::position.y;

				if (gui::position.x >= 0 &&
					gui::position.x <= gui::WIDTH &&
					gui::position.y >= 0 && gui::position.y <= 19)
					SetWindowPos(
						gui::window,
						HWND_TOPMOST,
						rect.left,
						rect.top,
						0, 0,
						SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
					);
			}
		} return 0;

			
	}
	
	
	return DefWindowProcW(window, message, wParam, lParam);
}


void gui::CreateHWindow(
	const char* windowName,
	const char* className) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = 0;

	RegisterClassExA(&windowClass);
	
	window = CreateWindowA(
		className,
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);


	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
	
	
}



void gui::DestroyHWindow() noexcept
{
	
	DestroyWindow(window);
	UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
	
	
}


bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
		return false;
	
	ZeroMemory(&presentParameters, sizeof(presentParameters));
	
	presentParameters.Windowed = true;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = true;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) <0 )
		return false;
	
	return true;
	
}


void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	
	const auto result = device->Reset(&presentParameters);
	
	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
	
}


void gui::DestroyDevice() noexcept
{

	if (device)
	{
		device->Release();
		device = nullptr;
	}
	
	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}


void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();
	io.IniFilename = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
	
}


void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}


void gui::EndRender() noexcept
{
	
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();

	}

	const auto result = device->Present(0, 0, 0, 0);

	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();

}


void gui::Theme() noexcept
{
	ImGuiStyle* style = &ImGui::GetStyle();
	
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	
	style->WindowMinSize = ImVec2(WIDTH, HEIGHT);

	style->FramePadding = ImVec2(8, 6);

	
	
	style->Colors[ImGuiCol_TitleBg] = ImColor(config.Settings.Cfg.titleBg.r, config.Settings.Cfg.titleBg.g, config.Settings.Cfg.titleBg.b, config.Settings.Cfg.titleBg.a);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(config.Settings.Cfg.titleBgActive.r, config.Settings.Cfg.titleBgActive.g, config.Settings.Cfg.titleBgActive.b, config.Settings.Cfg.titleBgActive.a);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(config.Settings.Cfg.titleBgCollapsed.r, config.Settings.Cfg.titleBgCollapsed.g, config.Settings.Cfg.titleBgCollapsed.b, config.Settings.Cfg.titleBgCollapsed.a);

	style->Colors[ImGuiCol_Button] = ImColor(config.Settings.Cfg.button.r, config.Settings.Cfg.button.g, config.Settings.Cfg.button.b, config.Settings.Cfg.button.a);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(config.Settings.Cfg.buttonHovered.r, config.Settings.Cfg.buttonHovered.g, config.Settings.Cfg.buttonHovered.b, config.Settings.Cfg.buttonHovered.a);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(config.Settings.Cfg.buttonActive.r, config.Settings.Cfg.buttonActive.g, config.Settings.Cfg.buttonActive.b, config.Settings.Cfg.buttonActive.a);
	
	style->Colors[ImGuiCol_Separator] = ImColor(config.Settings.Cfg.separator.r, config.Settings.Cfg.separator.g, config.Settings.Cfg.separator.b, config.Settings.Cfg.separator.a);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(config.Settings.Cfg.separatorHovered.r, config.Settings.Cfg.separatorHovered.g, config.Settings.Cfg.separatorHovered.b, config.Settings.Cfg.separatorHovered.a);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(config.Settings.Cfg.separatorActive.r, config.Settings.Cfg.separatorActive.g, config.Settings.Cfg.separatorActive.b, config.Settings.Cfg.separatorActive.a);
	
	
}

void gui::Menu() noexcept
{
	ImGuiIO& io = ::ImGui::GetIO();
	ImFont* mainFont = io.Fonts->AddFontFromFileTTF("../Fonts/Oswald-Medium.ttf", 15, NULL, io.Fonts->GetGlyphRangesJapanese());
	IM_ASSERT(mainFont != NULL);

	ImGui::BeginChild("##Top", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 70), TRUE);
	{
		switch (config.Tab) {
		case 1:
			//Legit Bot
			ImGui::Checkbox("Active", &config.Settings.Legit.enabled);

			if (config.Settings.Legit.enabled == true)
				ImGui::Text("Legit Bot Enabled");
			else
				ImGui::Text("Legit Bot Disabled");

			break;

		case 2:
			//RageBot
			ImGui::Text("RageBot");
			break;
		case 3:
			//Visuals
			ImGui::Text("Visuals");
			break;
		case 4:
			//Misc
			ImGui::Text("Visuals");
			break;
		case 5:
			//Skins
			ImGui::Text("Visuals");
			break;
		case 6:
			//Settings
			
			break;
		default:
			ImGui::Text("ERR: R001");
		}
		

	}
	ImGui::EndChild();


	ImGui::BeginChild("##Bottom", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), TRUE);
	{
		static ImVec4 active = imguipp::to_vec4(config.Settings.Cfg.buttonActive.r, config.Settings.Cfg.buttonActive.g, config.Settings.Cfg.buttonActive.b, config.Settings.Cfg.buttonActive.a);
		static ImVec4 inactive = imguipp::to_vec4(config.Settings.Cfg.button.r, config.Settings.Cfg.button.g, config.Settings.Cfg.button.b, config.Settings.Cfg.button.a);
		ImGui::Columns(1);
		

		{
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 1 ? active : inactive);
			if (ImGui::Button(" Legit ", ImVec2(153 - 15, 50)))
				config.Tab = 1; ImGui::SameLine();
		
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 2 ? active : inactive);
			if (ImGui::Button(" Rage ", ImVec2(153 - 15, 50)))
				config.Tab = 2; ImGui::SameLine();
		
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 3 ? active : inactive);
			if (ImGui::Button(" Visuals ", ImVec2(153 - 15, 50)))
				config.Tab = 3; ImGui::SameLine();
		
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 4 ? active : inactive);
			if (ImGui::Button(" Misc ", ImVec2(153 - 15, 50)))
				config.Tab = 4; ImGui::SameLine();
		
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 5 ? active : inactive);
			if (ImGui::Button(" Skins ", ImVec2(153 - 15, 50)))
				config.Tab = 5; ImGui::SameLine();
		
			ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 6 ? active : inactive);
			if (ImGui::Button(" Settings ", ImVec2(153 - 15, 50)))
				config.Tab = 6; 
		}
		ImGui::PopStyleColor(1);
	}
	ImGui::EndChild();

	/*
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);
	
	{
		//left
		static ImVec4 active = imguipp::to_vec4(config.Settings.Cfg.buttonActive.r, config.Settings.Cfg.buttonActive.g, config.Settings.Cfg.buttonActive.b, config.Settings.Cfg.buttonActive.a);
		static ImVec4 inactive = imguipp::to_vec4(config.Settings.Cfg.button.r, config.Settings.Cfg.button.g, config.Settings.Cfg.button.b, config.Settings.Cfg.button.a);
		
		ImGui::PushFont(mainFont);
		
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 1 ? active : inactive);
		if (ImGui::Button(" Legit ", ImVec2(230 - 15, 40)))
			config.Tab = 1;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 2 ? active : inactive);
		if (ImGui::Button(" Rage ", ImVec2(230 - 15, 40)))
			config.Tab = 2;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 3 ? active : inactive);
		if (ImGui::Button(" Visuals ", ImVec2(230 - 15, 40)))
			config.Tab = 3;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 4 ? active : inactive);
		if (ImGui::Button(" Misc ", ImVec2(230 - 15, 40)))
			config.Tab = 4;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 5 ? active : inactive);
		if (ImGui::Button(" Skin ", ImVec2(230 - 15, 40)))
			config.Tab = 5;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, config.Tab == 6 ? active : inactive);
		if (ImGui::Button(" Settings ", ImVec2(230 - 15, 40)))
			config.Tab = 6;

		ImGui::Spacing();
		ImGui::Spacing();
		
		ImGui::PopStyleColor(6);
		
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		imguipp::center_text_ex("Version 0.0.1", 230, 1, false);

		ImGui::PopFont();
	}

	ImGui::NextColumn();;
	
	{

		//right

		switch (config.Tab) {
		case 1:
			//Legit Bot
			break;
		}
	}
	*/



}



void gui::Render() noexcept
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	
	ImGui::Begin(
		"Re-ReVoid",
		0,
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoDecoration
		
	);
	{
		gui::Menu();
	}

	ImGui::End();
}




