#include "gui.h"
#include "Config.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx9.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imguipp.h"

ImFont* font1;


ImColor float4toImColorRead(float input[4]) {
	return ImColor(input[0], input[1], input[2], input[3]);
}

ImVec4 float4toImVec4Read(float input[4]) {
	return ImVec4(input[0], input[1], input[2], input[3]);
}


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

	
	
	style->Colors[ImGuiCol_TitleBg] = float4toImColorRead(Config::Settings.Cfg.titleBg);
	style->Colors[ImGuiCol_TitleBgActive] = float4toImColorRead(Config::Settings.Cfg.titleBgActive);
	style->Colors[ImGuiCol_TitleBgCollapsed] = float4toImColorRead(Config::Settings.Cfg.titleBgCollapsed);

	style->Colors[ImGuiCol_Button] = float4toImColorRead(Config::Settings.Cfg.button);
	style->Colors[ImGuiCol_ButtonHovered] = float4toImColorRead(Config::Settings.Cfg.buttonHovered);
	style->Colors[ImGuiCol_ButtonActive] = float4toImColorRead(Config::Settings.Cfg.buttonActive);
	
	style->Colors[ImGuiCol_Separator] = float4toImColorRead(Config::Settings.Cfg.separator);
	style->Colors[ImGuiCol_SeparatorHovered] = float4toImColorRead(Config::Settings.Cfg.separatorHovered);
	style->Colors[ImGuiCol_SeparatorActive] = float4toImColorRead(Config::Settings.Cfg.separatorActive);

	style->Colors[ImGuiCol_Text] = float4toImColorRead(Config::Settings.Cfg.textCol1);
	style->Colors[ImGuiCol_ChildBg] = float4toImColorRead(Config::Settings.Cfg.childBg);
	style->Colors[ImGuiCol_WindowBg] = float4toImColorRead(Config::Settings.Cfg.windowBg);
	style->Colors[ImGuiCol_Border] = float4toImColorRead(Config::Settings.Cfg.borderBg);
	style->Colors[ImGuiCol_FrameBg] = float4toImColorRead(Config::Settings.Cfg.frameBg);

	style->Colors[ImGuiCol_CheckMark] = float4toImColorRead(Config::Settings.Cfg.checkMark);

	style->Colors[ImGuiCol_SliderGrab] = float4toImColorRead(Config::Settings.Cfg.sliderGrab);
	style->Colors[ImGuiCol_SliderGrabActive] = float4toImColorRead(Config::Settings.Cfg.sliderGrabActive);

	style->Colors[ImGuiCol_ScrollbarBg] = float4toImColorRead(Config::Settings.Cfg.scrollBar);
	style->Colors[ImGuiCol_ScrollbarGrab] = float4toImColorRead(Config::Settings.Cfg.scrollBarGrab);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = float4toImColorRead(Config::Settings.Cfg.scrollBarHovered);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = float4toImColorRead(Config::Settings.Cfg.scrollBarActive);
	
}

void gui::Menu() noexcept
{
	
	ImGuiIO& io = ImGui::GetIO();

	ImGui::BeginChild("##Top", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 70), TRUE);
	{
		switch (Config::Tab) {
		case 1:
			//Legit Bot
			ImGui::Checkbox("Active", &Config::Settings.Legit.enabled);

			if (Config::Settings.Legit.enabled == true)
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
			ImGui::BeginChild("Misc", ImVec2(200, ImGui::GetContentRegionAvail().y), TRUE);
			{
				imguipp::center_text_ex("Player Functions", 200, 1, false);
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

				ImGui::Checkbox("Legit BHop", &Config::Settings.Misc.legitBhop);
				ImGui::Checkbox("Rage BHop", &Config::Settings.Misc.bhop);
				ImGui::Checkbox("Auto Strafe", &Config::Settings.Misc.autoStrafe);
				ImGui::Checkbox("Auto Accept", &Config::Settings.Misc.autoAccept);
				ImGui::Checkbox("Auto Block", &Config::Settings.Misc.autoBlock);
				ImGui::Checkbox("ReVoid Tag", &Config::Settings.Misc.reVoidTag);
				{
					Config::Settings.Misc.customTag == true ? Config::Settings.Misc.reVoidTag = false : NULL;
				}
				ImGui::Checkbox("Custom Tag", &Config::Settings.Misc.customTag);
				{
					Config::Settings.Misc.reVoidTag == true ? Config::Settings.Misc.customTag = false : NULL;
				}

				ImGui::InputTextWithHint("","10 Char", Config::Settings.Misc.customTagText, 11, 0, 0);


				ImGui::Text(Config::Settings.Misc.customTagText);
			}
			ImGui::EndChild();
			break;
		case 5:
			//Skins
			ImGui::Text("Visuals");
			break;
		case 6:
			//Settings
			ImGui::BeginChild("Colours", ImVec2(200, ImGui::GetContentRegionAvail().y), TRUE);
			{

				//Menu Colours
				imguipp::center_text_ex("Menu Colours", 200, 1, false);
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
				
				ImGui::ColorEdit4("Button", (float*)&Config::Settings.Cfg.button, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Button Active", (float*)&Config::Settings.Cfg.buttonActive, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Button Hover", (float*)&Config::Settings.Cfg.buttonHovered, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Separator", (float*)&Config::Settings.Cfg.separator, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				//ImGui::ColorEdit4("Separator Hover", (float*)&Config::Settings.Cfg.separatorHovered, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				//ImGui::ColorEdit4("Separator Active", (float*)&Config::Settings.Cfg.separatorActive, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				
				//ImGui::ColorEdit4("Title Background", (float*)&Config::Settings.Cfg.titleBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				//ImGui::ColorEdit4("Title Bg Active", (float*)&Config::Settings.Cfg.titleBgActive, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		
				ImGui::ColorEdit4("Window", (float*)&Config::Settings.Cfg.windowBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Child", (float*)&Config::Settings.Cfg.childBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Border", (float*)&Config::Settings.Cfg.borderBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Check Mark", (float*)&Config::Settings.Cfg.checkMark, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Slider", (float*)&Config::Settings.Cfg.sliderGrab, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Slider Active", (float*)&Config::Settings.Cfg.sliderGrabActive, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Frame Background", (float*)&Config::Settings.Cfg.frameBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Scrollbar", (float*)&Config::Settings.Cfg.scrollBar, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Scrollbar Grab", (float*)&Config::Settings.Cfg.scrollBarGrab, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Scrollbar Hover", (float*)&Config::Settings.Cfg.scrollBarHovered, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("Scrollbar Active", (float*)&Config::Settings.Cfg.scrollBarActive, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

				ImGui::ColorEdit4("Text Colour", (float*)&Config::Settings.Cfg.textCol1, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			}
			ImGui::EndChild();
			
			break;
		default:
			ImGui::Text("ERR: R001");
		}
		

	}
	ImGui::EndChild();

	

	ImGui::BeginChild("##Bottom", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), TRUE);
	{
		ImVec4 active = imguipp::to_vec4(Config::Settings.Cfg.buttonActive[0] * 255, Config::Settings.Cfg.buttonActive[1] * 255, Config::Settings.Cfg.buttonActive[2] * 255, Config::Settings.Cfg.buttonActive[3] * 255);
		ImVec4 inactive = imguipp::to_vec4(Config::Settings.Cfg.button[0] * 255, Config::Settings.Cfg.button[1] * 255, Config::Settings.Cfg.button[2] * 255, Config::Settings.Cfg.button[3] * 255);
		ImGui::Columns(1);
		

		{

			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 1 ? active : inactive);
			if (ImGui::Button(" Legit ", ImVec2(153 - 15, 50)))
				Config::Tab = 1; ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 2 ? active : inactive);
			if (ImGui::Button(" Rage ", ImVec2(153 - 15, 50)))
				Config::Tab = 2; ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 3 ? active : inactive);
			if (ImGui::Button(" Visuals ", ImVec2(153 - 15, 50)))
				Config::Tab = 3; ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 4 ? active : inactive);
			if (ImGui::Button(" Misc ", ImVec2(153 - 15, 50)))
				Config::Tab = 4; ImGui::SameLine();
			
			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 5 ? active : inactive);
			if (ImGui::Button(" Skins ", ImVec2(153 - 15, 50)))
				Config::Tab = 5; ImGui::SameLine();
			
			ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 6 ? active : inactive);
			if (ImGui::Button(" Settings ", ImVec2(153 - 15, 50)))
				Config::Tab = 6; 

		}
		ImGui::PopStyleColor(1);
		
	}
	ImGui::EndChild();

	/*
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);
	
	{
		//left
		static ImVec4 active = imguipp::to_vec4(Config::Settings.Cfg.buttonActive[0], Config::Settings.Cfg.buttonActive[0], Config::Settings.Cfg.buttonActive[2], Config::Settings.Cfg.buttonActive.a);
		static ImVec4 inactive = imguipp::to_vec4(Config::Settings.Cfg.button[0], Config::Settings.Cfg.button[0], Config::Settings.Cfg.button[2], Config::Settings.Cfg.button.a);
		
		ImGui::PushFont(mainFont);
		
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 1 ? active : inactive);
		if (ImGui::Button(" Legit ", ImVec2(230 - 15, 40)))
			Config::Tab = 1;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 2 ? active : inactive);
		if (ImGui::Button(" Rage ", ImVec2(230 - 15, 40)))
			Config::Tab = 2;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 3 ? active : inactive);
		if (ImGui::Button(" Visuals ", ImVec2(230 - 15, 40)))
			Config::Tab = 3;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 4 ? active : inactive);
		if (ImGui::Button(" Misc ", ImVec2(230 - 15, 40)))
			Config::Tab = 4;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 5 ? active : inactive);
		if (ImGui::Button(" Skin ", ImVec2(230 - 15, 40)))
			Config::Tab = 5;

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Config::Tab == 6 ? active : inactive);
		if (ImGui::Button(" Settings ", ImVec2(230 - 15, 40)))
			Config::Tab = 6;

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

		switch (Config::Tab) {
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
		gui::Theme();
		{
			gui::Menu();
		}
		
	}

	ImGui::End();
}




