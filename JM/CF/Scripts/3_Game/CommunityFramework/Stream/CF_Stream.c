class CF_Stream : Managed
{
	bool _ReadFile(string path)
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	bool _WriteFile(string path)
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	/**
	 * Write a byte
	 */
	void Write(byte value)
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
	 * Read a byte
	 */
	byte Read()
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

	void SetBytes(array<byte> bytes)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	array<byte> GetBytes()
	{
		/*CF.Log.*/Error("Not implemented.");
		return null;
	}
};
