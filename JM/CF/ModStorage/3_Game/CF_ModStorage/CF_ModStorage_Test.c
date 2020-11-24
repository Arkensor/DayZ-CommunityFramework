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
		tests.Insert("TestArrayString");
		tests.Insert("TestArrayClass");
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
		CF_ModStorage mod = new CF_ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		float in_value = 2541.01;
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
		CF_ModStorage mod = new CF_ModStorage(null);

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
		CF_ModStorage mod = new CF_ModStorage(null);

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
		CF_ModStorage mod = new CF_ModStorage(null);

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
		CF_ModStorage mod = new CF_ModStorage(null);

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
		CF_ModStorage mod = new CF_ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		CF_ModStorage_Test_Class_B in_value = new CF_ModStorage_Test_Class_B("jacob", new CF_ModStorage_Test_Class_A(178));

		string expected = in_value.DebugString();
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);
		
		int lineNumber;
		Print(ThreadFunction(this, "_Perform", 100, lineNumber));

		CF_ModStorage_Test_Class_B out_value = new CF_ModStorage_Test_Class_B("a", null);
		mod.Read(out_value);
		string actual = out_value.DebugString();
		
		_assert(expected, actual);
	}
	
	void TestArrayString()
	{
		CF_ModStorage mod = new CF_ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		array<string> in_value = new array<string>();
		
		in_value.Insert("3rd December");
		in_value.Insert("meet you");
		in_value.Insert("on Namalsk");

		string expected = "count: " + in_value.Count() + " 0: " + in_value[0] + " 1: " + in_value[1] + " 2: " + in_value[2];
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		array<string> out_value = new array<string>();
		mod.Read(out_value);
		string actual = "count: " + out_value.Count() + " 0: " + out_value[0] + " 1: " + out_value[1] + " 2: " + out_value[2];
		
		_assert(expected, actual);
	}
	
	void TestArrayClass()
	{
		CF_ModStorage mod = new CF_ModStorage(null);

		ScriptReadWriteContext rw = new ScriptReadWriteContext();
		
		array<ref CF_ModStorage_Test_Class_B> in_value = new array<ref CF_ModStorage_Test_Class_B>();
		
		in_value.Insert(new CF_ModStorage_Test_Class_B("arkensor", new CF_ModStorage_Test_Class_A(178)));
		in_value.Insert(new CF_ModStorage_Test_Class_B("tyler", new CF_ModStorage_Test_Class_A(178)));
		in_value.Insert(new CF_ModStorage_Test_Class_B("paul", new CF_ModStorage_Test_Class_A(178)));

		string expected = "count: " + in_value.Count() + " 0: " + in_value[0].DebugString() + " 1: " + in_value[1].DebugString() + " 2: " + in_value[2].DebugString();
		mod.Write(in_value);
		
		mod.Save(null, rw.GetWriteContext());
		mod.Load(null, rw.GetReadContext(), -1);

		array<ref CF_ModStorage_Test_Class_B> out_value = new array<ref CF_ModStorage_Test_Class_B>();
		mod.Read(out_value);
		string actual = "count: " + out_value.Count() + " 0: " + out_value[0].DebugString() + " 1: " + out_value[1].DebugString() + " 2: " + out_value[2].DebugString();
		
		_assert(expected, actual);
	}
};

class CF_ModStorage_Test_Class_A
{
	int val;
	
	void CF_ModStorage_Test_Class_A(int i)
	{
		val = i;
	}
};

class CF_ModStorage_Test_Class_B
{
	string name;
	ref CF_ModStorage_Test_Class_A value;
	
	void CF_ModStorage_Test_Class_B(string na, CF_ModStorage_Test_Class_A val)
	{
		name = na;
		value = val;
	}
	
	string DebugString()
	{
		return "(name: " + name + ", value.val: " + value.val + ")";
	}
};