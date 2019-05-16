class ReadableInput
{
    string InputName;
    string DisplayName;

    void ReadableInput( string in, string dn )
    {
        InputName = in;
        DisplayName = dn;
    }
}

class ReadableMod
{
    string ModClassName;
    ref array< ref ReadableInput > Inputs;

    void ReadableMod( string name, ref array< ref ReadableInput > inps )
    {
        ModClassName = name;
        Inputs = inps;
    }
}

class ReadableInputs
{
    ref array< ref ReadableMod > Mods;

    void ReadableInputs()
    {
        Mods = new ref array< ref ReadableMod >;
    }

	static ref ReadableInputs Load()
	{
		ref ReadableInputs settings = new ReadableInputs();

		JsonFileLoader<ReadableInputs>.JsonLoadFile( "bin/inputs.json", settings );

        /*
        array< ref ReadableInput > inps = new array< ref ReadableInput >;
        
        inps.Insert( new ReadableInput( "UACOTModuleToggleCOT","Toggle COT" ) );
        inps.Insert( new ReadableInput( "UACOTModuleToggleMenu","Show Side Menu" ) );
        inps.Insert( new ReadableInput( "UACOTModuleCloseCOT","Close Side Menu" ) );
        inps.Insert( new ReadableInput( "UATeleportModuleTeleportCursor","Teleport To Cursor" ) );
        inps.Insert( new ReadableInput( "UACameraToolEnableCamera","Enable Freecam" ) );
        inps.Insert( new ReadableInput( "UACameraToolDisableCamera","Disable Freecam" ) );

        settings.Mods.Insert( new ReadableMod( "JM_CommunityOnlineTools", inps ) );

		JsonFileLoader<ReadableInputs>.JsonSaveFile( "$profile:Inputs.json", settings );
        */

		return settings;
	}
}

static ref ReadableInputs g_RInputs;

static ref ReadableInputs GetReadableInputs()
{
    if ( !g_RInputs )
    {
        g_RInputs = ReadableInputs.Load();
    }

    return g_RInputs;
}