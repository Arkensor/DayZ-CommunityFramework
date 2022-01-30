typedef string CF_String;
class CF_String : string
{
	/**
	 * @brief	Returns the number of times the specified character exists in the string
	 * 
	 * @param char The character that will be matched
	 * 
	 * @code
	 * 	CF_String str = "Hello, World!";
	 *  int count = str.CountCharacter("l");
	 * 	Print(count);
	 * 	>> '3'
	 * @endcode
	 */
	int CountCharacter(CF_String char)
	{
		int count = 0;
		int length = value.Length();
		for (int index = 0; index < length; index++)
		{
			count += value.Substring(index, 1) == char;
		}
		return count;
	}

	/**
	 * @brief	Returns the number of times the specified character exists in the string
	 * 
	 * @param char The character that will be matched
	 * @param[out] firstOccurrence  The index of the first character
	 * 
	 * @code
	 * 	CF_String str = "Hello, World!";
	 *  int index;
	 *  int count = str.CountCharacter("l", index);
	 * 	Print(count);
	 * 	Print(index);
	 * 	>> '3'
	 * 	>> '2'
	 * @endcode
	 */
	int CountCharacter(CF_String char, out int firstOccurrence )
	{
		int count = 0;
		firstOccurrence  = -1;

		int length = value.Length();
		for (int index = 0; index < length; index++)
		{
			count += value.Substring(index, 1) == char;

			if (count == 1 && firstOccurrence  == -1)
			{
				firstOccurrence  = index;
			}
		}

		return count;
	}

	/**
	 * @brief	Finds last 'sample' in 'str'. Returns -1 when not found
	 * 
	 * @param sample Finding string
	 * @return Returns position where sample starts, or -1 when sample not found
	 * 
	 * @code
	 * 	CF_String str = "Hello, World!";
	 * 	Print(str.CF_LastIndexOf("l"));
	 * 	>> 10
	 * @endcode
	 */
	int CF_LastIndexOf(CF_String sample)
	{
		int sampleLength = sample.Length();
		int length = value.Length();
		int start = length - sampleLength;
		if (start <= 0)
		{
			return -1;
		}

		for (int index = start - 1; index >= 0; index--)
		{
			if (value.Substring(index, sampleLength) == sample)
			{
				return index;
			}
		}

		return -1;
	}

	/**
	 * @brief	Fills the string with the specified character at the start so the string matches the length. 
	 * 			Does nothing if string is equal to or exceeds the specifiying length.
	 * 
	 * @param length The total string length 
	 * @param padChar The character that will be padded
	 * 
	 * @code
	 * 	CF_String str = "55";
	 * 	Print(str.PadStringFront(4, "0"));
	 * 	>> '0055'
	 * @endcode
	 */
	string PadStringFront(int length, CF_String padChar)
	{
		string newString = value;
		length = newString.Length() - length;

		if (length > 0)
		{
			for (int index = 0; index < length; index++)
			{
				newString = padChar + newString;
			}
		}

		return newString;
	}

	/**
	 * @brief	Fills the string with the specified character at the end so the string matches the length. 
	 * 			Does nothing if string is equal to or exceeds the specifiying length.
	 * 
	 * @param length The total string length 
	 * @param padChar The character that will be padded
	 * 
	 * @code
	 * 	CF_String str = "55";
	 * 	Print(str.PadStringBack(4, "0"));
	 * 	>> '5500'
	 * @endcode
	 */
	string PadStringBack(int length, CF_String padChar)
	{
		string newString = value;
		length = newString.Length() - length;

		if (length > 0)
		{
			for (int index = 0; index < length; index++)
			{
				newString += padChar;
			}
		}

		return newString;
	}

	/**
	 * @brief	Replaces the string of length at the index with the splice. 
	 * 
	 * @param start The index at which to start changing the string
	 * @param padChar The string the content will be replaced with
	 * 
	 * @code
	 * 	CF_String str = "How is you?";
	 * 	Print(str.SpliceString(4, "be"));
	 * 	>> 'How be you?'
	 * @endcode
	 */
	string SpliceString(int start, CF_String splice)
	{
		int middle = start + splice.Length();
		int end = value.Length();
		string a = value.Substring(0, start);
		string b = splice;
		if (middle >= end)
		{
			return a + b;
		}

		string c = value.Substring(middle, end - middle);
		return a + b + c;
	}

	/**
	 * @brief	Replaces the string of length at the index with the splice. New string does not have to match the length.
	 * 
	 * @param start The index at which to start changing the string
	 * @param length The length of characters to be removed
	 * @param padChar The string the content will be replaced with
	 * 
	 * @code
	 * 	CF_String str = "How are you?";
	 * 	Print(str.SpliceString(4, 3, "is"));
	 * 	>> 'How is you?'
	 * @endcode
	 */
	string SpliceString(int start, int length, CF_String splice)
	{
		int middle = start + length;
		int end = value.Length();
		string a = value.Substring(0, start);
		string b = splice;
		if (middle >= end)
		{
			return a + b;
		}

		string c = value.Substring(middle, end - middle);
		return a + b + c;
	}

	/**
	 * @brief	Checks to see if the two string matches
	 * 
	 * @param a The first string to be checked
	 * @param b The second string to be checked
	 * 
	 * @code
	 * 	CF_String a = "How are you?";
	 * 	CF_String b = "how are you?";
	 * 
	 * 	Print(CF_String.Equals(a, b));
	 * 	>> false
	 * 
	 * 	b = "How are you?";
	 * 	Print(CF_String.Equals(a, b));
	 * 	>> true
	 * @endcode
	 */
	static bool Equals(string a, string b)
	{
		return a == b;
	}


	/**
	 * @brief	Checks to see if the two string matches, ignoring their case
	 * 
	 * @param a The first string to be checked
	 * @param b The second string to be checked
	 * 
	 * @code
	 * 	CF_String a = "How are you?";
	 * 	CF_String b = "how are you?";
	 * 
	 * 	Print(CF_String.EqualsIgnoreCase(a, b));
	 * 	>> true
	 * 
	 * 	b = "How are you?";
	 * 	Print(CF_String.EqualsIgnoreCase(a, b));
	 * 	>> true
	 * @endcode
	 */
	static bool EqualsIgnoreCase(string a, string b)
	{
		a.ToLower();
		b.ToLower();

		return a == b;
	}

	/**
	 * @brief	Reverses the string
	 * 
	 * @code
	 * 	CF_String a = "How are you?";
	 * 	CF_String b = a.Reverse();
	 * 
	 * 	Print(a);
	 * 	>> "How are you?"
	 * 	Print(b);
	 * 	>> "?uoy era woH"
	 * 
	 * @endcode
	 */
	string Reverse()
	{
		string result;

		int index = value.Length() - 1;
		while (index >= 0)
		{
			result += value.Substring(index, 1);

			index--;
		}

		return result;
	}
};
