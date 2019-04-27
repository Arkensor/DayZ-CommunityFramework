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
		version = "JM/CF/scripts/Data/Version.hpp";
		author = "Jacob_Mango";
		authorID = "76561198103677868"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {
					"JM/CF/Scripts/3_Game"
				};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {
					"JM/CF/Scripts/4_World"
				};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {
					"JM/CF/Scripts/5_Mission"
				};
			};
		}
	};
};