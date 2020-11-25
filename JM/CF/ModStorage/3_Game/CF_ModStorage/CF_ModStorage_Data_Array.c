typedef CF_ModStorage_Data_Array<bool> CF_ModStorage_Data_Array_Bool;
typedef CF_ModStorage_Data_Array<int> CF_ModStorage_Data_Array_Int;
typedef CF_ModStorage_Data_Array<float> CF_ModStorage_Data_Array_Float;
typedef CF_ModStorage_Data_Array<vector> CF_ModStorage_Data_Array_Vector;
typedef CF_ModStorage_Data_Array<string> CF_ModStorage_Data_Array_String;

class CF_ModStorage_Data_Array<Class T> : CF_ModStorage_Data
{
	protected Class m_Value;

	protected string m_Type = "";
	protected autoptr array<ref CF_ModStorage_Data> m_Data = new ref array<ref CF_ModStorage_Data>();

	void CF_ModStorage_Data_Array(Class value)
	{
		m_Value = value;
	}

	override void OnSet()
	{
		if (!m_Value)
        {
            m_Type = "";
            return;
        }
		
		CF_ModStorage_Converter.GetArrayType(m_Value.Type(), m_Type).ReadArray(m_Value, m_Data);
    }

	override void Write(ParamsWriteContext ctx)
	{
		ctx.Write(m_VariableName);
		ctx.Write(m_Type);

		int count = m_Data.Count();
		ctx.Write(count);

		for (int i = 0; i < count; i++)
		{
			ctx.Write(m_Data[i].GetType().ToString());
			m_Data[i].Write(ctx);
		}
	}

	override void Read(ParamsReadContext ctx)
	{
		ctx.Read(m_VariableName);
		ctx.Read(m_Type);

		int count;
		ctx.Read(count);

		for (int i = 0; i < count; i++)
		{
			m_Data.Insert(CF_ModStorage_Converter.Read(ctx));
		}
	}
	
	override typename GetType()
	{
		if (T == bool)
			return TBoolArray;
		if (T == int)
			return TIntArray;
		if (T == float)
			return TFloatArray;
		if (T == vector)
			return TVectorArray;
		if (T == string)
			return TStringArray;
		return TClassArray;
	}

	override bool Get(inout Class cls)
	{
		if (!cls)
			return true;

		CF_ModStorage_Converter.GetArrayType(m_Value.Type(), m_Type).WriteArray(cls, m_Data);
		
		return true;
	}
};

class CF_ModStorage_Data_Array_Class<Class T> : CF_ModStorage_Data
{
	protected Class m_Value;

	protected string m_Type = "";
	protected autoptr array<ref CF_ModStorage_Data> m_Data = new ref array<ref CF_ModStorage_Data>();

	void CF_ModStorage_Data_Array_Class(Class value)
	{
		m_Value = value;
	}

	override void OnSet()
	{
		if (!m_Value)
        {
            m_Type = "";
            return;
        }
		
		CF_ModStorage_Data_ArrayProperty prop = new CF_ModStorage_Data_ArrayProperty_Class<T>();
		prop.ReadArray(m_Value, m_Data);
    }

	override void Write(ParamsWriteContext ctx)
	{
		ctx.Write(m_VariableName);
		ctx.Write(m_Type);

		int count = m_Data.Count();
		ctx.Write(count);

		for (int i = 0; i < count; i++)
		{
			ctx.Write(m_Data[i].GetType().ToString());
			m_Data[i].Write(ctx);
		}
	}

	override void Read(ParamsReadContext ctx)
	{
		ctx.Read(m_VariableName);
		ctx.Read(m_Type);

		int count;
		ctx.Read(count);

		for (int i = 0; i < count; i++)
		{
			m_Data.Insert(CF_ModStorage_Converter.Read(ctx));
		}
	}
	
	override typename GetType()
	{
		return Type();
	}
	
	override bool Get(inout Class cls)
	{
		if (!cls)
			return true;

		CF_ModStorage_Data_ArrayProperty prop = new CF_ModStorage_Data_ArrayProperty_Class<T>();
		prop.WriteArray(cls, m_Data);
		
		return true;
	}
};

class CF_ModStorage_Data_ArrayProperty
{
	void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
	}
	
	void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
	}
};

class CF_ModStorage_Data_ArrayProperty_String : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		TStringArray srcArr = TStringArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			_dstArr.Insert(new CF_ModStorage_Data_String(srcArr[i]));
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
		TStringArray dstArr = TStringArray.Cast(cls);
		for (int i = 0; i < _srcArr.Count(); i++)
		{
			dstArr.Insert(Param1<string>.Cast(_srcArr[i].Get()).param1);
		}
	}
};

class CF_ModStorage_Data_ArrayProperty_Float : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		TFloatArray srcArr = TFloatArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			_dstArr.Insert(new CF_ModStorage_Data_Float(srcArr[i]));
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
		TFloatArray dstArr = TFloatArray.Cast(cls);
		for (int i = 0; i < _srcArr.Count(); i++)
		{
			dstArr.Insert(Param1<float>.Cast(_srcArr[i].Get()).param1);
		}
	}
};

class CF_ModStorage_Data_ArrayProperty_Vector : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		TVectorArray srcArr = TVectorArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			_dstArr.Insert(new CF_ModStorage_Data_Vector(srcArr[i]));
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
		TVectorArray dstArr = TVectorArray.Cast(cls);
		for (int i = 0; i < _srcArr.Count(); i++)
		{
			dstArr.Insert(Param1<vector>.Cast(_srcArr[i].Get()).param1);
		}
	}
};

class CF_ModStorage_Data_ArrayProperty_Int : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		TIntArray srcArr = TIntArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			_dstArr.Insert(new CF_ModStorage_Data_Int(srcArr[i]));
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
		TIntArray dstArr = TIntArray.Cast(cls);
		for (int i = 0; i < _srcArr.Count(); i++)
		{
			dstArr.Insert(Param1<int>.Cast(_srcArr[i].Get()).param1);
		}
	}
};

class CF_ModStorage_Data_ArrayProperty_Bool : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		TBoolArray srcArr = TBoolArray.Cast(cls);
		for (int i = 0; i < srcArr.Count(); i++)
		{
			_dstArr.Insert(new CF_ModStorage_Data_Bool(srcArr[i]));
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
		TBoolArray dstArr = TBoolArray.Cast(cls);
		for (int i = 0; i < _srcArr.Count(); i++)
		{
			dstArr.Insert(Param1<bool>.Cast(_srcArr[i].Get()).param1);
		}
	}
};

class CF_ModStorage_Data_ArrayProperty_Class<Class T> : CF_ModStorage_Data_ArrayProperty
{
	override void ReadArray(inout Class cls, ref array< ref CF_ModStorage_Data > _dstArr)
	{
		ref CF_ModStorage_Data data;
		int i;
		
		array<T> srcArr;
		if (Class.CastTo(srcArr, cls))
		{
			for (i = 0; i < srcArr.Count(); i++)
			{
				data = new CF_ModStorage_Data_Class(srcArr[i]);
				data.OnSet();
				_dstArr.Insert(data);
			}
			
			return;
		}
		
		array<ref T> srcArrR;
		if (Class.CastTo(srcArrR, cls))
		{
			for (i = 0; i < srcArrR.Count(); i++)
			{
				data = new CF_ModStorage_Data_Class(srcArrR[i]);
				data.OnSet();
				_dstArr.Insert(data);
			}
			
			return;
		}
	}
	
	override void WriteArray(inout Class cls, ref array< ref CF_ModStorage_Data > _srcArr)
	{
	    Class value;
		int i;
		
		array<T> dstArr;
		if (Class.CastTo(dstArr, cls))
		{
			for (i = 0; i < _srcArr.Count(); i++)
			{
	            if (_srcArr[i].Get(value))
	            {
	                dstArr.Insert(value);
	            }
			}
		}
		
		array<ref T> dstArrR;
		if (Class.CastTo(dstArrR, cls))
		{
			for (i = 0; i < _srcArr.Count(); i++)
			{
	            if (_srcArr[i].Get(value))
	            {
	                dstArrR.Insert(value);
	            }
			}
		}
	}
};