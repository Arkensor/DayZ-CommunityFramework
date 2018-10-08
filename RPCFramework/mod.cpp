class CfgMods
{
	class RPCFramework
	{
		dir = "RPCFramework";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "RPCFramework";
		credits = "Jacob_Mango, Arkensor";
		author = "Jacob_Mango, Arkensor";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = { "Game" };
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"JM/RPC/scripts/3_Game"};
			};
		}
	};
};
