class CfgPatches
{
    class Example
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
	class Example
	{
		dir = "Example";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Example";
		credits = "Jacob_Mango, Arkensor";
		creditsJson = "Example/Data/Credits.json";
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
				files[] = {"Example/5_Mission"};
			};
		}
	};
};