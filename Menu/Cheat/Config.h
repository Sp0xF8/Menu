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
	int Tab = 1;
	float version = 0.1;


	struct s_Config {
		struct s_Legit {
			bool enabled = false;
			int activationType = 0;
			int aimKey = 0;
			bool shootSmoke = false;
			bool shootFlash = false;

			float legitBackTracking = 0;
			bool legitDrawFOV = false;
			bool legitAutoPistol = false;
			
			struct s_Weapons {
				struct s_Rifles {
					float aimFOV = 0;
					float aimSmooth = 0;
					bool enableRCS = false;
					bool standaloneRCS = false;
					float xRCS = 0;
					float yRCS = 0;
					
					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;

					bool autoWall = false;
					float autoWallDamage = 0;
					
					struct s_Scout {
						float aimFOV = 0;
						float aimSmooth = 0;
						
					} Scout;
					struct s_AWP {
						float aimFOV = 0;
						float aimSmooth = 0;

						
					} AWP;
					struct s_Auto {
						float aimFOV = 0;
						float aimSmooth = 0;
	

					} Auto;
				} Rifles;
				struct s_SMGs {
					float aimFOV = 0;
					float aimSmooth = 0;
					bool enableRCS = false;
					bool standaloneRCS = false;
					float xRCS = 0;
					float yRCS = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;

					bool autoWall = false;
					float autoWallDamage = 0;
					
				} SMGs;
				struct s_Shotguns {
					float aimFOV = 0;
					float aimSmooth = 0;
					bool enableRCS = false;
					bool standaloneRCS = false;
					float xRCS = 0;
					float yRCS = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;

					bool autoWall = false;
					float autoWallDamage = 0;
					
				} Shotguns;
				struct s_Pistols {
					float aimFOV = 0;
					float aimSmooth = 0;
					bool enableRCS = false;
					bool standaloneRCS = false;
					float xRCS = 0;
					float yRCS = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;

					bool autoWall = false;
					float autoWallDamage = 0;
				} Pistols;
			} Weapons;
		} Legit;
		struct s_Rage {

			struct s_Weapons {
				struct s_Rifles {

					struct s_Scout {

					} Scout;
					struct s_AWP {

					} AWP;
					struct s_Auto {

					} Auto;
				} Rifles;
				struct s_SMGs {

				} SMGs;
				struct s_Shotguns {

				} Shotguns;
				struct s_Pistols {

					struct s_Revolver {

					} Revolver;
					struct s_Deagle {

					} Deagle;
				} Pistols;
			} Weapons;
		} Rage;
		struct s_Visuals {
		} Visuals;
		struct s_Misc {
		} Misc;
		struct s_Skinchanger {
		} Skinchanger;
		struct s_Cfg {
			Colour titleBg = { 82, 0, 122, 255 };
			Colour titleBgActive = { 82, 0, 122, 255 };
			Colour titleBgCollapsed = { 0, 0, 0, 255 };

			Colour button = { 79, 1, 32, 255 };
			Colour buttonHovered = { 31, 30, 31, 150 };
			Colour buttonActive = { 186, 2, 75, 255 };

			Colour separator = { 79, 1, 32, 255 };
			Colour separatorHovered = { 31, 30, 31, 150 };
			Colour separatorActive = { 186, 2, 75, 255 };
		} Cfg;
		
	} Settings; 
	
	//LegitBot Settings

	
	
	
	
	
	

	


	//RageBot Settings

	
	
	//Visual Settings
	

	
	//Misc Settings
	
	
	
	//Skin Changer

	
	//Settings
	

	
	
	//Config Settings
	
	
	
	

	
};