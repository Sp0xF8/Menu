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




namespace Config {
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
			//R G B A !!!!!!!!!!!!!!!!!!
			float titleBg[4] = { 0.32f, 0, 0.47f, 1.0f };
			float titleBgActive[4] = { 0.32f, 0, 0.47f, 1.0f };
			float titleBgCollapsed[4] = { 0, 0, 0, 1.0f };

			float textCol1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			float button[4] = { 0.30f, 0, 0.13f, 1.0f };
			float buttonHovered[4] = { 0.12f, 0.11f, 0.12f, 1.0f };
			float buttonActive[4] = { 0.71f, 0, 0.29f, 1.0f };

			float separator[4] = { 0.30f, 0, 0.13f, 1.0f };
			float separatorHovered[4] = { 0.12f, 0.11f, 0.12f, 1.0f };
			float separatorActive[4] = { 0.71f, 0, 0.29f, 1.0f };
		} Cfg;
		
	} Settings; 
	
};