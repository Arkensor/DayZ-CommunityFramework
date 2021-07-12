class CF_Stream : Managed
{
	bool File(string path, FileMode mode)
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	/**
	 * Write a byte
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
	 * Write a bool
	 */
	void WriteBool(bool value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write an int
	 */
	void WriteInt(int value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write a float
	 */
	void WriteFloat(float value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write a vector
	 */
	void WriteVector(vector value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write a string
	 */
	void WriteString(string value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * Write a null terminated string
	 */
	void WriteCString(string value)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	/**
	 * ReadByte a byte
	 */
	int ReadByte()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadByte an ascii character
	 */
	string ReadChar()
	{
		/*CF.Log.*/Error("Not implemented.");
		return "";
	}

	/**
	 * ReadByte a bool
	 */
	bool ReadBool()
	{
		/*CF.Log.*/Error("Not implemented.");
		return false;
	}

	/**
	 * ReadByte a int
	 */
	int ReadInt()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadByte a float
	 */
	float ReadFloat()
	{
		/*CF.Log.*/Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadByte a vector
	 */
	vector ReadVector()
	{
		/*CF.Log.*/Error("Not implemented.");
		return "0 0 0";
	}

	/**
	 * ReadByte a string
	 */
	string ReadString()
	{
		/*CF.Log.*/Error("Not implemented.");
		return "";
	}

	/**
	 * ReadByte a null terminated string
	 */
	string ReadCString()
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

	void Seek(int num, CF_SeekOrigin origin = CF_SeekOrigin.CURRENT)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	void SetBytes(array<int> bytes)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	array<int> GetBytes()
	{
		/*CF.Log.*/Error("Not implemented.");
		return null;
	}
};
