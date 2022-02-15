typedef CF_XML_Attribute XMLAttribute;

class CF_XML_Attribute : Managed
{
	private string _name;
	private string _value;

	private CF_XML_Tag _parentTag;

	void CF_XML_Attribute(CF_XML_Tag parent, string name)
	{
		_parentTag = parent;
		_name = name;
		_value = "";
	}

	CF_XML_Attribute Copy(CF_XML_Tag parent = NULL)
	{
		CF_XML_Attribute element = new CF_XML_Attribute(parent, _name);

		element._value = _value;

		return element;
	}

	string GetName()
	{
		return _name;
	}

	void SetValue(string value)
	{
		_value = value;
	}

	void SetValue(bool value)
	{
		if (value)
		{
			_value = "true";
		}
		else
		{
			_value = "false";
		}
	}

	void SetValue(int value)
	{
		_value = "" + value;
	}

	void SetValue(float value)
	{
		_value = "" + value;
	}

	void SetValue(vector value)
	{
		_value = "" + value[0] + " " + value[1] + " " + value[2];
	}

	string GetValue()
	{
		return _value;
	}

	string ValueAsString()
	{
		return _value;
	}

	bool ValueAsBool()
	{
		if (_value == "true")
			return true;

		return false;
	}

	int ValueAsInt()
	{
		return _value.ToInt();
	}

	float ValueAsFloat()
	{
		return _value.ToFloat();
	}

	vector ValueAsVector()
	{
		array<string> tokens = new array<string>;
		_value.Split(" ", tokens);

		return Vector(tokens[0].ToFloat(), tokens[1].ToFloat(), tokens[2].ToFloat());
	}

	CF_XML_Tag GetParent()
	{
		return _parentTag;
	}

	void Debug(int level = 0)
	{
		string indent = CF_Indent(level);
		CF_Log.Info(indent + " name=" + _name + " value=" + _value);
	}

	void OnWrite(FileHandle handle, int depth)
	{
		FPrint(handle, _name);
		FPrint(handle, "=\"");
		FPrint(handle, _value);
		FPrint(handle, "\" ");
	}
};