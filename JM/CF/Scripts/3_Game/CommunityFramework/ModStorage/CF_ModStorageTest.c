//TODO: Automate into a framework for other modders to use for their own testing
#ifdef CF_MODSTORAGE_TEST
class CF_ModStorageTest
{
	private string _current;
	private int _cpu;
	private int _failed;

	private void CF_ModStorageTest()
	{
	}

	static void Perform()
	{
		CF_ModStorageTest tests = new CF_ModStorageTest();
		tests._Perform();
	}

	static void PerformSingle(string test)
	{
		CF_ModStorageTest tests = new CF_ModStorageTest();
		tests.PerformTest(test);
	}

	protected void Setup(inout array<string> tests)
	{
		tests.Insert("CreateEntity");
		tests.Insert("TestEntity");
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
	
	EntityAI object;
	
	void CreateEntity()
	{
		string objectType = "Apple";
		object = EntityAI.Cast(GetGame().CreateObject(objectType, "0 0 0"));
	}
	
	void TestEntity()
	{
		object.SetPosition("5 5 0");
		string prev = object.GetDebugName();

		ScriptReadWriteContext ctx = new ScriptReadWriteContext;
		
		object.OnStoreSave(ctx.GetWriteContext());
		object.OnStoreLoad(ctx.GetReadContext(), GetGame().SaveVersion());

		_assert(prev, object.GetDebugName());
	}
};
#endif
