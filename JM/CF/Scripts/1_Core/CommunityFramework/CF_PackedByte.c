/**
 * Storing bytes in a forward doubly linked list.
 * This gives both fast reading and an unlimited size of bytes
 */
class CF_PackedByte
{
	ref CF_PackedByte m_Next;
	CF_PackedByte m_Prev;

	CF_Byte m_Value;

	CF_PackedByte SerializerWrite(Serializer ctx, int length, inout int index)
	{
		CF_PackedByte byte = this;

		int b0;
		int b1;
		int b2;
		int b3;

		if (byte)
		{
			b0 = byte.m_Value;
			byte = byte.m_Next;

			index++;
		}

		if (byte)
		{
			b1 = byte.m_Value;
			byte = byte.m_Next;

			index++;
		}

		if (byte)
		{
			b2 = byte.m_Value;
			byte = byte.m_Next;

			index++;
		}

		if (byte)
		{
			b3 = byte.m_Value;
			byte = byte.m_Next;

			index++;
		}

		ctx.Write(((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0 & 0x000000FF));

		return byte;
	}

	CF_PackedByte SerializerRead(Serializer ctx, int length, inout int index)
	{
		CF_PackedByte byte = this;

		int value;

		ctx.Read(value);

		int b3 = (value >> 24) & 0x000000FF;
		int b2 = (value >> 16) & 0x000000FF;
		int b1 = (value >> 8 ) & 0x000000FF;
		int b0 = (value		 ) & 0x000000FF;
		
		if (index < length)
		{
			index++;
			
			// set and clamp
			byte.m_Value = b0 & 255;

			byte.m_Next = new CF_PackedByte();
			byte.m_Next.m_Prev = byte;
			byte = byte.m_Next;
		}

		if (index < length)
		{
			index++;
			
			// set and clamp
			byte.m_Value = b1 & 255;
			
			byte.m_Next = new CF_PackedByte();
			byte.m_Next.m_Prev = byte;
			byte = byte.m_Next;
		}

		if (index < length)
		{
			index++;
			
			byte.m_Value = b2 & 255;
			
			byte.m_Next = new CF_PackedByte();
			byte.m_Next.m_Prev = byte;
			byte = byte.m_Next;
		}

		if (index < length)
		{
			index++;
			
			byte.m_Value = b3 & 255;
			
			byte.m_Next = new CF_PackedByte();
			byte.m_Next.m_Prev = byte;
			byte = byte.m_Next;
		}

		return byte;
	}
};
