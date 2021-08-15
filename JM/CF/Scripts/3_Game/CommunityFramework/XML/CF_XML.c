class CF_XML
{
	static void _Cleanup()
	{
	}

	static CF_XML_Reader Open(string path)
	{
		CF_XML_Reader reader = new CF_XML_Reader();

		FileHandle fileHandle = OpenFile(path, FileMode.READ);

		string lineContent;
		while (FGets(fileHandle, lineContent) >= 0)
			reader.AddLine(lineContent);

		CloseFile(fileHandle);

		return reader;
	}

	static bool ReadDocument(string file, out CF_XML_Document document)
	{
		if (!document)
			document = new CF_XML_Document();

		return document.Read(Open(file));
	}

	static void Read(string file, notnull CF_XML_Callback callback)
	{
		Process(Open(file), callback);
	}

	static void ReadAsync(string file, notnull CF_XML_Callback callback)
	{
		thread Process(Open(file), callback);
	}

	static void Process(CF_XML_Reader reader, CF_XML_Callback callback)
	{
		CF_XML_Document document = new CF_XML_Document();

		callback.OnStart(document);

		bool success = false;
		if (document && reader)
		{
			success = document.Read(reader);
		}

		if (success)
		{
			callback.OnSuccess(document);
		}
		else
		{
			callback.OnFailure(document);
		}
	}
};

static CF_XML GetXMLApi()
{
	return CF.XML;
}