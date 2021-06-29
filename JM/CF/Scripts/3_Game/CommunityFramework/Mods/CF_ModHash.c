class CF_ModHash
{
	protected int m_Hash[2];
	protected string m_Packed;

	void CF_ModHash(string modName = "", bool secondaryHash = true)
	{
		if (!modName)
			return;

		Update(modName, secondaryHash);
	}

	string Repr()
	{
		return "{" + m_Packed + "}";
	}

	string GetPacked()
	{
		return m_Packed;
	}

	/*static int Hash(string data)
	{
		//! Based on DayZ' internal string.Hash() method, but using a different prime for better collision resilience

		int hash;
		for (int i = 0; i < data.Length(); i++)
		{
			string character = data[i];
			//! XXX: ToAscii is broken, always returns 0
			int ascii = character.ToAscii(character);
			Print("ModStructure::ToAscii '" + character + "' -> " + ascii);
			hash = hash * 109 + ascii;
		}

		Print("ModStructure::Hash '" + data + "' -> " + hash);

		return hash;
	}*/

	void Save(ParamsWriteContext ctx)
	{
		ctx.Write(m_Hash);
	}
	
	bool Load(ParamsReadContext ctx, int cf_version)
	{
		if (cf_version >= 4)
		{
			if (!ctx.Read(m_Hash)) return false;
		}
		else if (cf_version == 3)
		{
			int hash;
			if (!ctx.Read(hash)) return false;
			m_Hash[0] = hash;
		}
		else
		{
			return false;
		}

		Pack();

		//Print(ToString() + "::Load version " + cf_version + " -> " + Repr());

		return true;
	}

	/*static string Pack(int n)
	{
		string cbytes;
		//! XXX: AsciiToString returns random data if outside ASCII range
		cbytes += ((n >> 24) & 0xFF).AsciiToString();
		cbytes += ((n >> 16) & 0xFF).AsciiToString();
		cbytes += ((n >> 8) & 0xFF).AsciiToString();
		cbytes += (n & 0xFF).AsciiToString();
		return cbytes;
	}*/

	void Pack()
	{
		m_Packed = m_Hash[0].ToString() + "," + m_Hash[1].ToString();
	}

	void Update(string modName, bool secondaryHash = true)
	{
		string repr = Repr();

		m_Hash[0] = modName.Hash();

		if (secondaryHash)
		{
			//! Make it more resilient against collisions by using a 2nd hash from the reversed mod name
			string reversed;
			for (int i = 0; i < modName.Length(); i++)
			{
				reversed = modName[i] + reversed;
			}
			m_Hash[1] = reversed.Hash();
		}

		Pack();

		Print(ToString() + "::Update('" + modName + "', " + secondaryHash + ") " + repr + " -> " + Repr());
	}
}
