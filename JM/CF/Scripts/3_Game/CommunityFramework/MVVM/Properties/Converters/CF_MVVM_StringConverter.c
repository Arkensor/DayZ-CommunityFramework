class CF_MVVM_StringConverter
{
	static bool Get(CF_Model_Base model, string variable, out string value)
	{
		CF_Trace trace(null, "CF_MVVM_StringConverter::Get", "" + model, variable);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool;
				EnScript.GetClassVar(model, variable, 0, _bool);
				value = _bool.ToString();
				return true;
			case CF_MVVM_PropertyType.INT:
				int _int;
				EnScript.GetClassVar(model, variable, 0, _int);
				value = _int.ToString();
				return true;
			case CF_MVVM_PropertyType.FLOAT:
				float _float;
				EnScript.GetClassVar(model, variable, 0, _float);
				value = _float.ToString();
				return true;
			case CF_MVVM_PropertyType.VECTOR:
				vector _vector;
				EnScript.GetClassVar(model, variable, 0, _vector);
				value = _vector.ToString();
				return true;
			case CF_MVVM_PropertyType.STRING:
				EnScript.GetClassVar(model, variable, 0, value);
				return true;
			case CF_MVVM_PropertyType.CLASS:
				Class _class;
				EnScript.GetClassVar(model, variable, 0, _class);
				value = "" + _class;
				return true;
		}

		return false;
	}

	static bool Set(CF_Model_Base model, string variable, string value)
	{
		CF_Trace trace(null, "CF_MVVM_StringConverter::Set", "" + model, variable, "" + value);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool = CF.StringToBool(value);
				EnScript.SetClassVar(model, variable, 0, _bool);
				return true;
			case CF_MVVM_PropertyType.INT:
				int _int = value.ToInt();
				EnScript.SetClassVar(model, variable, 0, _int);
				return true;
			case CF_MVVM_PropertyType.FLOAT:
				float _float = value.ToFloat();
				EnScript.SetClassVar(model, variable, 0, _float);
				return true;
			case CF_MVVM_PropertyType.VECTOR:
				vector _vector = value.ToVector();
				EnScript.SetClassVar(model, variable, 0, _vector);
				return true;
			case CF_MVVM_PropertyType.STRING:
				EnScript.SetClassVar(model, variable, 0, value);
				return true;
			case CF_MVVM_PropertyType.CLASS:
				return false;
		}

		return false;
	}
};