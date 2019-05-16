modded class ModStructure
{
	protected ref JsonDataCredits m_Credits;
	
	protected string m_Version;
	
	override void LoadData()
	{
        super.LoadData();

		if ( GetGame().ConfigIsExisting( m_ModPath ) )
		{
            if ( GetGame().ConfigIsExisting( m_ModPath + " creditsJson" ) )
            {
                string creditsPath;
			    GetGame().ConfigGetText( m_ModPath + " creditsJson", creditsPath );

				JsonFileLoader<ref JsonDataCredits>.JsonLoadFile( creditsPath, m_Credits );
            } else if ( GetGame().ConfigIsExisting( m_ModPath + " credits" ) )
            {
                string credits = "";

                m_Credits = new ref JsonDataCredits;
                m_Credits.Departments = new array< ref JsonDataCreditsDepartment >;

			    GetGame().ConfigGetText( m_ModPath + " credits", credits );

                ref JsonDataCreditsDepartment mod_department_header = new JsonDataCreditsDepartment;
                mod_department_header.Sections = new array<ref JsonDataCreditsSection>;
                mod_department_header.DepartmentName = m_ModName;

                ref JsonDataCreditsSection mod_section_modheader = new JsonDataCreditsSection;
                mod_section_modheader.SectionLines = new array<string>;
                mod_section_modheader.SectionName = ("");
                mod_section_modheader.SectionLines.Insert( credits );
                mod_department_header.Sections.Insert(mod_section_modheader);

                m_Credits.Departments.Insert(mod_department_header);
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
		}
	}
	
	ref JsonDataCredits GetCredits()
	{
		return m_Credits;
	}
}