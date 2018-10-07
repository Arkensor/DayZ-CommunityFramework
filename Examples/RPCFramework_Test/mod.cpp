class CfgMods
{
	class RPCFramework_Test
	{
		dir = "RPCFramework_Test";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "RPCFramework_Test";
		credits = "Jacob_Mango, Arkensor";
		author = "Jacob_Mango, Arkensor";
		authorID = "0"; 
		version = "0.1"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Mission"};
		
		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"JM/RPC/test/5_Mission"};
			};
		}
	};
};