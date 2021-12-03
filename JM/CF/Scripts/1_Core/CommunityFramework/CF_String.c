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
	 * @param firstIndex The index of the first character
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
	int CountCharacter(CF_String char, out int firstIndex)
	{
		int count = 0;
		firstIndex = -1;

		int length = value.Length();
		for (int index = 0; index < length; index++)
		{
			count += value.Substring(index, 1) == char;

			if (count == 1 && firstIndex == -1)
			{
				firstIndex = index;
			}
		}

		return count;
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
	 * 	Print(str.PadStringEnd(4, "0"));
	 * 	>> '0055'
	 * @endcode
	 */
	string PadString(int length, CF_String padChar)
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
	 * 	Print(str.PadStringEnd(4, "0"));
	 * 	>> '5500'
	 * @endcode
	 */
	string PadStringEnd(int length, CF_String padChar)
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
	 * @param start The first character to be removed
	 * @param padChar The string that will replace those characters
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
		string c = value.Substring(middle, end - middle);
		return a + b + c;
	}

	/**
	 * @brief	Replaces the string of length at the index with the splice. New string does not have to match the length.
	 * 
	 * @param start The first character to be removed
	 * @param length The length of characters to be removed
	 * @param padChar The string that will replace those characters
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
		string c = value.Substring(middle, end - middle);
		return a + b + c;
	}
};
