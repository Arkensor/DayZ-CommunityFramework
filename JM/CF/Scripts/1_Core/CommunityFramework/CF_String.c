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
	[Obsolete("Use string::LastIndexOf")]
	int CF_LastIndexOf(CF_String sample)
	{
		string s = sample;
		return value.LastIndexOf(s);
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
		length = length - newString.Length();

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
		length = length - newString.Length();

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
	 * @brief	Returns trimmed string with removed leading 'trimChars'
	 * 
	 * @param trimChars The characters to be trimmed (defaults to whitepace if not given)
	 * 
	 * @code
	 * 	string str = " Hello World "
	 * 	Print( str );
	 * 	Print( str.TrimStart() );
	 * 
	 * 	>> ' Hello World '
	 * 	>> 'Hello World '
	 * @endcode
	 */
	string TrimStart(string trimChars = "")
	{
		if (!trimChars)
			trimChars = " \n\r\t";

		int length = value.Length();
		int index;

		while (index < length)
		{
			string c = value[index];
			bool found = false;

			for (int i = 0; i < trimChars.Length(); ++i)
			{
				if (c == trimChars[i])
				{
					found = true;
					break;
				}
			}

			if (!found)
				break;

			++index;
		}

		if (index > 0)
			return value.Substring(index, length - index);

		return value;
	}

	/**
	 * @brief	Removes leading 'trimChars'
	 *
	 * @param trimChars The characters to be trimmed (defaults to whitepace if not given)
	 * @return New length of string
	 * 
	 * @code
	 *  string str = " Hello World ";
	 *  int i = str.TrimStartInPlace();
	 *  Print(str);
	 *  Print(i);
	 *  
	 *  >> str = 'Hello World '
	 *  >> i = 12
	 * @endcode
	 */
	int TrimStartInPlace(string trimChars = "")
	{
		CF_String toTrim = value;
		value = toTrim.TrimStart(trimChars);
		return value.Length();
	}

	/**
	 * @brief	Returns trimmed string with removed trailing 'trimChars'
	 * 
	 * @param trimChars The characters to be trimmed (defaults to whitepace if not given)
	 * 
	 * @code
	 * 	string str = " Hello World "
	 * 	Print( str );
	 * 	Print( str.TrimEnd() );
	 * 
	 * 	>> ' Hello World '
	 * 	>> ' Hello World'
	 * @endcode
	 */
	string TrimEnd(string trimChars = "")
	{
		if (!trimChars)
			trimChars = " \n\r\t";

		int length = value.Length();
		int index = length - 1;

		while (index >= 0)
		{
			string c = value[index];
			bool found = false;

			for (int i = 0; i < trimChars.Length(); ++i)
			{
				if (c == trimChars[i])
				{
					found = true;
					break;
				}
			}

			if (!found)
				break;

			--index;
		}

		int newLength = index + 1;
		if (newLength < length)
			return value.Substring(0, newLength);

		return value;
	}

	/**
	 * @brief	Removes trailing 'trimChars'
	 *
	 * @param trimChars The characters to be trimmed (defaults to whitepace if not given)
	 * @return New length of string
	 * 
	 * @code
	 *  string str = " Hello World ";
	 *  int i = str.TrimEndInPlace();
	 *  Print(str);
	 *  Print(i);
	 *  
	 *  >> str = ' Hello World'
	 *  >> i = 12
	 * @endcode
	 */
	int TrimEndInPlace(string trimChars = "")
	{
		
		CF_String toTrim = value;
		value = toTrim.TrimEnd(trimChars);
		return value.Length();
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

		for (int i = value.Length() - 1; i >= 0; --i)
		{
			result += value[i];
		}

		return result;
	}

	//! Vanilla string.Replace truncates long text >:-(
	int CF_Replace(string search, string replace)
	{
		int count;
		int searchLen = search.Length();
		int replaceLen = replace.Length();
		int index = value.IndexOf(search);
		while (index > -1)
		{
			if (index > 8191)
				Error("Index exceeds string::Substring max of 8191");
			int remainingLen = value.Length() - index - searchLen;
			if (remainingLen > 8191)
				Error("Remaining length exceeds string::Substring max of 8191");
			value = value.Substring(0, index) + replace + value.Substring(index + searchLen, remainingLen);
			count++;
			index = value.IndexOfFrom(index + replaceLen, search);
		}

		return count;
	}
};
