class CF_ModStorageReader : CF_ModStorage
{
	ref CF_Stream m_Stream;

	void CF_ModStorageReader(ModStructure mod, CF_Stream stream)
	{
		m_Stream = stream;
	}

	override bool Read(out bool value)
	{
		value = m_Stream.Next() != 0;

		return true;
	}

	override bool Read(out int value)
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();
		
		value = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);

		return true;
	}

	override bool Read(out float value)
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

	override bool Read(out vector value)
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

	override bool Read(out string value)
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
};
