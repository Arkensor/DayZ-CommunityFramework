class CF_MVVM_VectorConverter
{
	static bool Get(CF_Model_Base model, string variable, out vector value)
	{
		CF_Trace trace(null, "CF_MVVM_VectorConverter::Get", "" + model, variable);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				return false;;
			case CF_MVVM_PropertyType.INT:
				return false;
			case CF_MVVM_PropertyType.FLOAT:
				return false;
			case CF_MVVM_PropertyType.VECTOR:
				EnScript.GetClassVar(model, variable, 0, value);
				return true;
			case CF_MVVM_PropertyType.STRING:
				string _string;
				EnScript.GetClassVar(model, variable, 0, _string);
				value = _string.ToVector();
				return true;
			case CF_MVVM_PropertyType.CLASS:
				return false;
		}

		return false;
	}

	static bool Set(CF_Model_Base model, string variable, vector value)
	{
		CF_Trace trace(null, "CF_MVVM_VectorConverter::Set", "" + model, variable, "" + value);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				return false;
			case CF_MVVM_PropertyType.INT:
				return false;
			case CF_MVVM_PropertyType.FLOAT:
				return false;
			case CF_MVVM_PropertyType.VECTOR:
				EnScript.SetClassVar(model, variable, 0, value);
				return true;
			case CF_MVVM_PropertyType.STRING:
				string _string = value.ToString();
				EnScript.SetClassVar(model, variable, 0, _string);
				return true;
			case CF_MVVM_PropertyType.CLASS:
				return false;
		}

		return false;
	}
};