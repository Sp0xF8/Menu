#pragma once

namespace Config {
	extern int Tab;
	extern float version;
	extern const char* binds[];
	extern int item_current;

	namespace Settings {
		namespace Legit {
			extern bool enabled;
			
			extern bool shootSmoke;
			extern bool shootFlash;
			extern bool grenadeHelper;
			extern bool drawFOV;
			extern bool quickStop;

			
			namespace Weapons {
				namespace Rifles {
					extern float aimFOV;
					extern float aimSmooth;
					extern bool enableRCS;
					extern bool standaloneRCS;
					extern float xRCS;
					extern float yRCS;
					
					
					/// <summary>
					/// Bone Selection
					/// </summary>
					
					extern bool aimHead;
					extern bool aimNeck;
					extern bool aimChest;
					extern bool aimStomach;
					extern bool aimPelvis;
					extern bool aimArms;
					extern bool aimLegs;
					extern bool aimFeet;
					extern bool aimHands;
					
					extern bool triggerBot;
					extern int triggerKey;
					extern float triggerHC;
					extern int minTrigDmg;
					extern float triggerDelay;
					
					extern bool backTrackingEnabled;
					extern int backTracking;
					
					extern bool autoWall;
					extern float autoWallDamage;
					
					namespace Scout {
						extern float aimFOV;
						extern float aimSmooth;
						
						extern bool aimHead;
						extern bool aimNeck;
						extern bool aimChest;
						extern bool aimStomach;
						extern bool aimPelvis;
						extern bool aimArms;
						extern bool aimLegs;
						extern bool aimFeet;
						extern bool aimHands;

						extern bool triggerBot;
						extern int triggerKey;
						extern float triggerHC;
						extern int minTrigDmg;
						extern float triggerDelay;
						
						extern bool backTrackingEnabled;
						extern int backTracking;
						
						extern bool autoWall;
						extern float autoWallDamage;
					};
					namespace AWP {
						extern float aimFOV;
						extern float aimSmooth;

						extern bool aimHead;
						extern bool aimNeck;
						extern bool aimChest;
						extern bool aimStomach;
						extern bool aimPelvis;
						extern bool aimArms;
						extern bool aimLegs;
						extern bool aimFeet;
						extern bool aimHands;

						extern bool triggerBot;
						extern int triggerKey;
						extern float triggerHC;
						extern int minTrigDmg;
						extern float triggerDelay;
						
						extern bool backTrackingEnabled;
						extern int backTracking;
						
						extern bool autoWall;
						extern float autoWallDamage;
					};
					namespace Auto {
						extern float aimFOV;
						extern float aimSmooth;
	
						extern bool aimHead;
						extern bool aimNeck;
						extern bool aimChest;
						extern bool aimStomach;
						extern bool aimPelvis;
						extern bool aimArms;
						extern bool aimLegs;
						extern bool aimFeet;
						extern bool aimHands;

						extern bool triggerBot;
						extern int triggerKey;
						extern float triggerHC;
						extern int minTrigDmg;
						extern float triggerDelay;
						
						extern bool backTrackingEnabled;
						extern int backTracking;
						
						extern bool autoWall;
						extern float autoWallDamage;
					};
				};
				namespace SMGs {
					extern float aimFOV;
					extern float aimSmooth;
					extern bool enableRCS;
					extern bool standaloneRCS;
					extern float xRCS;
					extern float yRCS;

					extern bool triggerBot;
					extern int triggerKey;
					extern float triggerHC;
					extern int minTrigDmg;
					extern float triggerDelay;
					
					extern bool backTrackingEnabled;
					extern int backTracking;
					
					extern bool autoWall;
					extern float autoWallDamage;
					
					extern bool aimHead;
					extern bool aimNeck;
					extern bool aimChest;
					extern bool aimStomach;
					extern bool aimPelvis;
					extern bool aimArms;
					extern bool aimLegs;
					extern bool aimFeet;
					extern bool aimHands;
				};
				namespace Shotguns {
					extern float aimFOV;
					extern float aimSmooth;

					extern bool triggerBot;
					extern int triggerKey;
					extern float triggerHC;
					extern int minTrigDmg;
					extern float triggerDelay;
					
					extern bool backTrackingEnabled;
					extern int backTracking;
					
					extern bool autoWall;
					extern float autoWallDamage;
					
					extern bool aimHead;
					extern bool aimNeck;
					extern bool aimChest;
					extern bool aimStomach;
					extern bool aimPelvis;
					extern bool aimArms;
					extern bool aimLegs;
					extern bool aimFeet;
					extern bool aimHands;
				};
				namespace Pistols {
					extern float aimFOV;
					extern float aimSmooth;

					extern bool autoPistol;

					extern bool triggerBot;
					extern int triggerKey;
					extern float triggerHC;
					extern int minTrigDmg;
					extern float triggerDelay;
					
					extern bool backTrackingEnabled;
					extern int backTracking;
					
					extern bool autoWall;
					extern float autoWallDamage;
					
					extern bool aimHead;
					extern bool aimNeck;
					extern bool aimChest;
					extern bool aimStomach;
					extern bool aimPelvis;
					extern bool aimArms;
					extern bool aimLegs;
					extern bool aimFeet;
					extern bool aimHands;
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
			
			extern bool legitBhop;
			extern bool bhop;
			extern bool autoStrafe;
			extern bool autoAccept;
			extern bool autoBlock;
			extern bool reVoidTag;
			extern bool customTag;
			extern char customTagText[11];
		};
		namespace Skinchanger {
		};
		namespace Cfg {
            extern bool isOpen;
			//R G B A !!!!!!!!!!!!!!!!!!
			extern float titleBg[4];
			extern float titleBgActive[4];
			extern float titleBgCollapsed[4];

			extern float textCol1[4];

			extern float button[4];
			extern float buttonHovered[4];
			extern float buttonActive[4];

			extern float separator[4];
			extern float separatorHovered[4];
			extern float separatorActive[4];

			extern float windowBg[4];
			extern float childBg[4];
			extern float borderBg[4];
			
			
			extern float frameBg[4];
			extern float frameBgHover[4];
			extern float frameBgActive[4];

			extern float headder[4];
			extern float headderHover[4];
			extern float headderActive[4];
			
			extern float checkMark[4];
			
			extern float sliderGrab[4];
			extern float sliderGrabActive[4];
			
			extern float scrollBar[4];
			extern float scrollBarGrab[4];
			extern float scrollBarHovered[4];
			extern float scrollBarActive[4];
			
			extern float menuBonesInactive[4];
			extern float menuBonesActive[4];
		};
		
	}; 

	extern void SaveConfig();
	extern void LoadConfig();
	
};