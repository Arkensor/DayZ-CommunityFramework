typedef CF_Localiser StringLocaliser;

/**@class		CF_Localiser
 * @brief		This class handle string formatting over network
 **/
class CF_Localiser
{
	private	int m_Count;

	private	string m_Strings[10];
	private	bool m_Translates[10];

	void CF_Localiser(string text = "", string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		Set(-1, text);
		Set(0, param1);
		Set(1, param2);
		Set(2, param3);
		Set(3, param4);
		Set(4, param5);
		Set(5, param6);
		Set(6, param7);
		Set(7, param8);
		Set(8, param9);
	}

	void SetTranslates(bool translates)
	{
		m_Translates[0] = translates;
	}

	string Format()
	{
		return ToStr();
	}

	string ToStr()
	{
		string text = GetTranslated(-1);
		string p1 = GetTranslated(0);
		string p2 = GetTranslated(1);
		string p3 = GetTranslated(2);
		string p4 = GetTranslated(3);
		string p5 = GetTranslated(4);
		string p6 = GetTranslated(5);
		string p7 = GetTranslated(6);
		string p8 = GetTranslated(7);
		string p9 = GetTranslated(8);

		return string.Format(text, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	string GetText()
	{
		return Get(-1);
	}

	CF_Localiser Set(int index, bool value)
	{
		return Set(index, value.ToString(), false);
	}

	CF_Localiser Set(int index, int value)
	{
		return Set(index, value.ToString(), false);
	}

	CF_Localiser Set(int index, float value)
	{
		return Set(index, value.ToString(), false);
	}

	CF_Localiser Set(int index, vector value)
	{
		return Set(index, value.ToString(false), false);
	}

	CF_Localiser Set(int index, Class value)
	{
		string toStr = "";
		g_Script.CallFunction(value, "ToStr", toStr, null);
		return Set(index, toStr, false);
	}

	CF_Localiser Set(int index, string value)
	{
		return Set(index, value, true);
	}

	CF_Localiser Set(int index, string value, bool translates)
	{
		int realIndex = index + 1;
		if (realIndex < 0 || realIndex > 9)
			return this;

		if (realIndex >= m_Count)
		{
			if (value == "" && realIndex != 0)
				return this;

			m_Count = realIndex + 1;
		}

		m_Strings[realIndex] = value;
		m_Translates[realIndex] = translates;
		return this;
	}

	string Get(int index)
	{
		int realIndex = index + 1;
		if (realIndex < 0 || realIndex >= m_Count)
			return "";
		return m_Strings[realIndex];
	}

	string GetTranslated(int index)
	{
		int realIndex = index + 1;
		if (realIndex < 0 || realIndex >= m_Count)
			return "";
		string value = m_Strings[realIndex];
		if (m_Translates[realIndex])
		{
			value = Widget.TranslateString("#" + value);
			if (value == "" || value[0] == " ")
				return m_Strings[realIndex];
		}
		return value;
	}

	/* Backwards compatbility - to be removed after CF 1.4 */

	CF_Localiser SetParam1(string arg)
	{
		return Set(1, arg);
	}

	CF_Localiser SetParam2(string arg)
	{
		return Set(2, arg);
	}

	CF_Localiser SetParam3(string arg)
	{
		return Set(3, arg);
	}

	CF_Localiser SetParam4(string arg)
	{
		return Set(4, arg);
	}

	CF_Localiser SetParam5(string arg)
	{
		return Set(5, arg);
	}

	CF_Localiser SetParam6(string arg)
	{
		return Set(6, arg);
	}

	CF_Localiser SetParam7(string arg)
	{
		return Set(7, arg);
	}

	CF_Localiser SetParam8(string arg)
	{
		return Set(8, arg);
	}

	CF_Localiser SetParam9(string arg)
	{
		return Set(9, arg);
	}
};
