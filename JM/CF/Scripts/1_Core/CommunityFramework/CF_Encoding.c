class CF_Encoding
{
	static const ref array<string> HEX = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };

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
			int n0 = HEX.Find(str[i * 2 + 0]) * 16;
			int n1 = HEX.Find(str[i * 2 + 1]) * 16;

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
};
