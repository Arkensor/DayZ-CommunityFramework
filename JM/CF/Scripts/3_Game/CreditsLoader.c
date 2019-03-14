/*
	Epoch Mod for DayZ Standalone
	
	FileName: CreditsLoader.c

	Authors: DayZ SA Epoch Dev Team and Community Contributors
	https://github.com/EpochModTeam/DayZ_SA_Epoch/blob/experimental/README.md	
	
	Licensing:
	https://github.com/EpochModTeam/DayZ_SA_Epoch/blob/experimental/LICENSE.md

	Changelog:

	[1/16/2019] AWOL / DirtySanchez
		AWOL1 - DZSA Epoch Dev Team and Community Credits
	[1/20/2019] AWOL
		AWOL2 - Made credits dynamically support other mods via 'creditsJson' var in CfgMods. Also appended DayZ Game header and credits
	[14/03/2019] Jacob_Mango
		JM3 - Changed the formatting of the credits
		
	[NewDate] Author(s)
		Initials(Change#)-Description
*/
modded class CreditsLoader
{
	override static JsonDataCredits GetData()
	{
		// get all mods
		int modsCount = GetGame().ConfigGetChildrenCount("CfgMods");

		JsonDataCredits data = new JsonDataCredits;
		data.Departments = new array<ref JsonDataCreditsDepartment>;

		// Append credits for each mod that has a creditsJson defined.
		for (int i = 0; i < modsCount; i++)
		{
			string modName = "";
			GetGame().ConfigGetChildName("CfgMods", i, modName);
			string jsonCredits = "";
			GetGame().ConfigGetText("CfgMods " + modName + " creditsJson", jsonCredits);
			string modFancyName = "";
			GetGame().ConfigGetText("CfgMods " + modName + " name", modFancyName);
			string defaultCredits = "";
			GetGame().ConfigGetText("CfgMods " + modName + " credits", defaultCredits);
			
			if (jsonCredits != "") {
				ref JsonDataCredits jsondata;
				JsonFileLoader<ref JsonDataCredits>.JsonLoadFile(jsonCredits, jsondata);
				foreach(auto d: jsondata.Departments) {
					data.Departments.Insert(d);
				};
			} else if (defaultCredits != "" && modFancyName != "DayZ")
            {
                ref JsonDataCreditsDepartment mod_department_header = new JsonDataCreditsDepartment;
                mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
                mod_department_header.DepartmentName = ("				" + modFancyName);
                data.Departments.Insert(mod_department_header);
                ref JsonDataCreditsSection mod_section_modheader = new JsonDataCreditsSection;
                mod_section_modheader.SectionLines = new array<string>;
                mod_section_modheader.SectionName = ("");
                mod_section_modheader.SectionLines.Insert(defaultCredits);
                mod_department_header.Sections.Insert(mod_section_modheader);
            }
		}

		// Append DayZ Game Credits Header
		ref JsonDataCreditsDepartment data_department_header = new JsonDataCreditsDepartment;
		data_department_header.Sections = new array<ref JsonDataCreditsSection>;
		data_department_header.DepartmentName = ("				DayZ Standalone");
		data.Departments.Insert(data_department_header);

		// Append DayZ Game Credits
		ref JsonDataCredits dayzCreditsData;
		JsonFileLoader<ref JsonDataCredits>.JsonLoadFile(JSON_FILE_PATH, dayzCreditsData);
		foreach(auto b: dayzCreditsData.Departments) {
			data.Departments.Insert(b);
		};
		
		return data;
	}
}