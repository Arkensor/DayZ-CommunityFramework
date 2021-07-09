class CF_Stream : Managed
{
	bool ReadFile(string path)
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	bool WriteFile(string path)
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	/**
	 * Write a signed byte (-127 - 127)
	 */
	void Write(int value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write an ascii character
	 */
	void WriteChar(string value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Read a signed byte (-127 - 127)
	 */
	int Read()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	/**
	 * Read an ascii character
	 */
	string ReadChar()
	{
		/*CF.Log.*/Error("Not implemented.");
		return "";
	}

	bool EOF()
	{
		/*CF.Log.*/Error("Not implemented.");
		return true;
	}

	int Position()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	int Length()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	void GoTo(int position)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	void Seek(int offset)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	array<int> GetByteArray()
	{
		/*CF.Log.*/Error("Not implemented.");
		return null;
	}
};