#pragma once
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx9.h"
#include "../Imgui/imgui_impl_win32.h"

struct Colour {
	int r, g, b, a = 255;
};

class Config {
public:
	int Tab = 0;
	
	//LegitBot Settings



	//RageBot Settings

	
	
	//Visual Settings
	

	
	//Misc Settings
	
	
	
	//Skin Changer

	
	
	//Config Settings
	
	ImVec4 titleBg = { 82, 0, 122, 255 };
	ImVec4 titleBgActive = { 82, 0, 122, 255 };
	ImVec4 titleBgCollapsed = { 0, 0, 0, 255 };

	ImVec4 button = { 31, 30, 31, 150 };
	ImVec4 buttonHovered = { 31, 30, 31, 150 };
	ImVec4 buttonActive = { 41, 40, 41, 150 };

	
};