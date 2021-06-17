class CF_MVVM_BoolConverter
{
	static bool Get(CF_Model_Base model, string variable, out bool value)
	{
		CF_Trace trace(null, "CF_MVVM_BoolConverter::Get", "" + model, variable);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool;
				EnScript.GetClassVar(model, variable, 0, _bool);
				value = _bool;
				return true;
			case CF_MVVM_PropertyType.INT:
				int _int;
				EnScript.GetClassVar(model, variable, 0, _int);
				value = _int;
				return true;
			case CF_MVVM_PropertyType.FLOAT:
				float _float;
				EnScript.GetClassVar(model, variable, 0, _float);
				value = _float;
				return true;
			case CF_MVVM_PropertyType.VECTOR:
				return false;
			case CF_MVVM_PropertyType.STRING:
				string _string;
				EnScript.GetClassVar(model, variable, 0, _string);
				value = CF.StringToBool(_string);
				return true;
			case CF_MVVM_PropertyType.CLASS:
				return false;
		}

		return false;
	}

	static bool Set(CF_Model_Base model, string variable, bool value)
	{
		CF_Trace trace(null, "CF_MVVM_BoolConverter::Set", "" + model, variable, "" + value);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool = value;
				EnScript.SetClassVar(model, variable, 0, _bool);
				return true;
			case CF_MVVM_PropertyType.INT:
				int _int = value;
				EnScript.SetClassVar(model, variable, 0, _int);
				return true;
			case CF_MVVM_PropertyType.FLOAT:
				float _float = value;
				EnScript.SetClassVar(model, variable, 0, _float);
				return true;
			case CF_MVVM_PropertyType.VECTOR:
				return false;
			case CF_MVVM_PropertyType.STRING:
				string _string = "" + value;
				EnScript.SetClassVar(model, variable, 0, _string);
				return true;
			case CF_MVVM_PropertyType.CLASS:
				return false;
		}

		return false;
	}
};