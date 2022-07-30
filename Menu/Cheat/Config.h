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
	float version = 0.01;
	const char* binds[] = { "MB1", "MB2", "MB3", "MB4", "MB5", "INS", "HOME" };
	static int item_current = 0;

	struct s_Config {
		struct s_Legit {
			bool enabled = false;
			int activationType = 0;
			int aimKey = 0;
			bool shootSmoke = false;
			bool shootFlash = false;

			
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
					
					
					/// <summary>
					/// Bone Selection
					/// </summary>
					
					bool aimHead = false;
					bool aimNeck = false;
					bool aimChest = false;
					bool aimStomach = false;
					bool aimPelvis = false;
					bool aimArms = false;
					bool aimLegs = false;
					bool aimFeet = false;
					bool aimHands = false;
					
					bool triggerBot = false;
					int triggerKey;
					float triggerHC = 0;
					float legitBackTracking = 0;
					bool autoWall = false;
					float autoWallDamage = 0;
					
					struct s_Scout {
						float aimFOV = 0;
						float aimSmooth = 0;
						
						bool aimHead = false;
						bool aimNeck = false;
						bool aimChest = false;
						bool aimStomach = false;
						bool aimPelvis = false;
						bool aimArms = false;
						bool aimLegs = false;
						bool aimFeet = false;
						bool aimHands = false;

						bool triggerBot = false;
						int triggerKey = 0;
						float triggerHC = 0;
						float legitBackTracking = 0;
						bool autoWall = false;
						float autoWallDamage = 0;
					} Scout;
					struct s_AWP {
						float aimFOV = 0;
						float aimSmooth = 0;

						bool aimHead = false;
						bool aimNeck = false;
						bool aimChest = false;
						bool aimStomach = false;
						bool aimPelvis = false;
						bool aimArms = false;
						bool aimLegs = false;
						bool aimFeet = false;
						bool aimHands = false;

						bool triggerBot = false;
						int triggerKey = 0;
						float triggerHC = 0;
						float legitBackTracking = 0;
						bool autoWall = false;
						float autoWallDamage = 0;
					} AWP;
					struct s_Auto {
						float aimFOV = 0;
						float aimSmooth = 0;
	
						bool aimHead = false;
						bool aimNeck = false;
						bool aimChest = false;
						bool aimStomach = false;
						bool aimPelvis = false;
						bool aimArms = false;
						bool aimLegs = false;
						bool aimFeet = false;
						bool aimHands = false;

						bool triggerBot = false;
						int triggerKey = 0;
						float triggerHC = 0;
						float legitBackTracking = 0;
						bool autoWall = false;
						float autoWallDamage = 0;
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
					float legitBackTracking = 0;
					bool autoWall = false;
					float autoWallDamage = 0;
					
					bool aimHead = false;
					bool aimNeck = false;
					bool aimChest = false;
					bool aimStomach = false;
					bool aimPelvis = false;
					bool aimArms = false;
					bool aimLegs = false;
					bool aimFeet = false;
					bool aimHands = false;
				} SMGs;
				struct s_Shotguns {
					float aimFOV = 0;
					float aimSmooth = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;
					float legitBackTracking = 0;
					bool autoWall = false;
					float autoWallDamage = 0;
					
					bool aimHead = false;
					bool aimNeck = false;
					bool aimChest = false;
					bool aimStomach = false;
					bool aimPelvis = false;
					bool aimArms = false;
					bool aimLegs = false;
					bool aimFeet = false;
					bool aimHands = false;
				} Shotguns;
				struct s_Pistols {
					float aimFOV = 0;
					float aimSmooth = 0;

					bool autoPistol = false;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;
					float legitBackTracking = 0;
					bool autoWall = false;
					float autoWallDamage = 0;
					
					bool aimHead = false;
					bool aimNeck = false;
					bool aimChest = false;
					bool aimStomach = false;
					bool aimPelvis = false;
					bool aimArms = false;
					bool aimLegs = false;
					bool aimFeet = false;
					bool aimHands = false;
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
			
			bool legitBhop = false;
			bool bhop = false;
			bool autoStrafe = false;
			bool autoAccept = false;
			bool autoBlock = false;
			bool reVoidTag = false;
			bool customTag = false;
			char customTagText[11] = "Custom";
		} Misc;
		struct s_Skinchanger {
		} Skinchanger;
		struct s_Cfg {
			//R G B A !!!!!!!!!!!!!!!!!!
			float titleBg[4] =			{ 0.32f, 0.00f, 0.47f, 1.00f };
			float titleBgActive[4] =	{ 0.32f, 0.00f, 0.47f, 1.00f };
			float titleBgCollapsed[4] = { 0.00f, 0.00f, 0.00f, 1.00f };

			float textCol1[4] =			{ 1.00f, 1.00f, 1.00f, 1.00f };

			float button[4] =			{ 0.30f, 0.00f, 0.13f, 1.00f };
			float buttonHovered[4] =	{ 0.12f, 0.11f, 0.12f, 1.00f };
			float buttonActive[4] =		{ 0.71f, 0.00f, 0.29f, 1.00f };

			float separator[4] =		{ 0.30f, 0.00f, 0.13f, 1.00f };
			float separatorHovered[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float separatorActive[4] =	{ 0.71f, 0.00f, 0.29f, 1.00f };

			float windowBg[4] =			{ 0.06f, 0.06f, 0.06f, 0.94f };
			float childBg[4] =			{ 0.00f, 0.00f, 0.00f, 0.00f };
			float borderBg[4] =			{ 0.27f, 0.00f, 0.11f, 1.00f };
			
			
			float frameBg[4] =			{ 0.30f, 0.00f, 0.13f, 1.00f };
			float frameBgHover[4] =		{ 0.12f, 0.11f, 0.12f, 1.00f };
			float frameBgActive[4] =	{ 0.30f, 0.00f, 0.13f, 1.00f };

			float headder[4] =			{ 0.30f, 0.00f, 0.13f, 1.00f };
			float headderHover[4] =		{ 0.12f, 0.11f, 0.12f, 1.00f };
			float headderActive[4] =	{ 0.30f, 0.00f, 0.13f, 1.00f };
			
			float checkMark[4] =		{ 0.71f, 0.00f, 0.29f, 1.00f };
			
			float sliderGrab[4] =		{ 0.30f, 0.00f, 0.13f, 1.00f };
			float sliderGrabActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };
			
			float scrollBar[4] =		{ 0.30f, 0.00f, 0.13f, 1.00f };
			float scrollBarGrab[4] =	{ 0.71f, 0.00f, 0.29f, 1.00f };
			float scrollBarHovered[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float scrollBarActive[4] =	{ 0.71f, 0.00f, 0.29f, 1.00f };
			
			float menuBonesInactive[4] = { 0.30f, 0.00f, 0.13f, 0.50f };
			float menuBonesActive[4] =	{ 0.71f, 0.00f, 0.29f, 1.00f };
		} Cfg;
		
	} Settings; 
	
};