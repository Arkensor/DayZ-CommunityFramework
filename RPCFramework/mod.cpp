class CfgMods
{
	class RPCFramework
	{
		dir = "RPCFramework";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "RPC Framework";
		credits = "Jacob_Mango";
		author = "Jacob_Mango";
		authorID = "0"; 
		version = "0.1"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"JM/RPC/scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"JM/RPC/scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"JM/RPC/scripts/5_Mission"};
			};
		}
	};
};
