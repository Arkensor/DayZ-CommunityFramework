class CF_NetworkVariable
{
	static const int MAX_DEPTH = 4;

	ref CF_NetworkVariable m_Next;

	string m_Name;

	int m_Count; // MAX_DEPTH
	int m_AccessorIndices[MAX_DEPTH];
	ref map<int, typename> m_AccessorTypes = new map<int, typename>;

	CF_TypeConverterBase m_Converter;
};
