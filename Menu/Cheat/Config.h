#pragma once
#include "gui.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx9.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imguipp.h"
#include <string>

struct Colour {
	int r, g, b, a = 255;
};

class Config {
public:
	int Tab;
	float version = 0.1;
	
	//LegitBot Settings



	//RageBot Settings

	
	
	//Visual Settings
	

	
	//Misc Settings
	
	
	
	//Skin Changer

	
	
	//Config Settings
	
	
	Colour titleBg = { 82, 0, 122, 255 };
	Colour titleBgActive = { 82, 0, 122, 255 };
	Colour titleBgCollapsed = { 0, 0, 0, 255 };

	Colour button = { 79, 1, 32, 255 };
	Colour buttonHovered = { 31, 30, 31, 150 };
	Colour buttonActive = { 186, 2, 75, 255 };
	
	Colour separator = { 79, 1, 32, 255 };
	Colour separatorHovered = { 31, 30, 31, 150 };
	Colour separatorActive = { 186, 2, 75, 255 };
	

	
};