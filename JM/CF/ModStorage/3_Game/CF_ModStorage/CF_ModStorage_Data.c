enum ModStorageDataType
{
	UNKNOWN = 0,
	BOOL,
	INT,
	FLOAT,
	VECTOR,
	STRING,
	CLASS,
	ARRAY,
	MAP
};

class ModStorageData
{
	protected string m_VariableName;

	static ref ModStorageData ReadCreate( ParamsReadContext ctx )
	{
		ref ModStorageData data = null;

		int type;
		ctx.Read( type );

		switch ( type )
		{
		case ModStorageDataType.BOOL:
			data = new ModStorageDataBool();
			break;
		case ModStorageDataType.INT:
			data = new ModStorageDataInt();
			break;
		case ModStorageDataType.FLOAT:
			data = new ModStorageDataFloat();
			break;
		case ModStorageDataType.VECTOR:
			data = new ModStorageDataVector();
			break;
		case ModStorageDataType.STRING:
			data = new ModStorageDataString();
			break;
		case ModStorageDataType.CLASS:
			data = new ModStorageDataClass();
			break;
		case ModStorageDataType.ARRAY:
			data = new ModStorageDataArray();
			break;
		}

		if ( data )
			data.Read( ctx );

		return data;
	}

	void Write( ParamsWriteContext ctx )
	{
	}

	void Read( ParamsReadContext ctx )
	{
	}

	ModStorageDataType GetType()
	{
		return ModStorageDataType.UNKNOWN;
	}
	
	bool IsNull()
	{
		return false;
	}
	
	void SetVariableName(string name)
	{
		m_VariableName = name;
	}
	
	string GetVariableName()
	{
		return m_VariableName;
	}

	bool GetBool();
	int GetInt();
	float GetFloat();
	vector GetVector();
	string GetString();
	bool GetClass(inout Class value);
};

class ModStorageDataBool: ModStorageData
{
	private bool m_Value;

	void ModStorageDataBool( bool value = false )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.BOOL;
	}

	override bool GetBool()
	{
		return m_Value;
	}
};

class ModStorageDataInt: ModStorageData
{
	private int m_Value;

	void ModStorageDataInt( int value = 0 )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.INT;
	}

	override int GetInt()
	{
		return m_Value;
	}
};

class ModStorageDataFloat: ModStorageData
{
	private float m_Value;

	void ModStorageDataFloat( float value = 0 )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.FLOAT;
	}

	override float GetFloat()
	{
		return m_Value;
	}
};

class ModStorageDataVector: ModStorageData
{
	private vector m_Value;

	void ModStorageDataVector( vector value = "0 0 0" )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.VECTOR;
	}

	override vector GetVector()
	{
		return m_Value;
	}
};

class ModStorageDataString: ModStorageData
{
	private string m_Value;

	void ModStorageDataString( string value = "" )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.STRING;
	}

	override string GetString()
	{
		return m_Value;
	}
};

class ModStorageRetriever<Class T>
{
	static T FromClass(Class cls, string name)
	{
		T result;
		EnScript.GetClassVar(cls, name, 0, result);
		return result;
	}
};

class ModStorageArrayRetriever<Class T>
{
	static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		return ModStorageDataType.UNKNOWN;
	}
	
	static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
	}
};

class ModStorageArrayRetrieverString : ModStorageArrayRetriever<TStringArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TStringArray srcArr = TStringArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			dataArr.Insert(new ModStorageDataString(srcArr[i]));
		}
		
		return ModStorageDataType.STRING;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TStringArray srcArr = TStringArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			srcArr.Insert(dataArr[i].GetString());
		}
	}
};

class ModStorageArrayRetrieverFloat : ModStorageArrayRetriever<TFloatArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TFloatArray srcArr = TFloatArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			dataArr.Insert(new ModStorageDataFloat(srcArr[i]));
		}
		
		return ModStorageDataType.FLOAT;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TFloatArray srcArr = TFloatArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			srcArr.Insert(dataArr[i].GetFloat());
		}
	}
};

class ModStorageArrayRetrieverVector : ModStorageArrayRetriever<TVectorArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TVectorArray srcArr = TVectorArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			dataArr.Insert(new ModStorageDataVector(srcArr[i]));
		}
		
		return ModStorageDataType.FLOAT;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TVectorArray srcArr = TVectorArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			srcArr.Insert(dataArr[i].GetVector());
		}
	}
};

class ModStorageArrayRetrieverInt : ModStorageArrayRetriever<TIntArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TIntArray srcArr = TIntArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			dataArr.Insert(new ModStorageDataInt(srcArr[i]));
		}
		
		return ModStorageDataType.INT;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TIntArray srcArr = TIntArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			srcArr.Insert(dataArr[i].GetInt());
		}
	}
};

class ModStorageArrayRetrieverBool : ModStorageArrayRetriever<TBoolArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TBoolArray srcArr = TBoolArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			dataArr.Insert(new ModStorageDataBool(srcArr[i]));
		}
		
		return ModStorageDataType.BOOL;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TBoolArray srcArr = TBoolArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			srcArr.Insert(dataArr[i].GetBool());
		}
	}
};

class ModStorageArrayRetrieverClass : ModStorageArrayRetriever<TClassArray>
{
	override static int ReadArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		Print(cls);
		TClassArray srcArr = TClassArray.Cast(cls);
		Print(srcArr); //! is null
		for (int i = 0; i < srcArr.Count(); i++)
		{
			if (srcArr[i].Type().IsInherited(array))
			{
				dataArr.Insert(new ModStorageDataArray(srcArr[i]));
			} else
			{
				dataArr.Insert(new ModStorageDataClass(srcArr[i]));
			}
		}
		
		return ModStorageDataType.CLASS;
	}
	
	override static void WriteArray(Class cls, ref array< ref ModStorageData > dataArr)
	{
		TClassArray srcArr = TClassArray.Cast(cls);
		for (int i = 0; i < dataArr.Count(); i++)
		{
			Class cls1;
			if (dataArr[i].GetClass(cls1))
				srcArr.Insert(cls1);
		}
	}
};

class ModStorageDataClass: ModStorageData
{
	private string m_Type;
	private bool m_IsNull;
	private ref array< ref ModStorageData > m_Data = new ref array< ref ModStorageData >();

	void ModStorageDataClass( Class value = null )
	{
		Print("ModStorageDataClass");
		if (value)
		{			
			typename type = value.Type();
			
			m_Type = type.ToString();
			m_IsNull = false;
			
			for (int i = 0; i < type.GetVariableCount(); i++)
			{
				typename variableType = type.GetVariableType(i);
				string variableName = type.GetVariableName(i);
				
				ModStorageData data;

				if (variableType.IsInherited(array))
				{					
					data = new ModStorageDataArray(ModStorageRetriever<Class>.FromClass(value, variableName));
				} else if (variableType.IsInherited(map))
				{					
					//data = new ModStorageDataClass(ModStorageRetriever<Class>.FromClass(value, variableName));
				} else if (variableType.IsInherited(Class))
				{					
					data = new ModStorageDataClass(ModStorageRetriever<Class>.FromClass(value, variableName));
				} else
				{
					switch (variableType)
					{
						case bool:
							data = new ModStorageDataBool(ModStorageRetriever<bool>.FromClass(value, variableName));
							break;
						case int:
							data = new ModStorageDataInt(ModStorageRetriever<int>.FromClass(value, variableName));
							break;
						case float:
							data = new ModStorageDataFloat(ModStorageRetriever<float>.FromClass(value, variableName));
							break;
						case string:
							data = new ModStorageDataString(ModStorageRetriever<string>.FromClass(value, variableName));
							break;
						case vector:
							data = new ModStorageDataVector(ModStorageRetriever<vector>.FromClass(value, variableName));
							break;
					}
				}
				
				if (data)
				{
					data.m_VariableName = variableName;
					m_Data.Insert(data);
				}
			}
		} else
		{
			m_IsNull = true;
		}
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		ctx.Write( m_IsNull );
		
		int count = m_Data.Count();
		ctx.Write( count );

		for ( int i = 0; i < count; i++ )
		{
			int type = m_Data[i].GetType();
			ctx.Write( type );
			m_Data[i].Write( ctx );
		}
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		ctx.Read( m_IsNull );
		
		int count;
		ctx.Read( count );

		for ( int i = 0; i < count; i++ )
		{
			m_Data.Insert( ModStorageData.ReadCreate( ctx ) );
		}
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.CLASS;
	}
	
	override bool IsNull()
	{
		return m_IsNull;
	}

	override bool GetClass(inout Class value)
	{
		if (m_IsNull)
			return true;
		
		if (!value)
		{
			if (m_Type == "")
				return false;
			value = m_Type.ToType().Spawn();
			if (value == null)
				return false;
		}
		
		for (int i = 0; i < m_Data.Count(); i++)
		{
			switch (m_Data[i].GetType())
			{
			case ModStorageDataType.BOOL:
				EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, m_Data[i].GetBool());
				break;
			case ModStorageDataType.INT:
				EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, m_Data[i].GetInt());
				break;
			case ModStorageDataType.FLOAT:
				EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, m_Data[i].GetFloat());
				break;
			case ModStorageDataType.VECTOR:
				EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, m_Data[i].GetVector());
				break;
			case ModStorageDataType.STRING:
				EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, m_Data[i].GetString());
				break;
			case ModStorageDataType.ARRAY:
			case ModStorageDataType.CLASS:
				if (!m_Data[i].IsNull())
				{
					Class cls;
					EnScript.GetClassVar(value, m_Data[i].m_VariableName, 0, cls);
					m_Data[i].GetClass(cls);
					EnScript.SetClassVar(value, m_Data[i].m_VariableName, 0, cls);
				}
				break;
			}
		}
		
		return true;
	}
};

typedef array<ref Class> TRefClassArray;

class ModStorageDataArray: ModStorageData
{
	private int m_Type;
	private ref array< ref ModStorageData > m_Data = new ref array< ref ModStorageData >();

	void ModStorageDataArray( Class value = null )
	{
		if (value)
		{			
			if (value.IsInherited(TStringArray))
			{
				m_Type = ModStorageArrayRetrieverString.ReadArray(value, m_Data);
			} else if (value.IsInherited(TFloatArray))
			{
				m_Type = ModStorageArrayRetrieverFloat.ReadArray(value, m_Data);
			} else if (value.IsInherited(TVectorArray))
			{
				m_Type = ModStorageArrayRetrieverVector.ReadArray(value, m_Data);
			} else if (value.IsInherited(TIntArray))
			{
				m_Type = ModStorageArrayRetrieverInt.ReadArray(value, m_Data);
			} else if (value.IsInherited(TBoolArray))
			{
				m_Type = ModStorageArrayRetrieverBool.ReadArray(value, m_Data);
			} else
			{
				m_Type = ModStorageDataType.CLASS;
				
				//string type = m_Type.Type().ToString();
				
				//type.Replace("array<", "");
				//type.Replace(">", "");
				//type.Replace("@", "");
				
				m_Type = ModStorageArrayRetrieverClass.ReadArray(value, m_Data);
				
				//for (int i = 0; i < type.GetVariableCount(); i++)
				//	Print(type.GetVariableType(i));
			}
		} else
		{
			m_Type = ModStorageDataType.UNKNOWN;
		}
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_VariableName );
		
		ctx.Write( m_Type );
		
		int count = m_Data.Count();
		ctx.Write( count );

		for ( int i = 0; i < count; i++ )
		{
			int type = m_Data[i].GetType();
			ctx.Write( type );
			m_Data[i].Write( ctx );
		}
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_VariableName );
		
		ctx.Read( m_Type );
		
		int count;
		ctx.Read( count );

		for ( int i = 0; i < count; i++ )
		{
			m_Data.Insert( ModStorageData.ReadCreate( ctx ) );
		}
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.ARRAY;
	}
	
	override bool IsNull()
	{
		return false;
	}

	override bool GetClass(inout Class value)
	{
		if (!value)
		{
			return false;
		}
		
		switch (m_Type)
		{
			case ModStorageDataType.BOOL:
				ModStorageArrayRetrieverBool.WriteArray(value, m_Data);
				break;
			case ModStorageDataType.INT:
				ModStorageArrayRetrieverInt.WriteArray(value, m_Data);
				break;
			case ModStorageDataType.FLOAT:
				ModStorageArrayRetrieverFloat.WriteArray(value, m_Data);
				break;
			case ModStorageDataType.VECTOR:
				ModStorageArrayRetrieverVector.WriteArray(value, m_Data);
				break;
			case ModStorageDataType.STRING:
				ModStorageArrayRetrieverString.WriteArray(value, m_Data);
				break;
			case ModStorageDataType.ARRAY:
			case ModStorageDataType.CLASS:
				ModStorageArrayRetrieverClass.WriteArray(value, m_Data);
				break;
		}
		
		return true;
	}
};