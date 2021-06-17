class CF_MVVM_StringConverter
{
	static void Get(CF_Model_Base model, string variable, out string str)
	{
		CF_Trace trace(null, "CF_MVVM_StringConverter::Get", "" + model, variable);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool;
				EnScript.GetClassVar(model, variable, 0, _bool);
				str = _bool.ToString();
				break;
			case CF_MVVM_PropertyType.INT:
				int _int;
				EnScript.GetClassVar(model, variable, 0, _int);
				str = _int.ToString();
				break;
			case CF_MVVM_PropertyType.FLOAT:
				float _float;
				EnScript.GetClassVar(model, variable, 0, _float);
				str = _float.ToString();
				break;
			case CF_MVVM_PropertyType.VECTOR:
				vector _vector;
				EnScript.GetClassVar(model, variable, 0, _vector);
				str = _vector.ToString();
				break;
			case CF_MVVM_PropertyType.STRING:
				EnScript.GetClassVar(model, variable, 0, str);
				break;
			case CF_MVVM_PropertyType.CLASS:
				Class _class;
				EnScript.GetClassVar(model, variable, 0, _class);
				str = "" + _class;
				break;
		}
	}

	static void Set(CF_Model_Base model, string variable, string str)
	{
		CF_Trace trace(null, "CF_MVVM_StringConverter::Set", "" + model, variable, str);

		CF_MVVM_PropertyType type = CF.MVVM.GetPropertyType(model, variable);
		switch (type)
		{
			case CF_MVVM_PropertyType.BOOL:
				bool _bool = CF.StringToBool(str);
				EnScript.SetClassVar(model, variable, 0, _bool);
				break;
			case CF_MVVM_PropertyType.INT:
				int _int = str.ToInt();
				EnScript.SetClassVar(model, variable, 0, _int);
				break;
			case CF_MVVM_PropertyType.FLOAT:
				float _float = str.ToFloat();
				EnScript.SetClassVar(model, variable, 0, _float);
				break;
			case CF_MVVM_PropertyType.VECTOR:
				vector _vector = str.ToVector();
				EnScript.SetClassVar(model, variable, 0, _vector);
				break;
			case CF_MVVM_PropertyType.STRING:
				EnScript.SetClassVar(model, variable, 0, str);
				break;
			case CF_MVVM_PropertyType.CLASS:
				break;
		}
	}
};