class CfgPatches
{
	class JM_CF_Scripts
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
		
		defines[] = 
        { 
            "CF_MODULE_CONFIG",
            "CF_EXPRESSION",
            //"CF_EXPRESSION_TEST",
            //"CF_TRACE_ENABLED",
            "CF_TRACE_STACK_NAME_ASSUMPTION_FIX",
            "CF_GHOSTICONS",
            "CF_MODSTORAGE",
            //"CF_MODSTORAGE_TEST",
            //"CF_MODSTORAGE_TRACE",
            "CF_SURFACES",
            "CF_MODULES",
            "CF_REF_FIX",
            "CF_BUGFIX_REF", // Same as CF_REF_FIX but for mods that already anticipated a different name
            "CF_BUGFIX_XML",
            "CF_DOUBLYLINKEDNODES"
        };
        
		dependencies[] = { "Core", "Game", "World", "Mission" };
		
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] =
				{
					"JM/CF/Scripts/1_Core"
				};
			};
			class gameLibScriptModule
			{
				value = "";
				files[] =
				{
				    "JM/CF/Scripts/2_GameLib"
				};
			};
			class gameScriptModule
			{
				value = "CF_CreateGame";
				files[] =
				{
					"JM/CF/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = ""; //! Doesn't work
				files[] =
				{
					"JM/CF/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"JM/CF/Scripts/5_Mission"
				};
			};
		};
	};
};
