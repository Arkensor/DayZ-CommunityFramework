typedef CF_XML_Document XMLDocument;

class CF_XML_Document : CF_XML_Element
{
	private CF_XML_Tag _currentTag;

	private ref CF_XML_Reader _reader;

	private autoptr map<string, string> _entities = new map<string, string>();

	void CF_XML_Document(CF_XML_Tag parent = NULL)
	{
		_entities.Insert("&quot;", "\"");
		_entities.Insert("&amp;", "&");
		_entities.Insert("&apos;", "\'");
		_entities.Insert("&lt;", "<");
		_entities.Insert("&gt;", ">");
	}

	override CF_XML_Tag CreateTag(string name)
	{
		if (_currentTag)
		{
			_currentTag = _currentTag.CreateTag(name);
		}
		else
		{
			_currentTag = super.CreateTag(name);
		}

		return _currentTag;
	}

	CF_XML_Document CopyDocument()
	{
		CF_XML_Document document = new CF_XML_Document(NULL);

		for (int i = 0; i < _tags.Count(); ++i)
		{
			document._tags.Insert(_tags[i].Copy(this));
		}

		return document;
	}

	private bool ReadAttribute()
	{
		if (!_currentTag)
		{
			_reader.Err("Attempting to read attribute when not in tag!");
			return false;
		}

		bool isQuoted;
		string name = _reader.GetWord();
		string eq = _reader.GetCharacter();
		string value = _reader.GetQuotedWord(isQuoted);

		if (eq != "=")
		{
			_reader.Err("Expected '=' for attribute, got: " + eq);
			return false;
		}

		CF_XML_Attribute attrib = _currentTag.CreateAttribute(name);
		attrib.SetValue(value);

		return true;
	}

	private bool PopTag()
	{
		if (!_currentTag)
			return true;

		if (_currentTag.GetParent())
			_currentTag = _currentTag.GetParent().GetParent();
		else
			_currentTag = NULL;

		return true;
	}

	private bool ReadTag()
	{
		string c = _reader.SkipWhitespace();
		string tagName = "";

		if (c == "<")
		{
			c = _reader.GetCharacter();
			if (c == "/")
			{
				tagName = _reader.GetWord();

				if (_currentTag == NULL)
				{
					_reader.Err("Unexpected closing tag: " + tagName);
				}

				c = _reader.GetCharacter();
				if (c != ">")
				{
					_reader.Err("Expected '>' for closing tag, got: " + c);
				}

				PopTag();

				return true;
			}

			if (c != "?")
				_reader.BackChar();

			tagName = _reader.GetWord();

			CreateTag(tagName);

			c = _reader.SkipWhitespace();
			while (c != "/" && c != "?" && c != ">")
			{
				c = _reader.BackChar();

				if (!ReadAttribute())
					return false;

				c = _reader.SkipWhitespace();
			}

			if (c == "/" || c == "?")
			{
				c = _reader.GetCharacter();
				if (c != ">")
				{
					_reader.Err("Expected '>' for inline closing tag, got: " + c);
				}

				PopTag();
			}
			else if (c == ">")
			{
				c = _reader.SkipWhitespace();
				if (c == "<")
				{
					c = _reader.BackChar();
					return true;
				}

				string content = c;

				while (true)
				{
					bool wasNewLine = _reader.WasNewLine();
					if (wasNewLine) c = _reader.SkipWhitespace();
					else c = _reader.GetCharacter();

					if (c != "<")
					{
						if (wasNewLine) content += "\n";
						content += c;
						continue;
					}
					
					c = _reader.GetCharacter();
					if (c != "/")
					{
						_reader.Err("Expected '/' for inline closing tag, got: " + c);
					}

					tagName = _reader.GetWord();
					
					if (tagName != _currentTag.GetName())
					{
						_reader.Err("Unexpected closing tag: " + tagName);
					}
				
					break;
				}

				foreach (string ent_key, string ent_val : _entities)
					content.Replace(ent_key, ent_val);

				_currentTag.GetContent().SetContent(content);

				c = _reader.GetCharacter();
				if (c != ">")
				{
					_reader.Err("Expected '>' for closing tag, got: " + c);
				}

				PopTag();

				return true;
			}
			else
			{
				_reader.Err("Expected '>' for opening element within tag, got: " + c);
			}

			return true;
		}

		// could just be non-tagged content.

		return true;
	}

	bool Read(CF_XML_Reader reader)
	{
		_reader = reader;

		while (!_reader.EOF())
		{
			if (!ReadTag())
			{
				delete _reader;
				return false;
			}
		}

		delete _reader;
		return true;
	}

	void Save(string path)
	{
		ThreadWrite(path);
		//GetGame().GameScript.Call( this, "ThreadWrite", path );
	}

	private void ThreadWrite(string path)
	{
		FileHandle handle = OpenFile(path, FileMode.WRITE);
		if (handle != 0)
		{
			OnWrite(handle, 0);
			CloseFile(handle);
		}
	}
};