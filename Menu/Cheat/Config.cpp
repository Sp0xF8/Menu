#include "Config.h"
#include "../YMAL/Yaml.h"

#include <iostream>
#include <fstream>


namespace Config {
	int Tab = 1;
	float version = 0.01;
	const char* binds[] = { "MB1", "MB2", "MB3", "MB4", "MB5", "INS", "HOME" };
	int item_current = 0;

	namespace Settings {
		namespace Legit {
			bool enabled = false;
			int activationType = 0;
			int aimKey = 0;
			
			bool shootSmoke = false;
			bool shootFlash = false;
			bool grenadeHelper = false;
			bool drawFOV = false;
			bool quickStop = false;
			

			namespace Weapons {
				namespace Rifles {
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
					int minTrigDmg = 0;
					float triggerDelay = 0;

					bool backTrackingEnabled = false;
					int backTracking = 0;

					bool autoWall = false;
					float autoWallDamage = 0;

					namespace Scout {
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
						int minTrigDmg = 0;
						float triggerDelay = 0;

						bool backTrackingEnabled = false;
						int backTracking = 0;

						bool autoWall = false;
						float autoWallDamage = 0;
					};
					namespace AWP {
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
						int minTrigDmg = 0;
						float triggerDelay = 0;

						bool backTrackingEnabled = false;
						int backTracking = 0;

						bool autoWall = false;
						float autoWallDamage = 0;
					};
					namespace Auto {
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
						int minTrigDmg = 0;
						float triggerDelay = 0;

						bool backTrackingEnabled = false;
						int backTracking = 0;

						bool autoWall = false;
						float autoWallDamage = 0;
					};
				};
				namespace SMGs {
					float aimFOV = 0;
					float aimSmooth = 0;
					bool enableRCS = false;
					bool standaloneRCS = false;
					float xRCS = 0;
					float yRCS = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;
					int minTrigDmg = 0;
					float triggerDelay = 0;

					bool backTrackingEnabled = false;
					int backTracking = 0;

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
				};
				namespace Shotguns {
					float aimFOV = 0;
					float aimSmooth = 0;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;
					int minTrigDmg = 0;
					float triggerDelay = 0;

					bool backTrackingEnabled = false;
					int backTracking = 0;

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
				};
				namespace Pistols {
					float aimFOV = 0;
					float aimSmooth = 0;

					bool autoPistol = false;

					bool triggerBot = false;
					int triggerKey = 0;
					float triggerHC = 0;
					int minTrigDmg = 0;
					float triggerDelay = 0;

					bool backTrackingEnabled = false;
					int backTracking = 0;

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
				};
			};
		};
		namespace Rage {

			namespace Weapons {
				namespace Rifles {

					namespace Scout {

					};
					namespace AWP {

					};
					namespace Auto {

					};
				};
				namespace SMGs {

				};
				namespace s_Shotguns {

				};
				namespace s_Pistols {

					namespace s_Revolver {

					};
					namespace s_Deagle {

					};
				};
			};
		};
		namespace Visuals {
		};
		namespace Misc {

			bool legitBhop = false;
			bool bhop = false;
			bool autoStrafe = false;
			bool autoAccept = false;
			bool autoBlock = false;
			bool reVoidTag = false;
			bool customTag = false;
			char customTagText[11] = "Custom";
		};
		namespace Skinchanger {
		};
		namespace Cfg {
			//R G B A !!!!!!!!!!!!!!!!!!
			float titleBg[4] = { 0.32f, 0.00f, 0.47f, 1.00f };
			float titleBgActive[4] = { 0.32f, 0.00f, 0.47f, 1.00f };
			float titleBgCollapsed[4] = { 0.00f, 0.00f, 0.00f, 1.00f };

			float textCol1[4] = { 1.00f, 1.00f, 1.00f, 1.00f };

			float button[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float buttonHovered[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float buttonActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };

			float separator[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float separatorHovered[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float separatorActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };

			float windowBg[4] = { 0.06f, 0.06f, 0.06f, 0.94f };
			float childBg[4] = { 0.00f, 0.00f, 0.00f, 0.00f };
			float borderBg[4] = { 0.27f, 0.00f, 0.11f, 1.00f };


			float frameBg[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float frameBgHover[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float frameBgActive[4] = { 0.30f, 0.00f, 0.13f, 1.00f };

			float headder[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float headderHover[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float headderActive[4] = { 0.30f, 0.00f, 0.13f, 1.00f };

			float checkMark[4] = { 0.71f, 0.00f, 0.29f, 1.00f };

			float sliderGrab[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float sliderGrabActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };

			float scrollBar[4] = { 0.30f, 0.00f, 0.13f, 1.00f };
			float scrollBarGrab[4] = { 0.71f, 0.00f, 0.29f, 1.00f };
			float scrollBarHovered[4] = { 0.12f, 0.11f, 0.12f, 1.00f };
			float scrollBarActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };

			float menuBonesInactive[4] = { 0.30f, 0.00f, 0.13f, 0.50f };
			float menuBonesActive[4] = { 0.71f, 0.00f, 0.29f, 1.00f };
		};
		


		

	};




	void SaveConfig() {

		
		std::ofstream myFile;
		
		
		myFile.open("C:/Users/Public/Documents/Config1.yaml", std::fstream::out);
		if (myFile.is_open()) {
			myFile << "Settings:\n";
			myFile << "Legitbot:\n";
			myFile << "- boolean: " << Config::Settings::Legit::enabled << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::shootFlash << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::shootSmoke << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::grenadeHelper << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::drawFOV << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::quickStop << "\n";
			
			myFile << "Weapons:\n";
			
			/// <summary>
			/// RIFLES
			/// </summary>
			
			myFile << "Rifles:\n";
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::aimSmooth << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::enableRCS << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::standaloneRCS << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::xRCS << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::yRCS << "\n";
			
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::aimHands << "\n";
			
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::triggerDelay << "\n";
			
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::backTracking << "\n";
			
			/// <summary>
			/// SCOUT
			/// </summary>

			myFile << "Scout:\n";

			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimSmooth << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Scout::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Scout::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Scout::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Scout::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Scout::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Scout::backTracking << "\n";

			/// <summary>
			/// AWP
			/// </summary>
			myFile << "AWP:\n";
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimSmooth << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::AWP::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::AWP::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::AWP::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::AWP::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::AWP::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::AWP::backTracking << "\n";
			

			/// <summary>
			/// AUTO
			/// </summary>
			myFile << "Auto:\n";
			
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimSmooth << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Auto::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Auto::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Auto::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Rifles::Auto::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Rifles::Auto::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Rifles::Auto::backTracking << "\n";

			
			/// <summary>
			/// SMGS
			/// </summary>
			
			myFile << "SMGs:\n";
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::aimSmooth << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::enableRCS << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::standaloneRCS << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::xRCS << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::yRCS << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::SMGs::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::SMGs::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::SMGs::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::SMGs::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::SMGs::backTracking << "\n";


			/// <summary>
			/// Shotguns
			/// </summary>

			myFile << "Shotguns:\n";
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::Shotguns::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Shotguns::aimSmooth << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Shotguns::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Shotguns::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Shotguns::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Shotguns::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Shotguns::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Shotguns::backTracking << "\n";


			/// <summary>
			/// PISTOLS
			/// </summary>
			
			myFile << "Pistols:\n";
			
			myFile << "- float: " << Config::Settings::Legit::Weapons::Pistols::aimFOV << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Pistols::aimSmooth << "\n";


			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimHead << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimNeck << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimChest << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimPelvis << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimStomach << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimArms << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimLegs << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimFeet << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::aimHands << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::triggerBot << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Pistols::triggerKey << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Pistols::triggerHC << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Pistols::minTrigDmg << "\n";
			myFile << "- float: " << Config::Settings::Legit::Weapons::Pistols::triggerDelay << "\n";

			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::backTrackingEnabled << "\n";
			myFile << "- int: " << Config::Settings::Legit::Weapons::Pistols::backTracking << "\n";
			myFile << "- boolean: " << Config::Settings::Legit::Weapons::Pistols::autoPistol << "\n";
			
			
			myFile.close();
		}

	}
};