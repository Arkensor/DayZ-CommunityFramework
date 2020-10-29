class CfgPatches
{
	class JM_CF_Defines
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class JM_CommunityFramework_ScriptDefines
	{
		dir = "SCRIPT_DEFINES";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Script Defines";
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
					"JM\CF\Defines"
				};
			};
			class gameScriptModule
			{
				value = "";
				files[] =
				{
					"JM\CF\Defines"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"JM\CF\Defines"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"JM\CF\Defines"
				};
			};
		};
	};
};
