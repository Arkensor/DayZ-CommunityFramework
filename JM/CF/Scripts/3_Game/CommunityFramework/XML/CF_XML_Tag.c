typedef CF_XML_Tag XMLTag;

class CF_XML_Tag : Managed
{
	private string _name;
	
	private autoptr array<ref CF_XML_Attribute> _attributes;
	
	private ref CF_XML_Element _element;
	
	private CF_XML_Element _parentElement;

	private bool _isProcessingInstruction;

	void CF_XML_Tag(CF_XML_Element parent, string name, bool isCopy = false, bool isProcessingInstruction = false)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3(this).Add(parent).Add(name).Add(isCopy);
#endif

		_attributes = new array<ref CF_XML_Attribute>;
		_parentElement = parent;
		_name = name;

		if (!isCopy)
			_element = new CF_XML_Element(this);

		_isProcessingInstruction = isProcessingInstruction;
	}

	void ~CF_XML_Tag()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

		foreach (CF_XML_Attribute attribute: _attributes)
		{
			delete attribute;
		}

		delete _attributes;

		delete _element;
	}

	CF_XML_Tag Copy(CF_XML_Element parent = NULL)
	{
		CF_XML_Tag tag = new CF_XML_Tag(parent, _name, true, _isProcessingInstruction);

		foreach (CF_XML_Attribute attribute: _attributes)
		{
			tag._attributes.Insert(attribute.Copy(tag));
		}

		tag._element = _element.Copy(tag);

		return tag;
	}

	string GetName()
	{
		return _name;
	}

	CF_XML_Tag CreateTag(string name, bool isProcessingInstruction = false)
	{
		return _element.CreateTag(name, isProcessingInstruction);
	}

	array<CF_XML_Tag> GetTag(string type)
	{
		return _element.Get(type);
	}

	CF_XML_Attribute CreateAttribute(string name)
	{
		CF_XML_Attribute attrb = new CF_XML_Attribute(this, name);

		_attributes.Insert(attrb);

		return attrb;
	}

	CF_XML_Attribute GetAttribute(string name)
	{
		foreach (CF_XML_Attribute attribute: _attributes)
		{
			if (attribute.GetName() == name)
				return attribute;
		}

		return null;
	}

	CF_XML_Element GetContent()
	{
		return _element;
	}

	CF_XML_Element GetParent()
	{
		return _parentElement;
	}

	void Debug(int level = 0)
	{
		string indent = CF_Indent(level);

		CF_Log.Info(indent + "Tag:");
		CF_Log.Info(indent + " name=" + _name);

		CF_Log.Info(indent + "Attributes: count=" + _attributes.Count());
		foreach (CF_XML_Attribute attribute: _attributes)
		{
			attribute.Debug(level);
		}

		CF_Log.Info(indent + "Element:");
		_element.Debug(level + 1);
	}

	void OnWrite(FileHandle handle, int depth)
	{
		string indent = CF_XML_Indent(depth);

		FPrint(handle, indent);
		FPrint(handle, "<");
		if (_isProcessingInstruction)
			FPrint(handle, "?");
		FPrint(handle, _name);

		if (_attributes.Count() > 0)
		{
			foreach (CF_XML_Attribute attribute: _attributes)
			{
				attribute.OnWrite(handle, depth);
			}
		}

		if (_element.Count() > 0 || _element.GetContent())
		{
			FPrint(handle, ">\n");

			_element.OnWrite(handle, depth + 1);

			FPrint(handle, indent);
			FPrint(handle, "</");
			FPrint(handle, _name);
			FPrint(handle, ">\n");
		}
		else
		{
			if (_isProcessingInstruction)
				FPrint(handle, "?>\n");
			else
				FPrint(handle, " />\n");
		}
	}
};