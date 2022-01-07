/**
 * Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 3;

	protected ModStructure m_Mod;

	protected string m_ModName;
	protected int m_Version;
	protected ref CF_Stream m_Stream;

	void CF_ModStorage(ModStructure mod)
	{
		m_Mod = mod;
		m_Version = m_Mod.GetStorageVersion();
		m_ModName = m_Mod.GetName();
		m_Stream = null;
	}

	int GetVersion()
	{
		return m_Version;
	}

	ModStructure GetMod()
	{
		return m_Mod;
	}

	bool Read(out bool value)
	{
		value = m_Stream.Next() != 0;

		return true;
	}

	bool Read(out int value)
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();
		
		value = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);

		return true;
	}

	bool Read(out float value)
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();

		int src[1];
		src[0] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		float dst[1];
		
		copyarray(dst, src);

		value = dst[0];

		return true;
	}

	bool Read(out vector value)
	{
		int b3;
		int b2;
		int b1;
		int b0;

		int src[3];
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[0] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[1] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[2] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		copyarray(value, src);

		return true;
	}

	bool Read(out string value)
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();

		int length = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		for (int index = 0; index < length; index++)
		{
			value += m_Stream.Next().AsciiToString();
		}

		return true;
	}

	void Write(bool value)
	{
		m_Stream.AppendCurrent(value != 0);
	}

	void Write(int value)
	{
		m_Stream.AppendCurrent((value >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((value      ) & 0x000000FF);
	}

	void Write(float value)
	{
		float src[1] = { value };
		int dst[1];
		copyarray(dst, src);
		
		m_Stream.AppendCurrent((dst[0] >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0]      ) & 0x000000FF);
	}

	void Write(vector value)
	{
		int dst[3];
		copyarray(dst, value);

		int a = dst[0];
		int b = dst[1];
		int c = dst[2];
		
		m_Stream.AppendCurrent((a >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((a      ) & 0x000000FF);
		
		m_Stream.AppendCurrent((b >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((b      ) & 0x000000FF);
		
		m_Stream.AppendCurrent((c >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((c      ) & 0x000000FF);
	}

	void Write(string value)
	{
		int length = value.Length();
		m_Stream.AppendCurrent((length >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((length      ) & 0x000000FF);
		
		for (int i = 0; i < length; i++)
		{
			m_Stream.AppendCurrent(value.Substring(i, 1).Hash());
		}
	}

	void _WriteHeader()
	{
		m_Stream.m_Current = m_Stream.m_Head;
		m_Stream.m_Position = 0;

		// size + string length (+1) + mod version 
		Write(m_Stream.m_Size + m_ModName.Length() + 4 + 4);
		Write(m_ModName);
		Write(m_Version);

		m_Stream.m_Current = m_Stream.m_Tail;
		m_Stream.m_Position = m_Stream.m_Size - 1;
	}

	void _CopyStreamFrom(CF_Stream stream, int size, int version)
	{
		m_Stream = null;
		if (!stream) return;

		m_Stream = new CF_Stream();
		stream.CopyTo(m_Stream, size);

		m_Version = version;
	}

	void _CopyStreamTo(CF_Stream stream)
	{
		m_Stream.CopyTo(stream);
		
		_ResetStream();
	}

	void _ResetStream()
	{
		m_Stream = null;

		m_Version = m_Mod.GetStorageVersion();
	}
};
