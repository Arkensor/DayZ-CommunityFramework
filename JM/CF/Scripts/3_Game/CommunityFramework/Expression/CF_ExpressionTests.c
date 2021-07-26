//TODO: Automate into a framework for other modders to use for their own testing
class CF_ExpressionTests
{
	private string _current;
	private int _cpu;
	private int _failed;

	private void CF_ExpressionTests()
	{
	}

	static void Perform()
	{
		CF_ExpressionTests tests = new CF_ExpressionTests();
		tests._Perform();
	}

	static void PerformSingle( string test )
	{
		CF_ExpressionTests tests = new CF_ExpressionTests();
		tests.PerformTest( test );
	}

	protected void Setup( inout array< string > tests )
	{
		tests.Insert("TestMultiplication_1");
		tests.Insert("TestDivision_1");
		tests.Insert("TestAddition_1");
		tests.Insert("TestSubtraction_1");
		
		tests.Insert("TestVariable_1");
		
		tests.Insert("TestFunction_1");
		tests.Insert("TestFunction_2");
		tests.Insert("TestFunction_3");
		
		tests.Insert("TestBrackets_1");
		
		tests.Insert("TestOrderOfOperations_1");
		tests.Insert("TestOrderOfOperations_2");
		
		tests.Insert("TestSound_1");
		tests.Insert("TestSound_2");
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

	private void _assert( float expectedNum, float actualNum, string expectedRPN, string actualRPN )
	{
		int time = TickCount( _cpu );
		string info = "Test \"" + _current + "\" took " + time + " ticks to execute.";

		if ( expectedNum != actualNum || expectedRPN != actualRPN )
		{
			Print( "  Expected Result: " + expectedNum );
			Print( "  Actual Result: " + actualNum );
			
			Print( "  Expected RPN: " + expectedRPN );
			Print( "  Actual RPN: " + actualRPN );
			
			info = "FAILED: " + info;
			
			_failed++;
		} else
		{
			Print( "  Result: " + actualNum );
			Print( "  RPN: " + actualRPN );
			
			info = "PASSED: " + info;
		}
		
		Print( "" + info );
		Print( "" );
	}
	
	void TestMultiplication_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "5 * 5";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 5 * 5;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 5 *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestDivision_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "5 / 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 5 / 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 2 /";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestAddition_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "5 + 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 5 + 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 2 +";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestSubtraction_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "5 - 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 5 - 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 2 -";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestVariable_1()
	{
		map< string, float > variables = new map< string, float >();
		variables["speed"] = 45;
		
		string expr = "speed * 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = variables["speed"] * 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "speed 2 *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestFunction_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "4 factor [0, 5]";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = Math.Interpolate(4, 0, 5, 0, 1);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "4 factor [0, 5]";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestFunction_2()
	{
		map< string, float > variables = new map< string, float >();
		variables["angle"] = 45;
		variables["pi"] = Math.PI;
		variables["toRad"] = Math.DEG2RAD;
		variables["toDeg"] = Math.RAD2DEG;
		
		string expr = "(angle * toRad) cos";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = Math.Cos(variables["angle"] * Math.DEG2RAD);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "angle toRad * cos";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestFunction_3()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "4 * cos(3.14159265359)";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_MathExpression);
		
		float expectedNum = 4 * Math.Cos(3.14159265359);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "4 3.14159265359 cos *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestFunction_4()
	{
		map< string, float > variables = new map< string, float >();
		variables["test"] = 2;
		
		string expr = "5 * factor(test, 0, 5)";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_MathExpression);
		
		float expectedNum = 5 * Math.Interpolate(variables["test"], 0, 5, 0, 1);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 test factor [0, 5] *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestBrackets_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "3 * (4 - 2) * 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 3 * (4 - 2) * 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "3 4 2 - 2 * *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestOrderOfOperations_1()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "2 + 5 * 5 + 2";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 2 + 5 * 5 + 2;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "2 5 5 * 2 + +";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestOrderOfOperations_2()
	{
		map< string, float > variables = new map< string, float >();
		
		string expr = "5 * 5 - 8 * 8";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 5 * 5 - 8 * 8;
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "5 5 * 8 8 * -";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestSound_1()
	{
		map< string, float > variables = new map< string, float >();
		
		variables["rpm"] = 7000;
		variables["doors"] = 0;
		variables["campos"] = 0;
		variables["engineOn"] = 1;
		
		string expr = "0.75 * 1 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200)]) * ((1 - 0.25*doors) max campos) * (rpm factor[4800,6200])";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 0.75 * 1 * (0.7 + 0.3 * Math.Interpolate( variables["speed"], 10, 60, 0, 1 ) ) * variables["engineOn"] * 1 * Math.Interpolate(850 + ((variables["rpm"] - 850)/(8000/5600)), (((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200), 0, 1) * (Math.Max(1 - 0.25*variables["doors"], variables["campos"]) * Math.Interpolate(variables["rpm"], 4800,6200, 0, 1);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "0.75 1 0.7 0.3 speed factor [10, 60] * + engineOn 1 850 rpm 850 - 8000 5600 / / + factor [3325, 4025] 1 0.25 doors * - campos max rpm factor [4800, 6200] * * * * * * *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
	
	void TestSound_2()
	{
		map< string, float > variables = new map< string, float >();
		
		variables["rpm"] = 1100;
		variables["doors"] = 0;
		variables["campos"] = 0;
		variables["engineOn"] = 1;
		
		string expr = "0.75 * 1 * engineOn * 0.4 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((850+1200)/2) + 2.5*50),(((850+1200)/2) - 50)]) * ((1 - 0.25*doors) max campos)";
		CF_Expression test = CF_ExpressionVM.Create(expr, CF_SQFExpression);
		
		float expectedNum = 0.75 * 1 * variables["engineOn"] * 0.4 * Math.Interpolate(850 +((variables["rpm"] - 850)/(8000/5600)),(((850+1200)/2) - 50), (((850+1200)/2) + 2.5*50),0, 1) * Math.Max((1 - 0.25 * variables["doors"]), variables["campos"]);
		float actualNum = test.CompileEvaluateTest(variables, true);

		string expectedRPN = "0.75 1 engineOn 0.4 850 rpm 850 - 8000 5600 / / + factor [975, 1150] 1 0.25 doors * - campos max * * * * *";
		string actualRPN = test.ToRPN(true);

		_assert( expectedNum, actualNum, expectedRPN, actualRPN );
	}
};