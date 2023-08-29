/*
	Byte Type Definition
	--	This is a byte datatype definition for EnScript

	Author: Lystic, Jacob_Mango

	When working with bytes. It is necessary to use 'CF_Byte::Clamp()' to ensure the value remains 8 bit when modifying.
*/

typedef int CF_Byte;
class CF_Byte : CF_Uint
{
	CF_Byte Clamp()
	{
		CF_Byte oldByte = value;
		value = value & 255;
		return value;
	}

	void Set(int index, int v)
	{
		// set and clamp
		value = v & 255;
	}

	int Get(int index)
	{
		return value;
	}

	static CF_Byte Set(int value)
	{
		// set and clamp
		CF_Byte byte = value & 255;
		return byte;
	}

	static CF_Byte Set(string char)
	{
		CF_Byte byte = char.Get(0).ToAscii() & 255;
		return byte;
	}

	string ToHex()
	{
		int ascii = value & 255;

		int n0 = Math.Floor(ascii / 16);
		int n1 = ascii % 16;

		return CF_Encoding.BASE_16[n0] + CF_Encoding.BASE_16[n1];
	}

	override CF_Uint XOR(CF_Uint y)
	{
		CF_Byte b = super.XOR(y) & 255;
		return b;
	}
};
