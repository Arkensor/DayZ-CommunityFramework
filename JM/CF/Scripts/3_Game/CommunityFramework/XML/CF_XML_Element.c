typedef CF_XML_Element XMLElement;

class CF_XML_Element : Managed
{
	protected autoptr array<autoptr CF_XML_Tag> _tags = new array<autoptr CF_XML_Tag>;
	
	protected CF_XML_Tag _parentTag;
	
	protected string _data;

	void CF_XML_Element(CF_XML_Tag parent = NULL)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this).Add(parent);
#endif

		_parentTag = parent;
	}

	void ~CF_XML_Element()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
	}

	CF_XML_Element Copy(CF_XML_Tag parent = NULL)
	{
		CF_XML_Element element = new CF_XML_Element(parent);

		for (int i = 0; i < _tags.Count(); ++i)
		{
			element._tags.Insert(_tags[i].Copy(element));
		}

		element._data = "" + _data;

		return element;
	}

	CF_XML_Tag CreateTag(string name)
	{
		CF_XML_Tag tag = new CF_XML_Tag(this, name);

		_tags.Insert(tag);

		return tag;
	}

	int Count()
	{
		return _tags.Count();
	}

	CF_XML_Tag Get(int index)
	{
		return _tags[index];
	}

	void Remove(CF_XML_Tag tag)
	{
		int index = _tags.Find(tag);
		if (index >= 0)
			_tags.Remove(index);
	}

	array<CF_XML_Tag> Get(string type)
	{
		array<CF_XML_Tag> tags = new array<CF_XML_Tag>;

		for (int i = 0; i < _tags.Count(); ++i)
		{
			if (_tags[i].GetName() == type)
			{
				tags.Insert(_tags[i]);
			}
		}

		return tags;
	}

	void SetContent(string data)
	{
		_data = data;
	}

	string GetContent()
	{
		return _data;
	}

	CF_XML_Tag GetParent()
	{
		return _parentTag;
	}

	void Debug(int level = 0)
	{
		string indent = CF_Indent(level);

		CF_Log.Info(indent + "Tags: count=" + _tags.Count());
		for (int i = 0; i < _tags.Count(); ++i)
		{
			_tags[i].Debug(level + 1);
		}
	}

	void OnWrite(FileHandle handle, int depth)
	{
		string indent = CF_XML_Indent(depth);

		FPrint(handle, _data);

		for (int i = 0; i < _tags.Count(); ++i)
		{
			_tags[i].OnWrite(handle, depth);
		}
	}
};