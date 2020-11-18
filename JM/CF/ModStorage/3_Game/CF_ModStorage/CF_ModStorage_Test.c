//TODO: Automate into a framework for other modders to use for their own testing
class CF_ModStorage_Test
{
	private string _current;
	private int _cpu;
	private int _failed;

	private void CF_ModStorage_Test()
	{
	}

	static void Perform()
	{
		CF_ModStorage_Test tests = new CF_ModStorage_Test();
		tests._Perform();
	}

	static void PerformSingle( string test )
	{
		CF_ModStorage_Test tests = new CF_ModStorage_Test();
		tests.PerformTest( test );
	}

	protected void Setup( inout array< string > tests )
	{
		tests.Insert("TestFloat");
		tests.Insert("TestBool");
		tests.Insert("TestInt");
		tests.Insert("TestVector");
		tests.Insert("TestString");
		tests.Insert("TestClass");
	}

	private void _Perform()
	{
		Print( "Starting tests" );
		
		array< string > tests = new array< string >();
		Setup( tests );

		_failed = 0;

		int start = TickCount( 0 );

		for ( int i = 0; i < tests.Count(); i++ )
			PerformTest( tests[i] );

		int time = TickCount( start );
		
		Print("\n");

		if ( _failed == 0 )
		{
			Print( "Success. All " + tests.Count() + " passed!" );
		} else
		{
			Print( "Tests failed. " + ( tests.Count() - _failed ) + "/" + tests.Count() + " passed." );
		}
	}

	private void PerformTest( string method )
	{
		Print("\n");
		Print("Running test \"" + method + "\"");
		
		_current = method;

		_cpu = TickCount( 0 );

		GetGame().GameScript.CallFunction( this, _current, null, null );
	}

	private void _assert( string expected, string actual )
	{
		int time = TickCount( _cpu );
		string info = "Test \"" + _current + "\" took " + time + " ticks to execute.";

		Print( "  Expected Result: " + expected );
		Print( "  Actual Result: " + actual );
		
		if ( expected != actual )
		{
			//Print( "  Expected Result: " + expected );
			//Print( "  Actual Result: " + actual );
			
			info = "FAILED: " + info;
			
			_failed++;
		} else
		{
			info = "PASSED: " + info;
		}
		
		Print( "" + info );
		Print( "" );
	}
	
	void TestFloat()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		float in_value = 541.01;
		string expected = "" + in_value;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		float out_value;
		mod.Read(out_value);
		string actual = "" + out_value;
		
		_assert(expected, actual);
	}
	
	void TestBool()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		bool in_value = true;
		string expected = "" + in_value;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		bool out_value;
		mod.Read(out_value);
		string actual = "" + out_value;
		
		_assert(expected, actual);
	}
	
	void TestInt()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		int in_value = 12;
		string expected = "" + in_value;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		int out_value;
		mod.Read(out_value);
		string actual = "" + out_value;
		
		_assert(expected, actual);
	}
	
	void TestVector()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		vector in_value = "3 2.051 51.583";
		string expected = "" + in_value;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		vector out_value;
		mod.Read(out_value);
		string actual = "" + out_value;
		
		_assert(expected, actual);
	}
	
	void TestString()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		string in_value = "CF-Test Arkensor";
		string expected = "" + in_value;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		string out_value;
		mod.Read(out_value);
		string actual = "" + out_value;
		
		_assert(expected, actual);
	}
	
	void TestClass()
	{
		ModStorage mod = new ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		StatsEventMeasuresData in_value = new StatsEventMeasuresData();
		
		in_value.m_CharacterId = "3rd December, meet you on Namalsk";
		in_value.m_DistanceVehicle = 100;

		string expected = "m_CharacterId: " + in_value.m_CharacterId + " m_DistanceVehicle: " + in_value.m_DistanceVehicle;
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		StatsEventMeasuresData out_value = new StatsEventMeasuresData();
		mod.Read(out_value);
		string actual = "m_CharacterId: " + out_value.m_CharacterId + " m_DistanceVehicle: " + out_value.m_DistanceVehicle;
		
		_assert(expected, actual);
	}
};