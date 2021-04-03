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

	static void PerformSingle(string test)
	{
		CF_ModStorage_Test tests = new CF_ModStorage_Test();
		tests.PerformTest(test);
	}

	protected void Setup(inout array<string> tests)
	{
		tests.Insert("TestFloat");
		tests.Insert("TestBool");
		tests.Insert("TestInt");
		tests.Insert("TestVector");
		tests.Insert("TestString");
		tests.Insert("TestClass");
		tests.Insert("TestArrayString");
		tests.Insert("TestArrayClass");
		tests.Insert("TestMultiple");
	}

	private void _Perform()
	{
		Print("Starting tests");

		array<string> tests = new array<string>();
		Setup(tests);

		_failed = 0;

		int start = TickCount(0);

		for (int i = 0; i < tests.Count(); i++)
			PerformTest(tests[i]);

		int time = TickCount(start);

		Print("\n");

		if (_failed == 0)
		{
			Print("Success. All " + tests.Count() + " passed!");
		}
		else
		{
			Print("Tests failed. " + (tests.Count() - _failed) + "/" + tests.Count() + " passed.");
		}
	}

	private void PerformTest(string method)
	{
		Print("\n");
		Print("Running test \"" + method + "\"");

		_current = method;

		_cpu = TickCount(0);

		GetGame().GameScript.CallFunction(this, _current, null, null);
	}

	private void _assert(string expected, string actual)
	{
		int time = TickCount(_cpu);
		string info = "Test \"" + _current + "\" took " + time + " ticks to execute.";

		Print("  Expected Result: " + expected);
		Print("  Actual Result: " + actual);

		if (expected != actual)
		{
			//Print( "  Expected Result: " + expected );
			//Print( "  Actual Result: " + actual );

			info = "FAILED: " + info;

			_failed++;
		}
		else
		{
			info = "PASSED: " + info;
		}

		Print("" + info);
		Print("");
	}
	
	void ModLoadSave(CF_ModStorage mod_in, out CF_ModStorage mod_out)
	{
		ScriptReadWriteContext rw = new ScriptReadWriteContext();

		mod_in.Save(rw.GetWriteContext());
		
		ParamsReadContext ctx = rw.GetReadContext();
		string mod_name;
		ctx.Read(mod_name);
		
		mod_out = new CF_ModStorage(null);
		mod_out.Load(ctx, -1);
	}

	void TestFloat()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		float in_value = 2541.01;
		string expected = "" + in_value;
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		float out_value;
		mod_out.Read(out_value);
		string actual = "" + out_value;

		_assert(expected, actual);
	}

	void TestBool()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		bool in_value = true;
		string expected = "" + in_value;
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		bool out_value;
		mod_out.Read(out_value);
		string actual = "" + out_value;

		_assert(expected, actual);
	}

	void TestInt()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		int in_value = 12;
		string expected = "" + in_value;
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		int out_value;
		mod_out.Read(out_value);
		string actual = "" + out_value;

		_assert(expected, actual);
	}

	void TestVector()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		vector in_value = "3 2.051 51.583";
		string expected = "" + in_value;
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		vector out_value;
		mod_out.Read(out_value);
		string actual = "" + out_value;

		_assert(expected, actual);
	}

	void TestString()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		string in_value = "CF-Test Arkensor";
		string expected = "" + in_value;
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		string out_value;
		mod_out.Read(out_value);
		string actual = "" + out_value;

		_assert(expected, actual);
	}

	void TestClass()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		CF_ModStorage_Test_Class_B in_value = new CF_ModStorage_Test_Class_B("jacob", new CF_ModStorage_Test_Class_A(178));

		string expected = CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(in_value);
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		int lineNumber;
		Print(ThreadFunction(this, "_Perform", 100, lineNumber));

		CF_ModStorage_Test_Class_B out_value = new CF_ModStorage_Test_Class_B("a", null);
		mod_out.Read(out_value);
		string actual = CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(out_value);

		_assert(expected, actual);
	}

	void TestArrayString()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		array<string> in_value = new array<string>();

		in_value.Insert("3rd December");
		in_value.Insert("meet you");
		in_value.Insert("on Namalsk");

		string expected = CF_ModStorage_DebugP<string>.DebugString(in_value);
		mod_in.Write(in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		array<string> out_value = new array<string>();
		mod_out.Read(out_value);
		string actual = CF_ModStorage_DebugP<string>.DebugString(out_value);

		_assert(expected, actual);
	}

	void TestArrayClass()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		array<ref CF_ModStorage_Test_Class_B> in_value = new array<ref CF_ModStorage_Test_Class_B>();

		in_value.Insert(new CF_ModStorage_Test_Class_B("arkensor", new CF_ModStorage_Test_Class_A(1768)));
		in_value.Insert(new CF_ModStorage_Test_Class_B("tyler", new CF_ModStorage_Test_Class_A(1278)));
		in_value.Insert(new CF_ModStorage_Test_Class_B("paul", new CF_ModStorage_Test_Class_A(278)));

		string expected = CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(in_value);
		CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Write(mod_in, in_value);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		array<ref CF_ModStorage_Test_Class_B> out_value = new array<ref CF_ModStorage_Test_Class_B>();
		CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Read(mod_out, out_value);		
		string actual = CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(out_value);

		_assert(expected, actual);
	}	

	void TestMultiple()
	{
		CF_ModStorage mod_in = new CF_ModStorage(null);

		string expected = "";
		string actual = "";

		float in_value_float = 2541.01;
		expected += "" + in_value_float;
		mod_in.Write(in_value_float);

		bool in_value_bool = true;
		expected += "" + in_value_bool;
		mod_in.Write(in_value_bool);

		int in_value_int = 12;
		expected += "" + in_value_int;
		mod_in.Write(in_value_int);

		vector in_value_vector = "3 2.051 51.583";
		expected += "" + in_value_vector;
		mod_in.Write(in_value_vector);

		string in_value_string = "CF-Test Arkensor";
		expected += "" + in_value_string;
		mod_in.Write(in_value_string);

		CF_ModStorage_Test_Class_B in_value_cls = new CF_ModStorage_Test_Class_B("jacob", new CF_ModStorage_Test_Class_A(178));

		expected += CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(in_value_cls);
		mod_in.Write(in_value_cls);

		array<string> in_value_str_arr = new array<string>();

		in_value_str_arr.Insert("3rd December");
		in_value_str_arr.Insert("meet you");
		in_value_str_arr.Insert("on Namalsk");

		expected += CF_ModStorage_DebugP<string>.DebugString(in_value_str_arr);
		mod_in.Write(in_value_str_arr);

		array<ref CF_ModStorage_Test_Class_B> in_value_cls_arr = new array<ref CF_ModStorage_Test_Class_B>();

		in_value_cls_arr.Insert(new CF_ModStorage_Test_Class_B("arkensor", new CF_ModStorage_Test_Class_A(1768)));
		in_value_cls_arr.Insert(new CF_ModStorage_Test_Class_B("tyler", new CF_ModStorage_Test_Class_A(1278)));
		in_value_cls_arr.Insert(new CF_ModStorage_Test_Class_B("paul", new CF_ModStorage_Test_Class_A(278)));

		expected += CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(in_value_cls_arr);
		CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Write(mod_in, in_value_cls_arr);

		CF_ModStorage mod_out;
		ModLoadSave(mod_in, mod_out);

		float out_value_float;
		mod_out.Read(out_value_float);
		actual += "" + out_value_float;

		bool out_value_bool;
		mod_out.Read(out_value_bool);
		actual += "" + out_value_bool;

		int out_value_int;
		mod_out.Read(out_value_int);
		actual += "" + out_value_int;

		vector out_value_vector;
		mod_out.Read(out_value_vector);
		actual += "" + out_value_vector;

		string out_value_str;
		mod_out.Read(out_value_str);
		actual += "" + out_value_str;

		CF_ModStorage_Test_Class_B out_value_cls = new CF_ModStorage_Test_Class_B("a", null);
		mod_out.Read(out_value_cls);
		actual += CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(out_value_cls);

		array<string> out_value_str_arr = new array<string>();
		mod_out.Read(out_value_str_arr);
		actual += CF_ModStorage_DebugP<string>.DebugString(out_value_str_arr);

		array<ref CF_ModStorage_Test_Class_B> out_value_cls_arr = new array<ref CF_ModStorage_Test_Class_B>();
		CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Read(mod_out, out_value_cls_arr);		
		actual += CF_ModStorage_Debug<ref CF_ModStorage_Test_Class_B>.DebugString(out_value_cls_arr);

		_assert(expected, actual);
	}
};

class CF_ModStorage_DebugP<Class T>
{
	static string DebugString(array<T> data, int max = 3)
	{
		int num = max;
		if (data.Count() < max || max == -1)
			num = data.Count();

		string str = "count: " + data.Count();
		for (int i = 0; i < num; i++)
		{
			str += " " + i + ": " + data[i];
		}

		return str;
	}
};

class CF_ModStorage_Debug<Class T>
{
	static string DebugString(T data)
	{
		if (data)
			return data.DebugString();

		return "";
	}

	static string DebugString(array<ref T> data, int max = 3)
	{
		int num = max;
		if (data.Count() < max || max == -1)
			num = data.Count();

		string str = "count: " + data.Count();
		for (int i = 0; i < num; i++)
		{
			str += " " + i + ": " + data[i].DebugString();
		}

		return str;
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