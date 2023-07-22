class CF_Encoding
{
	static const string BASE_16[16] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"
	};
	
	static const string BASE_64[64] = {
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
		"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f",
		"g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
		"w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/",
	};

	static int Find(string[] data, int count, string match)
	{
		for (int i = 0; i < count; i++)
		{
			if (data[i] == match) return i;
		}

		return -1;
	}

	static string FindGet(string[] data, int count, string match)
	{
		for (int i = 0; i < count; i++)
		{
			if (data[i] == match) return data[i];
		}

		return data[0];
	}

	static CF_Byte GetByte(string char)
	{
		return CF_Byte.Set(char);
	}

	static array<CF_Byte> GetBytes(string str)
	{
		array<CF_Byte> bytes = new array<CF_Byte>();
		for (int i = 0; i < str.Length(); i++)
		{
			bytes.Insert(CF_Byte.Set(str[i]));
		}
		return bytes;
	}

	static string ToHex(array<CF_Byte> bytes)
	{
		string str = "";
		for (int i = 0; i < bytes.Count(); i++)
		{
			str += bytes[i].ToHex();
		}
		return str;
	}

	static array<CF_Byte> FromHex(string str)
	{
		if (str.Length() % 2 != 0)
		{
			Error("Invalid string length");
			return null;
		}

		array<CF_Byte> bytes = new array<CF_Byte>();

		for (int i = 0; i < str.Length() / 2; i++)
		{
			int n0 = Find(BASE_16, 16, str[i * 2 + 0]) * 16;
			int n1 = Find(BASE_16, 16, str[i * 2 + 1]);

			if (n0 < 0 || n1 < 0)
			{
				Error("Invalid character, expect valid base-16, got \"" + str[i * 2 + 0] + str[i * 2 + 1] + "\"");
				return null;
			}

			CF_Byte byte = n0 + n1;
			bytes.Insert(byte);
		}

		return bytes;
	}

	static string ToBase64(array<CF_Byte> bytes)
	{
		string str = "";
		for (int i = 0; i < bytes.Count(); i++)
		{
			str += bytes[i].ToHex();
		}
		return str;
	}

	static bool IsWhitespace(string char)
	{
		return IsWhitespace(CF_Byte.Set(char));
	}

	/**
	 * @brief	Returns true if the input byte as in any character below decimal 32.
	 * 			Helpful table https://commons.wikimedia.org/wiki/File:ASCII-Table-wide.svg
	 */
	static bool IsWhitespace(CF_Byte byte)
	{
		if (byte <= 32) return true;

		return false;
	}

	static bool IsAlphanumeric(string char)
	{
		return IsAlphanumeric(CF_Byte.Set(char));
	}

	static bool IsAlphanumeric(CF_Byte byte)
	{
		if (byte >= 48 && byte <= 57) return true;
		if (byte > 90) byte -= 32;
		if (byte >= 65 && byte <= 90) return true;

		return false;
	}

	static bool IsAlpha(string char)
	{
		return IsAlpha(CF_Byte.Set(char));
	}

	static bool IsAlpha(CF_Byte byte)
	{
		if (byte > 90) byte -= 32;
		if (byte >= 65 && byte <= 90) return true;

		return false;
	}

	static bool IsNumeric(string char)
	{
		return IsNumeric(CF_Byte.Set(char));
	}

	static bool IsNumeric(CF_Byte byte)
	{
		if (byte >= 48 && byte <= 57) return true;

		return false;
	}

	static bool IsLine(string char)
	{
		return IsNumeric(CF_Byte.Set(char));
	}

	static bool IsLine(CF_Byte byte)
	{
		if (byte >= 10 && byte <= 15) return true;

		return false;
	}

    static bool StringToBool(string str)
    {
        str.ToLower();
        str.Trim();
        if (str == "true") return true;
        if (str == "false") return false;
        return str.ToInt();
    }
};
