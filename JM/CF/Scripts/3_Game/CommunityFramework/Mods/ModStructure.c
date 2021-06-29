modded class ModStructure
{
	protected ref array< ref ModInput > m_ModInputs;

	protected ref JsonDataCredits m_Credits;
	
	protected string m_Version;

	protected int m_StorageVersion;

	protected string m_Name;

	protected ref CF_ModHash m_Hash;

	void ~ModStructure()
	{
		delete m_ModInputs;
	}

	/**
	 * Set the mod specific data in here
	 * 
	 * @param modName	The name of the loaded mod, retrieved from the CfgMods params array
	 * 
	 * @code
	override bool OnLoad( string modName )
	{
		if ( modName != "JM_CommunityFramework" )
			return super.OnLoad( modName );

		//! Set the storage version for this mod
		SetStorageVersion( 1 );

		return true;
	}
	 */
	bool OnLoad( string modName )
	{
		return false;
	}
	
	override void LoadData()
	{
		super.LoadData();

		m_ModInputs = new ref array< ref ModInput >;

		m_StorageVersion = 0;

		if ( GetGame().ConfigIsExisting( m_ModPath ) )
		{			
			GetGame().ConfigGetChildName( "CfgMods", m_ModIndex, m_Name );

			m_Hash = new CF_ModHash( m_Name );

			if ( !OnLoad( m_ModName ) )
			{
				//Print( "(Community-Framework) Notice: The mod '" + m_ModName + "' either does not override ModStructure::OnLoad or failed to load." );
			}

			//GetLogger().Log( "Checking mod: " + m_ModName, "JM_CF_Mods" );
			/*if ( GetGame().ConfigIsExisting( m_ModPath + " creditsJson" ) )
			{
				//GetLogger().Log( "	Found JSON Credits", "JM_CF_Mods" );
				
				string creditsPath;
				GetGame().ConfigGetText( m_ModPath + " creditsJson", creditsPath );
				
				Print(creditsPath);

				JsonFileLoader<ref JsonDataCredits>.JsonLoadFile( creditsPath, m_Credits );
			} else */
			if ( GetGame().ConfigIsExisting( m_ModPath + " credits" ) )
			{
				//GetLogger().Log( "	Using Raw Credits", "JM_CF_Mods" );
				
				string credits = "";

				m_Credits = new ref JsonDataCredits;
				m_Credits.Departments = new array< ref JsonDataCreditsDepartment >;

				ref JsonDataCreditsDepartment mod_department_header = new JsonDataCreditsDepartment;
				mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
				mod_department_header.DepartmentName = "				" + m_ModName;

				string author = "";
				bool hasAuthor = GetGame().ConfigIsExisting( m_ModPath + " author" );
				GetGame().ConfigGetText( m_ModPath + " author", author );

				//GetLogger().Log( "	Has author: " + hasAuthor, "JM_CF_Mods" );
				//GetLogger().Log( "	Author: " + author, "JM_CF_Mods" );
				if ( hasAuthor && author != "" )
				{
					ref JsonDataCreditsSection mod_section_modheader_author = new JsonDataCreditsSection;
					mod_section_modheader_author.SectionLines = new array<string>;
					mod_section_modheader_author.SectionName = ( "Author" );
					
					mod_section_modheader_author.SectionLines.Insert( author );
					
					mod_department_header.Sections.Insert( mod_section_modheader_author );
				}
				
				GetGame().ConfigGetText( m_ModPath + " credits", credits );
				//GetLogger().Log( "	Credits: " + credits, "JM_CF_Mods" );
				if ( credits != "" )
				{
					ref JsonDataCreditsSection mod_section_modheader = new JsonDataCreditsSection;
					mod_section_modheader.SectionLines = new array<string>;
					mod_section_modheader.SectionName = ( "Credits" );
					
					array<string> creditsArray = new array<string>;
					credits.Split(", ", creditsArray);
					foreach ( string credit: creditsArray )
					{
						mod_section_modheader.SectionLines.Insert( credit );
					}
					
					mod_department_header.Sections.Insert( mod_section_modheader );
				}

				m_Credits.Departments.Insert( mod_department_header );
			} else
			{
				m_Credits = new ref JsonDataCredits;
			}
			
			if ( GetGame().ConfigIsExisting( m_ModPath + " versionPath" ) )
			{
				string versionPath;
				GetGame().ConfigGetText( m_ModPath + " versionPath", versionPath );
				
				FileHandle file_handle = OpenFile( versionPath, FileMode.READ );
		
				while ( FGets( file_handle, m_Version ) > 0 )
					break;
		
				CloseFile( file_handle );
			} else if ( GetGame().ConfigIsExisting( m_ModPath + " version" ) )
			{
				GetGame().ConfigGetText( m_ModPath + " version", m_Version );
			}
			
			//GetLogger().Log( "	Mod version is " + m_Version, "JM_CF_Mods" );

			if ( GetGame().ConfigIsExisting( m_ModPath + " inputs" ) )
			{
				string inputPath;
				GetGame().ConfigGetText( m_ModPath + " inputs", inputPath );
				
				CF_XML_Document document;
				if ( inputPath != "" && CF.XML.ReadDocument( inputPath, document ) )
				{
					auto parent_tag = document.Get( "modded_inputs" )[0];
					if ( parent_tag )
						parent_tag = parent_tag.GetTag( "inputs" )[0];
					if ( parent_tag )
						parent_tag = parent_tag.GetTag( "actions" )[0];

					array< CF_XML_Tag > inputs = null;
					if ( !parent_tag )
						inputs = new array< CF_XML_Tag >();
					else
						inputs = parent_tag.GetTag( "input" );

					for ( int i = 0; i < inputs.Count(); i++ )
					{
						ref ModInput modInput = new ref ModInput;

						CF_XML_Attribute attrib = null;

						attrib = inputs[i].GetAttribute( "name" );
						if ( attrib )
							modInput.Name = attrib.ValueAsString();

						attrib = inputs[i].GetAttribute( "loc" );
						if ( attrib )
							modInput.Localization = attrib.ValueAsString();

						attrib = inputs[i].GetAttribute( "visible" );
						if ( attrib )
							modInput.Visible = attrib.ValueAsBool();
						else 
							modInput.Visible = true;

						m_ModInputs.Insert( modInput );
					}
				}
			}
		}
	}
	
	ref array< ref ModInput > GetModInputs()
	{
		return m_ModInputs;
	}

	ref JsonDataCredits GetCredits()
	{
		return m_Credits;
	}

	string GetName()
	{
		return m_Name;
	}

	CF_ModHash GetHash()
	{
		return m_Hash;
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
		return m_Version;
	}

	int GetStorageVersion()
	{
		return m_StorageVersion;
	}

	protected void SetStorageVersion( int version )
	{
		m_StorageVersion = version;
	}
};