class CF_IO : Managed
{
	ref CF_Stream m_Stream;

	void CF_IO(CF_Stream stream = null)
	{
		m_Stream = stream;
	}

	void SetStream(CF_Stream stream)
	{
		m_Stream = stream;
	}

	bool IsValid()
	{
		if (!m_Stream) return false;

		return m_Stream.IsValid();
	}

	bool IsRead()
	{
		return false;
	}

	bool IsWrite()
	{
		return false;
	}

	/**
	 * Write a byte
	 */
	void WriteByte(CF_Byte value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write an array of bytes
	 */
	void WriteBytes(array<CF_Byte> bytes)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write an ascii character
	 */
	void WriteChar(string value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a bool
	 */
	void WriteBool(bool value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a short int
	 */
	void WriteShort(int value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write an int
	 */
	void WriteInt(int value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a float
	 */
	void WriteFloat(float value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a vector
	 */
	void WriteVector(vector value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a string
	 */
	void WriteString(string value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a string line
	 */
	void WriteLine(string value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * Write a null terminated string
	 */
	void WriteCString(string value)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * ReadByte a byte
	 */
	CF_Byte ReadByte()
	{
		CF_Log.Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadByte an array of byte
	 */
	array<CF_Byte> ReadBytes(int count)
	{
		CF_Log.Error("Not implemented.");
		return null;
	}

	/**
	 * ReadByte an array of byte
	 */
	void ReadBytes(int count, inout array<CF_Byte> bytes)
	{
		CF_Log.Error("Not implemented.");
	}

	/**
	 * ReadChar an ascii character
	 */
	string ReadChar()
	{
		CF_Log.Error("Not implemented.");
		return "";
	}

	/**
	 * ReadBool a bool
	 */
	bool ReadBool()
	{
		CF_Log.Error("Not implemented.");
		return false;
	}

	/**
	 * Read a short int
	 */
	int ReadShort()
	{
		CF_Log.Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadInt a int
	 */
	int ReadInt()
	{
		CF_Log.Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadFloat a float
	 */
	float ReadFloat()
	{
		CF_Log.Error("Not implemented.");
		return 0;
	}

	/**
	 * ReadVector a vector
	 */
	vector ReadVector()
	{
		CF_Log.Error("Not implemented.");
		return "0 0 0";
	}

	/**
	 * ReadString a string
	 */
	string ReadString()
	{
		CF_Log.Error("Not implemented.");
		return "";
	}

	/**
	 * ReadLine a line ended with '\n'
	 */
	string ReadLine()
	{
		CF_Log.Error("Not implemented.");
		return "";
	}

	/**
	 * ReadByte a null terminated string
	 */
	string ReadCString()
	{
		CF_Log.Error("Not implemented.");
		return "";
	}

	bool EOF()
	{
		if (!m_Stream) return true;
		
		return m_Stream.m_Position >= m_Stream.m_Size;
	}

	int Position()
	{
		if (!m_Stream) return 0;
		
		return m_Stream.m_Position;
	}

	int Length()
	{
		if (!m_Stream) return 0;
		
		return m_Stream.m_Size;
	}

	void Seek(int num, CF_SeekOrigin origin = CF_SeekOrigin.CURRENT)
	{
		if (!m_Stream) return;

		m_Stream.Seek(num, origin);
	}
	
	void Close()
	{
		m_Stream.Close();
		m_Stream = null;
	}

	override string GetDebugName()
	{
		string str = "[" + ClassName() + "] ";

		if (m_Stream) str += m_Stream.GetDebugName();
		else str += "NULL";

		return str;
	}
};
