class CF_ObservableArray<Class T> : CF_ObservableCollection
{
	private ref array<autoptr T> m_Data = new array<autoptr T>();

	void CF_ObservableArray()
	{
		#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
		#endif

		typename t = T;
		CF_Trace trace(this, string.Format("CF_ObservableArray<%1>", "" + t));

		m_Converter = CF.TypeConverters.Create(t);

		CF.Log.Info("m_Converter=%1", "" + m_Converter);
	}

	override string String()
	{
		string str = super.String();
		str += "Count: " + m_Data.Count();
		for (int i = 0; i < m_Data.Count(); i++)
		{
			str += " " + m_Data[i];
		}
		return str;
	}

	override CF_TypeConverter GetConverter(int index)
	{
		CF_Trace trace(this, "GetConverter", "" + index);
		
		g_Script.CallFunction(m_Converter, "Set", null, m_Data[index]);
		return m_Converter;
	}

	/*!
	O(1) complexity.
	\return Number of elements of the array
	*/
	override int Count()
	{
		return m_Data.Count();
	}

	/*!
	Destroyes all elements of the array and sets the Count to 0.
	The underlying memory of the array is not freed.
	*/
	void Clear()
	{
		m_Data.Clear();

		NotifyCollectionChanged(new CF_CollectionClearEventArgs());
	}

	/*!
	Sets n-th element to given value.
	*/
	void Set(int n, T value)
	{
		m_Data.Set(n, value);

		NotifyCollectionChanged(new CF_CollectionSetEventArgs(n));
	}

	/*!
	Tries to find the first occurance of given value in the array.
	\return Index of the first occurance of `value` if found, -1 otherwise
	*/
	int Find(T value)
	{
		return m_Data.Find(value);
	}

	/*!
	\return Element at the index `n`
	*/
	T Get(int index)
	{
		return m_Data[index];
	}

	/*!
	Inserts element at the end of array.
	\param value
	Element to be inserted
	\return
	Position at which element is inserted
	*/
	void Insert(T value)
	{
		int index = m_Data.Insert(value);

		NotifyCollectionChanged(new CF_CollectionInsertEventArgs(index));
	}

	/*!
	Inserts element at certain position and moves all elements behind
	this position by one.
	\param value
	Element to be inserted
	\param index
	Position at which element is inserted. Must be less than Array::GetCardinality()
	\return
	Number of elements after insertion
	*/
	int InsertAt(T value, int index)
	{
		int idx = m_Data.InsertAt(value, index);

		NotifyCollectionChanged(new CF_CollectionInsertAtEventArgs(idx));

		return idx;
	}

	/**
	\brief Inserts all elements from array
		\param from \p array<T> array from which all elements will be added
		@code
			TStringArray arr1 = new TStringArray;
			arr1.Insert( "Dave" );
			arr1.Insert( "Mark" );
			arr1.Insert( "John" );
			
			TStringArray arr2 = new TStringArray;
			arr2.Insert( "Sarah" );
			arr2.Insert( "Cate" );
			
			arr1.InsertAll(arr2);
			
			for ( int i = 0; i < arr1.Count(); i++ )
			{
				Print( arr1.Get(i) );
			}
			
			delete arr2;
			delete arr1;

			>> "Dave"
			>> "Mark"
			>> "John"
			>> "Sarah"
			>> "Cate"
		@endcode
	*/
	void InsertAll(notnull array<T> from)
	{
		m_Data.InsertAll(from);
	}

	void InsertAll(notnull CF_ObservableArray<T> from)
	{
		//m_Data.InsertAll(from.m_Data);
	}

	/*!
	Removes element from array. The empty position is replaced by
	last element, so removal is quite fast but do not retain order.
	\param index
	Index of element to be removed
	*/
	void Remove(int index)
	{
		if (m_Data.Count() <= 1) NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(index));

		m_Data.Remove(index);

		if (m_Data.Count() > 0 && index < m_Data.Count()) NotifyCollectionChanged(new CF_CollectionSetEventArgs(index));
	}

	/*!
	Removes element from array, but retain all elements ordered. It's
	slower than Remove
	\param index
	Index of element to be removed
	*/
	void RemoveOrdered(int index)
	{
		NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(index));

		m_Data.RemoveOrdered(index);
	}

	/*!
	Resizes the array to given size.
	If the `newSize` is lower than current Count overflowing objects are destroyed.
	If the `newSize` is higher than current Count missing elements are initialized to zero (null).
	*/
	void Resize(int newSize)
	{
		m_Data.Resize(newSize);
	}

	/*!
	Swaps the contents of this and `other` arrays.
	Does not involve copying of the elements.
	*/
	void Swap(notnull array<T> other)
	{
		m_Data.Swap(other);
	}

	/*!
	Swaps the contents of this and `other` arrays.
	Does not involve copying of the elements.
	*/
	void Swap(notnull CF_ObservableArray<T> other)
	{
		//m_Data.Swap(other.m_Data);
	}

	/*!
	Sorts elements of array, depends on underlaying type.
	*/
	void Sort(bool reverse = false)
	{
		m_Data.Sort(reverse);
	}

	/*!
	Copies contents of `from` array to this array.
	\return How many elements were copied
	*/
	int Copy(notnull array<T> from)
	{
		return 0;//m_Data.Copy(from);
	}

	int Copy(notnull CF_ObservableArray<T> from)
	{
		return 0;//m_Data.Copy(from.m_Data);
	}

	int Init(T init[])
	{
		return m_Data.Init(init);
	}

	void RemoveItem(T value)
	{
		m_Data.RemoveItem(value);
	}
	
	void RemoveItemUnOrdered(T value)
	{
		m_Data.RemoveItemUnOrdered(value);
	}
	
	bool IsValidIndex( int index )
	{
		return m_Data.IsValidIndex(index);
	}

	/**
	\brief Print all elements in array
		\return \p void
		@code
			my_array.Debug();

			>> "One"
			>> "Two"
			>> "Three"
		@endcode
	*/
	void Debug()
	{
		m_Data.Debug();
	}

	/**
	\brief Returns a random index of array. If Count is 0, return index is -1 .
		\return \p int Random index of array
		@code
			Print( my_array.GetRandomIndex() );

			>> 2
		@endcode
	*/
	int GetRandomIndex()
	{
		return m_Data.GetRandomIndex();
	}

	/**
	\brief Returns a random element of array
		\return \p int Random element of array
		@code
			Print( my_array.GetRandomElement() );

			>> "Three"
		@endcode
	*/
	T GetRandomElement()
	{
		return m_Data.GetRandomElement();
	}

	void SwapItems(int item1_index, int item2_index)
	{
		NotifyCollectionChanged(new CF_CollectionSwapEventArgs(item1_index, item2_index));

		m_Data.SwapItems(item1_index, item2_index);
	}
	
	void InsertArray(array<T> other)
	{
		m_Data.InsertArray(other);
	}
	
	void InsertArray(CF_ObservableArray<T> other)
	{
		//m_Data.InsertArray(other.m_Data);
	}
	
	void Invert()
	{
		m_Data.Invert();
	}
	
	/**
	\brief Returns a index in array moved by specific number
		\return \p int Moved index in this array
		@code
			Print( "Count: "+ my_array.Count() );
			Print( "Moved 1:"+ my_array.MoveIndex(2, 1) );
			Print( "Moved 3:"+ my_array.MoveIndex(2, 2) );

			>> "Count: 4"
			>> "Moved index 2 by 1: 3";
			>> "Moved index 2 by 2: 0";
		@endcode
	*/
	int MoveIndex(int curr_index, int move_number)
	{
		return m_Data.MoveIndex(curr_index, move_number);
	}
};