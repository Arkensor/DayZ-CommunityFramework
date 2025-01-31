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
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("JsonDataCredits");
#endif

		JsonDataCredits data = new JsonDataCredits;
		data.Departments = {};

		// get all mods
		array<ref ModStructure> mods = ModLoader.GetMods();
		foreach (auto mod : mods)
		{
			auto credits = mod.GetCredits();

			if (!credits || !credits.Departments) 
				continue;

			foreach (auto department : credits.Departments)
			{
				data.Departments.Insert(department);
			}
		}

		// Append DayZ Game Credits Header
		JsonDataCreditsDepartment dayzDepartmentHeader();
		dayzDepartmentHeader.Sections = {};
		// Need to have at least one section (can be empty), else the red line below department header is misaligned in credits scroller
		JsonDataCreditsSection section = new JsonDataCreditsSection;
		section.SectionLines = {};
		dayzDepartmentHeader.Sections.Insert(section);
		dayzDepartmentHeader.DepartmentName = "DayZ Standalone";
		data.Departments.Insert(dayzDepartmentHeader);

		// Append DayZ Game Credits
		JsonDataCredits dayzCreditsData;
		string errorMessage;
		if (JsonFileLoader<ref JsonDataCredits>.LoadFile(JSON_FILE_PATH, dayzCreditsData, errorMessage))
		{
			foreach (auto dayzDepartment : dayzCreditsData.Departments)
			{
				data.Departments.Insert(dayzDepartment);
			}
		}
		else
		{
			CF_Log.Warn("%1: %2", JSON_FILE_PATH, errorMessage);
		}

		return data;
	}
};
