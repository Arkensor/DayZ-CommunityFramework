class CF_SHA256
{
	static CF_Uint s_K[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	static CF_Uint s_DataLength;
	static CF_Byte s_Data[64];
	static CF_Byte s_M[64];
	static CF_Uint s_BitLen[2];
	static CF_Uint s_State[8];
	static CF_Byte s_Hash[64];

	static void Process(CF_IO input, CF_IO output)
	{
		Process(input, output.m_Stream);
	}
	
	static void Process(CF_IO input, CF_Stream output)
	{
		if (!input) return;
		if (!input.m_Stream) return;

		input.m_Stream.SetPositionAtStart();

		s_DataLength = 0;
		s_BitLen[0] = 0;
		s_BitLen[1] = 0;
		s_State[0] = 0x6a09e667;
		s_State[1] = 0xbb67ae85;
		s_State[2] = 0x3c6ef372;
		s_State[3] = 0xa54ff53a;
		s_State[4] = 0x510e527f;
		s_State[5] = 0x9b05688c;
		s_State[6] = 0x1f83d9ab;
		s_State[7] = 0x5be0cd19;

		while (!input.EOF())
		{
			s_Data[s_DataLength] = input.ReadByte();
			s_DataLength++;

			if (s_DataLength == 64)
			{
				_Transform();

				_AdjustBitLength(512);
				s_DataLength = 0;
			}
		}

        CF_Uint i = s_DataLength;
        if (s_DataLength < 56)
        {
            s_Data[i++] = 0x80;

            while (i < 56)
                s_Data[i++] = 0x00;
        }
        else
        {
            s_Data[i++] = 0x80;

            while (i < 64)
                s_Data[i++] = 0x00;

            _Transform();
        }

		_AdjustBitLength(s_DataLength * 8);

        s_Data[63] = s_BitLen[0];
        s_Data[62] = s_BitLen[0].ShiftRight(8);
        s_Data[61] = s_BitLen[0].ShiftRight(16);
        s_Data[60] = s_BitLen[0].ShiftRight(24);
        s_Data[59] = s_BitLen[1];
        s_Data[58] = s_BitLen[1].ShiftRight(8);
        s_Data[57] = s_BitLen[1].ShiftRight(16);
        s_Data[56] = s_BitLen[1].ShiftRight(24);

        _Transform();
		
        for (i = 0; i < 4; ++i)
        {
            int shift = 24 - (i * 8);
			s_Hash[i     ] = s_State[0].ShiftRight(shift);
			s_Hash[i + 4 ] = s_State[1].ShiftRight(shift);
			s_Hash[i + 8 ] = s_State[2].ShiftRight(shift);
			s_Hash[i + 12] = s_State[3].ShiftRight(shift);
			s_Hash[i + 16] = s_State[4].ShiftRight(shift);
			s_Hash[i + 20] = s_State[5].ShiftRight(shift);
			s_Hash[i + 24] = s_State[6].ShiftRight(shift);
			s_Hash[i + 28] = s_State[7].ShiftRight(shift);
		}

        for (i = 0; i < 32; ++i)
		{
			output.Append(s_Hash[i] & 255);
		}
	}

	static void _Transform()
	{
		CF_Uint a, b, c, d, e, f, g, h, i, j, t1, t2;
		
		for (i = 0; i < 64; ++i) s_M[i] = 0;

		for (i = 0; i < 16; ++i)
		{
			CF_Uint l1_a = s_Data[j] << 24;
			CF_Uint l1_b = s_Data[j + 1] << 16;
			CF_Uint l1_c = s_Data[j + 2] << 8;
			CF_Uint l1_d = s_Data[j + 3];
			s_M[i] = (l1_a | l1_b | l1_c | l1_d);
			j += 4;
		}

		for (; i < 64; ++i)
		{
			CF_Uint l2_a = s_M[i - 2];
			CF_Uint l2_b = CF_Uint.SIG1(l2_a);
			CF_Uint l2_c = s_M[i - 7];
			CF_Uint l2_d = s_M[i - 15];
			CF_Uint l2_e = CF_Uint.SIG0(l2_d);
			CF_Uint l2_f = s_M[i - 16];
			s_M[i] = l2_b + l2_c + l2_e + l2_f;
		}

		a = s_State[0];
		b = s_State[1];
		c = s_State[2];
		d = s_State[3];
		e = s_State[4];
		f = s_State[5];
		g = s_State[6];
		h = s_State[7];

		for (i = 0; i < 64; ++i)
		{
			t1 = h.Add(CF_Uint.EP1(e)).Add(CF_Uint.CH(e, f, g)).Add(s_K[i]).Add(s_M[i]);	//h + EP1(e) + CH(e, f, g) + s_K[i] + s_M[i];
			t2 = CF_Uint.EP0(a).Add(CF_Uint.MAJ(a, b, c));						//EP0(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d.Add(t1); //d + t1;
			d = c;
			c = b;
			b = a;
			a = t1.Add(t2); //t1 + t2;
		}
		
		s_State[0] = s_State[0] + a;
		s_State[1] = s_State[1] + b;
		s_State[2] = s_State[2] + c;
		s_State[3] = s_State[3] + d;
		s_State[4] = s_State[4] + e;
		s_State[5] = s_State[5] + f;
		s_State[6] = s_State[6] + g;
		s_State[7] = s_State[7] + h;
	}

	static void _AdjustBitLength(CF_Uint c)
	{
		CF_Uint max_int = 0xffffffff;
		CF_Uint test = max_int - c;
		if (s_BitLen[0].IsGt(test)) //if a > test (unsigned comparison)
		{
			s_BitLen[1] = s_BitLen[1] + 1;
		}

		s_BitLen[0] = s_BitLen[0].Add(c); // A + C using unsigned math
	}
};
