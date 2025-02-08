modded class ModStructure
{
	protected CF_String m_CF_Name;

	int m_CF_HashA;
	int m_CF_HashB;

	protected ref array<ref ModInput> m_CF_ModInputs;
	protected ref JsonDataCredits m_CF_Credits;

	protected string m_CF_ModVersion;
	protected int m_CF_StorageVersion;

	/**
	 * Set the mod specific data in here
	 * 
	 * @param modName	The name of the loaded mod, retrieved from the CfgMods params array
	 * 
	 * @code
	 *	override bool CF_OnLoad( string modName )
	 *	{
	 *		if ( modName != "JM_CommunityFramework" )
	 *			return super.CF_OnLoad( modName );
	 *
	 *		//! Set the storage version for this mod
	 *		SetStorageVersion( 1 );
	 *
	 *		return true;
	 *	}
	 * @endcode
	 */
	bool CF_OnLoad(CF_String modName)
	{
		return false;
	}

	/**
	 * @brief Backwards compatibility
	 * 
	 * @deprecated
	 */
	bool OnLoad(string modName)
	{
		return false;
	}

	void _CF_Init(int index, string name, string path)
	{
		m_ModIndex = index;
		m_ModPath = path;

		m_CF_Name = name;
		m_CF_HashA = m_CF_Name.Hash();
		m_CF_HashB = m_CF_Name.Reverse().Hash();

		m_CF_ModInputs = new array<ref ModInput>;
		m_CF_StorageVersion = 0;

		if (GetGame().ConfigIsExisting(m_ModPath))
		{
			if (GetGame().ConfigIsExisting(m_ModPath + " storageVersion"))
			{
				SetStorageVersion(GetGame().ConfigGetInt(m_ModPath + " storageVersion"));
			}

			GetGame().ConfigGetText(m_ModPath + " name", m_ModName);

			if (m_ModName.Trim() == "")
				m_ModName = name;

			JsonDataCreditsDepartment mod_department_header;
			JsonDataCreditsSection mod_section_modheader;

			if (GetGame().ConfigIsExisting(m_ModPath + " creditsJson"))
			{
				string creditsPath;
				GetGame().ConfigGetText(m_ModPath + " creditsJson", creditsPath);

				string errorMessage;
				if (!JsonFileLoader<JsonDataCredits>.LoadFile(creditsPath, m_CF_Credits, errorMessage))
				{
					CF_Log.Warn("%1: %2", creditsPath, errorMessage);
				}
				else if (m_CF_Credits.Departments.Count() > 0)
				{
					//! Check if 1st department name contains mod name or vice versa, and if not, insert it

					string departmentName = m_CF_Credits.Departments[0].DepartmentName;
					string modName = m_ModName;

					departmentName.ToLower();
					modName.ToLower();

					departmentName.Replace("-", " ");
					departmentName.Replace("_", " ");
					modName.Replace("-", " ");
					modName.Replace("_", " ");

					if (!departmentName.Contains(modName) && !modName.Contains(departmentName))
					{
						if (m_CF_Credits.Departments.Count() == 1)
						{
							//! If there is only one department in this mod's credits, overwrite department name with mod name
							m_CF_Credits.Departments[0].DepartmentName = m_ModName;
						}
						else
						{
							//! If there is more than one department in this mod's credits, insert a new department with mod name at the top
							mod_department_header = new JsonDataCreditsDepartment;
							mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
							mod_department_header.DepartmentName = m_ModName;
							m_CF_Credits.Departments.InsertAt(mod_department_header, 0);
						}
					}
				}
			}
			else if (GetGame().ConfigIsExisting(m_ModPath + " credits"))
			{
				string credits = "";

				m_CF_Credits = new JsonDataCredits;
				m_CF_Credits.Departments = new array<ref JsonDataCreditsDepartment>;

				mod_department_header = new JsonDataCreditsDepartment;
				mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
				mod_department_header.DepartmentName = m_ModName;

				string author = "";
				bool hasAuthor = GetGame().ConfigIsExisting(m_ModPath + " author");
				GetGame().ConfigGetText(m_ModPath + " author", author);

				if (hasAuthor && author != "")
				{
					JsonDataCreditsSection mod_section_modheader_author = new JsonDataCreditsSection;
					mod_section_modheader_author.SectionLines = new array<string>;
					mod_section_modheader_author.SectionName = ("Author");

					mod_section_modheader_author.SectionLines.Insert(author);

					mod_department_header.Sections.Insert(mod_section_modheader_author);
				}

				GetGame().ConfigGetText(m_ModPath + " credits", credits);

				if (credits != "")
				{
					mod_section_modheader = new JsonDataCreditsSection;
					mod_section_modheader.SectionLines = new array<string>;
					mod_section_modheader.SectionName = ("Credits");

					array<string> creditsArray = new array<string>;
					credits.Split(", ", creditsArray);
					foreach (string credit : creditsArray)
					{
						mod_section_modheader.SectionLines.Insert(credit);
					}

					mod_department_header.Sections.Insert(mod_section_modheader);
				}

				m_CF_Credits.Departments.Insert(mod_department_header);
			}
			else
			{
				m_CF_Credits = new JsonDataCredits;
			}

			if (mod_department_header && mod_department_header.Sections.Count() == 0)
			{
				//! Need to have at least one section (can be empty), else the red line below department header is misaligned in credits scroller
				mod_section_modheader = new JsonDataCreditsSection;
				mod_section_modheader.SectionLines = {};
				mod_department_header.Sections.Insert(mod_section_modheader);
			}

			if (GetGame().ConfigIsExisting(m_ModPath + " versionPath"))
			{
				string versionPath;
				GetGame().ConfigGetText(m_ModPath + " versionPath", versionPath);

				FileHandle file_handle = OpenFile(versionPath, FileMode.READ);

				while (FGets(file_handle, m_CF_ModVersion) > 0)
					break;

				CloseFile(file_handle);
			}
			else if (GetGame().ConfigIsExisting(m_ModPath + " version"))
			{
				GetGame().ConfigGetText(m_ModPath + " version", m_CF_ModVersion);
			}

			if (GetGame().ConfigIsExisting(m_ModPath + " inputs"))
			{
				string inputPath;
				GetGame().ConfigGetText(m_ModPath + " inputs", inputPath);

				CF_XML_Document document;
				if (inputPath != "" && CF.XML.ReadDocument(inputPath, document))
				{
					auto parent_tag = document.Get("modded_inputs")[0];
					if (parent_tag)
						parent_tag = parent_tag.GetTag("inputs")[0];
					if (parent_tag)
						parent_tag = parent_tag.GetTag("actions")[0];

					array<CF_XML_Tag> inputs = null;
					if (!parent_tag)
						inputs = new array<CF_XML_Tag>();
					else
						inputs = parent_tag.GetTag("input");

					for (int i = 0; i < inputs.Count(); i++)
					{
						ModInput modInput = new ModInput;

						CF_XML_Attribute attrib = null;

						attrib = inputs[i].GetAttribute("name");
						if (attrib)
							modInput.Name = attrib.ValueAsString();

						attrib = inputs[i].GetAttribute("loc");
						if (attrib)
							modInput.Localization = attrib.ValueAsString();

						attrib = inputs[i].GetAttribute("visible");
						if (attrib)
							modInput.Visible = attrib.ValueAsBool();
						else
							modInput.Visible = true;

						m_CF_ModInputs.Insert(modInput);
					}
				}
			}
			
			LoadData();

			if (ClassName() == "ModStructure" && !CF_OnLoad(m_CF_Name))
			{
				OnLoad(m_CF_Name);
			}
		}
	}

	array<ref ModInput> GetModInputs()
	{
		return m_CF_ModInputs;
	}

	JsonDataCredits GetCredits()
	{
		return m_CF_Credits;
	}

	string GetName()
	{
		return m_CF_Name;
	}

	string GetModPath()
	{
		return m_ModPath;
	}

	override string GetModName()
	{
		return m_ModName;
	}

	override string GetModLogo()
	{
		return m_ModLogo;
	}

	override string GetModLogoSmall()
	{
		return m_ModLogoSmall;
	}

	override string GetModLogoOver()
	{
		return m_ModLogoOver;
	}

	override string GetModActionURL()
	{
		return m_ModActionURL;
	}

	override string GetModToltip()
	{
		return m_ModTooltip;
	}

	override string GetModOverview()
	{
		return m_ModOverview;
	}

	string GetModVersion()
	{
		return m_CF_ModVersion;
	}

	int GetStorageVersion()
	{
		return m_CF_StorageVersion;
	}

	protected void SetStorageVersion(int version)
	{
		m_CF_StorageVersion = version;
	}

	bool HasModStorage()
	{
		return m_CF_StorageVersion > 0;
	}

	override string GetDebugName()
	{
		string str = super.GetDebugName();

		str += ", GetName=" + GetName();
		str += ", GetModPath=" + GetModPath();
		str += ", GetModName=" + GetModName();
		str += ", GetModLogo=" + GetModLogo();
		str += ", GetModLogoSmall=" + GetModLogoSmall();
		str += ", GetModLogoOver=" + GetModLogoOver();
		str += ", GetModActionURL=" + GetModActionURL();
		str += ", GetModToltip=" + GetModToltip();
		str += ", GetModOverview=" + GetModOverview();
		str += ", GetModVersion=" + GetModVersion();
		str += ", GetStorageVersion=" + GetStorageVersion();
		str += ", HasModStorage=" + HasModStorage();

		return str;
	}
};
