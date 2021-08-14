/*
	Byte Type Definition
	--	This is a byte datatype definition for EnScript

	Author: Lystic, Jacob_Mango

	When working with bytes. It is necessary to use `CF_Byte::Clamp()` to ensure the value remains 8 bit when modifying.
*/

typedef int CF_Byte;
class CF_Byte : CF_Uint
{
	CF_Byte Clamp()
	{
		CF_Byte old_byte = value;
		value = value & 255;
		if (value != old_byte)
		{
			Error("byte overflow");
		}
		return value;
	}

	void Set(int index, int v)
	{
		value = v;
		value.Clamp();
	}

	int Get(int index)
	{
		return value;
	}

	static CF_Byte Set(int value)
	{
		CF_Byte byte = value;
		byte.Clamp();
		return byte;
	}

	static CF_Byte Set(string char)
	{
		CF_Byte byte = char[0].Hash();
		byte.Clamp();
		return byte;
	}

	string ToHex()
	{
		value.Clamp();
		int ascii = value;

		int n0 = Math.Floor(value / 16);
		int n1 = value % 16;

		return CF_Encoding.BASE_16[n0] + CF_Encoding.BASE_16[n1];
	}

	override CF_Uint ^(CF_Uint y)
	{
		CF_Byte b = super.^(y);
		b.Clamp();
		return b;
	}

	override CF_Uint XOR(CF_Uint y)
	{
		CF_Byte b = super.XOR(y);
		b.Clamp();
		return b;
	}
};
