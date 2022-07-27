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
	io.Fonts->AddFontFromFileTTF("../Fonts/Oswald-Light.ttf", 12);

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
	
	style->Colors[ImGuiCol_TitleBg] = ImColor(config.titleBg);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(config.titleBgActive);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(config.titleBgCollapsed);

	style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 150);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(31, 30, 31, 150);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(41, 40, 41, 150);
	
	
}

void gui::Menu() noexcept
{
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);
	
	{
		//left

		static ImVec4 active = imguipp::to_vec4(186, 2, 75, 255);
		static ImVec4 inactive = imguipp::to_vec4(79, 1, 32, 255);
		
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
		if (ImGui::Button(" Config ", ImVec2(230 - 15, 40)))
			config.Tab = 6;

		ImGui::Spacing();
		ImGui::Spacing();
	}

	ImGui::NextColumn();;
	
	{

		//right
	}
	
}



void gui::Render() noexcept
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	
	ImGui::Begin(
		"Re-ReVoid",
		&exit,
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings 
	);
	{
		gui::Menu();
	}

	ImGui::End();
}




