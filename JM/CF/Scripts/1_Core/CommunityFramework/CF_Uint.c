/*
	Uint Type Definition
	--	This is a CF_Uint datatype definition for EnScript

	Author: Lystic, Jacob_Mango

	When working with uints, Right Shift operations need to be handled by the ShiftRight method.
*/

typedef int CF_Uint;
class CF_Uint : int
{
	CF_Uint Add(CF_Uint b)
	{
		CF_Uint a = value;
		CF_Uint carry = a & b;
		CF_Uint result = a.XOR(b);
		while (carry)
		{
			CF_Uint shiftedcarry = carry << 1;
			carry = result & shiftedcarry;
			result = result.XOR(shiftedcarry);
		}
		return result;
	}

	bool IsGt(CF_Uint b)
	{
		CF_Uint a = value;

		CF_Uint ltb = ~a & b;
		CF_Uint gtb = a & ~b;
		ltb |= ltb.ShiftRight(1);
		ltb |= ltb.ShiftRight(2);
		ltb |= ltb.ShiftRight(4);
		ltb |= ltb.ShiftRight(8);
		ltb |= ltb.ShiftRight(16);
		CF_Uint isGt = gtb & ~ltb;
		return (isGt != 0); //non-zero if A > B
	}

	bool IsLt(CF_Uint b)
	{
		return !b.IsGt(value);
	}

	CF_Uint ShiftLeft(int amount)
	{
		return value << amount;
	}

	CF_Uint ShiftRight(int amount)
	{
		if (amount <= 0) return value;

		CF_Uint new_value = (value >> 1) & 0x7FFFFFFF; //strip the sign bit away (making it 0)
		CF_Uint extra_shifts = amount - 1;
		if (extra_shifts > 0) new_value = (new_value >> extra_shifts);

		return new_value;
	}

	//--- unsigned bitwise operations

	static CF_Uint RotateLeft(CF_Uint a, CF_Uint b)
	{
		CF_Uint y = (a << b);
		CF_Uint x = (32 - b);
		CF_Uint z = a.ShiftRight(x);
		return (y | z);
	}

	static CF_Uint RotateRight(CF_Uint a, CF_Uint b)
	{
		CF_Uint y = a.ShiftRight(b);
		CF_Uint x = (32 - b);
		CF_Uint z = (a << x);
		return (y | z);
	}

	static CF_Uint CH(CF_Uint x, CF_Uint y, CF_Uint z)
	{
		CF_Uint a = (x & y);
		CF_Uint b = ~x;
		CF_Uint c = (b & z);
		return a.XOR(c); // a XOR c
	}

	static CF_Uint MAJ(CF_Uint x, CF_Uint y, CF_Uint z)
	{
		CF_Uint a = x & y;
		CF_Uint b = x & z;
		CF_Uint c = y & z;
		return a.XOR(b.XOR(c))); //a XOR b XOR c (left-right associativity)
	}

	static CF_Uint EP0(CF_Uint x)
	{
		CF_Uint a = CF_Uint.RotateRight(x, 2);
		CF_Uint b = CF_Uint.RotateRight(x, 13);
		CF_Uint c = CF_Uint.RotateRight(x, 22);
		return a.XOR(b.XOR(c))); //a XOR b XOR c
	}

	static CF_Uint EP1(CF_Uint x)
	{
		CF_Uint a = CF_Uint.RotateRight(x, 6);
		CF_Uint b = CF_Uint.RotateRight(x, 11);
		CF_Uint c = CF_Uint.RotateRight(x, 25);
		return a.XOR(b.XOR(c))); //a XOR b XOR c
	}

	static CF_Uint SIG0(CF_Uint x)
	{
		CF_Uint a = CF_Uint.RotateRight(x, 7);
		CF_Uint b = CF_Uint.RotateRight(x, 18);
		CF_Uint c = x.ShiftRight(3);
		return a.XOR(b.XOR(c))); //a XOR b XOR c
	}

	static CF_Uint SIG1(CF_Uint x)
	{
		CF_Uint a = CF_Uint.RotateRight(x, 17);
		CF_Uint b = CF_Uint.RotateRight(x, 19);
		CF_Uint c = x.ShiftRight(10);
		return a.XOR(b.XOR(c))); //a XOR b XOR c
	}

	CF_Uint XOR(CF_Uint y)
	{
		CF_Uint x = value;
		int a = (x | y);
		int b = ~x;
		int c = ~y;
		int d = (b | c);
		return (a & d);
	}
};
