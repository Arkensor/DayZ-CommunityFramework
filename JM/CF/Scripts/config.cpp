#include "\JM\CF\Defines\CFDefines.c"

class CfgPatches
{
	class JM_CF_Scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",

			//! Community Framework
			#ifdef CF_MODULE_PERMISSIONS
			"JM_CF_Permissions",
			#endif
		};
	};
};

class CfgMods
{
	class JM_CommunityFramework
	{
		dir = "JM/CF";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Community Framework";
		credits = "Jacob_Mango, Arkensor";
		creditsJson = "JM/CF/Scripts/Data/Credits.json";
		version = "0.0.0";
		versionPath = "JM/CF/scripts/Data/Version.hpp";
		author = "Jacob_Mango";
		authorID = "76561198103677868"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = { "Core", "Game", "World", "Mission" };
		
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] =
				{
					"JM/CF/Defines",
					"JM/CF/XML/1_Core",
					"JM/CF/Scripts/1_Core"
				};
			};
			class gameScriptModule
			{
				value = "CF_CreateGame";
				files[] =
				{
					"JM/CF/Defines",
					"JM/CF/XML/3_Game",
					"JM/CF/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = ""; //! Doesn't work
				files[] =
				{
					"JM/CF/Defines",
					"JM/CF/XML/4_World",
					"JM/CF/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"JM/CF/Defines",
					"JM/CF/XML/5_Mission",
					"JM/CF/Scripts/5_Mission"
				};
			};
		};
	};
};
