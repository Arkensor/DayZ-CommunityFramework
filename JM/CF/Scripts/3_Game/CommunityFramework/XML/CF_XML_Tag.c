typedef CF_XML_Tag XMLTag;

class CF_XML_Tag : Managed
{
	private string _name;
	
	private autoptr map<string, ref CF_XML_Attribute> _attributes;
	
	private ref CF_XML_Element _element;
	
	private CF_XML_Element _parentElement;

	void CF_XML_Tag(CF_XML_Element parent, string name, bool isCopy = false)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3(this).Add(parent).Add(name).Add(isCopy);
#endif

		_attributes = new map<string, ref CF_XML_Attribute>;
		_parentElement = parent;
		_name = name;

		if (!isCopy)
			_element = new CF_XML_Element(this);
	}

	void ~CF_XML_Tag()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

		for (int i = 0; i < _attributes.Count(); ++i)
		{
			delete _attributes.GetElement(i);
		}

		delete _attributes;

		delete _element;
	}

	CF_XML_Tag Copy(CF_XML_Element parent = NULL)
	{
		CF_XML_Tag tag = new CF_XML_Tag(parent, _name);

		for (int i = 0; i < _attributes.Count(); ++i)
		{
			CF_XML_Attribute attrib = _attributes.GetElement(i).Copy(tag);
			tag._attributes.Insert(attrib.GetName(), attrib);
		}

		tag._element = _element.Copy(tag);

		return tag;
	}

	string GetName()
	{
		return _name;
	}

	CF_XML_Tag CreateTag(string name)
	{
		return _element.CreateTag(name);
	}

	array<CF_XML_Tag> GetTag(string type)
	{
		return _element.Get(type);
	}

	CF_XML_Attribute CreateAttribute(string name)
	{
		CF_XML_Attribute attrb = new CF_XML_Attribute(this, name);

		_attributes.Insert(name, attrb);

		return attrb;
	}

	CF_XML_Attribute GetAttribute(string name)
	{
		return _attributes.Get(name);
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
		for (int i = 0; i < _attributes.Count(); ++i)
		{
			_attributes.GetElement(i).Debug(level);
		}

		CF_Log.Info(indent + "Element:");
		_element.Debug(level + 1);
	}

	void OnWrite(FileHandle handle, int depth)
	{
		string indent = CF_XML_Indent(depth);

		FPrint(handle, indent);
		FPrint(handle, "<");
		FPrint(handle, _name);

		if (_attributes.Count() > 0)
		{
			FPrint(handle, " ");

			for (int i = 0; i < _attributes.Count(); ++i)
			{
				_attributes.GetElement(i).OnWrite(handle, depth);
			}
		}

		if (_element.Count() > 0)
		{
			FPrint(handle, ">\n");

			_element.OnWrite(handle, depth + 1);

			FPrint(handle, indent);
			FPrint(handle, "<");
			FPrint(handle, _name);
			FPrint(handle, " ");
		}
		else if (_attributes.Count() == 0)
		{
			FPrint(handle, " ");
		}

		FPrint(handle, "/>\n");
	}
};