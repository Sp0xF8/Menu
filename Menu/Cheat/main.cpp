#include "gui.h"

#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();

	while (!(GetKeyState(VK_INSERT) & 0x8000))
	{
		gui::BeginRender();
		
		gui::Theme(); 
		{
			gui::Render();
		}
		
		
		gui::EndRender();


		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
	}
	
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();
	
	return EXIT_SUCCESS;
}
	