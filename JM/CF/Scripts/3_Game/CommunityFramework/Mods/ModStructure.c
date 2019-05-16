modded class ModStructure
{
	protected ref JsonDataCredits m_Credits;
	
	protected string m_Version;
	
	override void LoadData()
	{
		super.LoadData();

		if ( GetGame().ConfigIsExisting( m_ModPath ) )
		{
			GetDebugging().Log( "Checking mod: " + m_ModName, "JM_CF_Mods" );
			
			if ( GetGame().ConfigIsExisting( m_ModPath + " creditsJson" ) )
			{
				GetDebugging().Log( "	Found JSON Credits", "JM_CF_Mods" );
				
				string creditsPath;
				GetGame().ConfigGetText( m_ModPath + " creditsJson", creditsPath );

				JsonFileLoader<ref JsonDataCredits>.JsonLoadFile( creditsPath, m_Credits );
			} else if ( GetGame().ConfigIsExisting( m_ModPath + " credits" ) )
			{
				GetDebugging().Log( "	Using Raw Credits", "JM_CF_Mods" );
				
				string credits = "";

				m_Credits = new ref JsonDataCredits;
				m_Credits.Departments = new array< ref JsonDataCreditsDepartment >;

				GetGame().ConfigGetText( m_ModPath + " credits", credits );

				ref JsonDataCreditsDepartment mod_department_header = new JsonDataCreditsDepartment;
				mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
				mod_department_header.DepartmentName = "				" + m_ModName;

				bool hasAuthor = GetGame().ConfigIsExisting( m_ModPath + " author" );
				GetDebugging().Log( "	Has author: " + hasAuthor, "JM_CF_Mods" );
				if ( hasAuthor )
				{
					string author = "";
					
					ref JsonDataCreditsSection mod_section_modheader_author = new JsonDataCreditsSection;
					mod_section_modheader_author.SectionLines = new array<string>;
					mod_section_modheader_author.SectionName = ( "Author" );
					
					GetGame().ConfigGetText( m_ModPath + " author", author );
					
					mod_section_modheader_author.SectionLines.Insert( author );
					
					mod_department_header.Sections.Insert( mod_section_modheader_author );
				}
				
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

				m_Credits.Departments.Insert( mod_department_header );
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
			
			GetDebugging().Log( "	Mod version is " + m_Version, "JM_CF_Mods" );
		}
	}
	
	ref JsonDataCredits GetCredits()
	{
		return m_Credits;
	}

	string GetModPath()
	{
		return m_ModPath;
	}
	
	string GetModName()
	{
		return m_ModName;
	}
	
	string GetModLogo()
	{
		return m_ModLogo;
	}
	
	string GetModLogoSmall()
	{
		return m_ModLogoSmall;
	}
	
	string GetModLogoOver()
	{
		return m_ModLogoOver;
	}
	
	string GetModActionURL()
	{
		return m_ModActionURL;
	}
	
	string GetModToltip()
	{
		return m_ModTooltip;
	}
	
	string GetModOverview()
	{
		return m_ModOverview;
	}
}