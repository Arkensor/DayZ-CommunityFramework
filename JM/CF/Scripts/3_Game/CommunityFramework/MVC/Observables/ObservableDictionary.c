class ObservableDictionary<Class TKey, Class TValue> : Observable
{
	private	ref map<TKey, ref TValue> _data = new map<TKey, ref TValue>();
	private	ref array<TValue> _dataArray = {};

	void ObservableDictionary(Controller controller)
	{
		m_Type = TemplateType<TValue>.GetType();
	}

	void ~ObservableDictionary()
	{
		delete _data;
		delete _dataArray;
	}

	int Insert(TKey key, TValue value)
	{
		if (_data.Insert(key, value))
		{
			int index = _dataArray.Insert(value);
			if (index == -1)
			{
				Error("Inserted into map but failed to insert into array so FML.");
				return -1;
			}
			
			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Insert, index, new Param1<TValue>(value)));
			return index;
		}

		return -1;
	}

	void Remove(TKey key)
	{
		if (_data.Contains(key))
		{
			TValue value = _data.Get(key);

			int remove_index = _dataArray.Find(value);
			if (remove_index >= 0) _dataArray.RemoveOrdered(remove_index);

			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, remove_index, new Param1<TValue>(value)));
			
			_data.Remove(key);
		}
	}

	void Remove(int index)
	{
		TValue value = _dataArray.Get(index);
		_dataArray.Remove(index);

		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, index, new Param1<TValue>(value)));

		_data.Remove(_data.GetKeyByValue(value));
	}

	void RemoveRange(int start, int end)
	{
		for (int i = start; i < end; i++)
		{
			int index = start;
			
			TValue value = _dataArray.Get(index);
			_dataArray.Remove(index);

			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, index, new Param1<TValue>(value)));

			_data.Remove(_data.GetKeyByValue(value));
		}
	}

	void Clear()
	{
		_data.Clear();
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Clear, -1, null));
	}

	void Set(TKey key, TValue value)
	{
		int remove_index = -1;

		if (_data.Contains(key))
		{
			remove_index = _dataArray.Find(_data.Get(key));
			if (remove_index >= 0) _dataArray.Set(remove_index, value);
		}

		_data.Set(key, value);
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Replace, remove_index, new Param1<TValue>(value)));
	}

	int MoveIndex(int index, int moveIndex)
	{
		if (moveIndex == index)
			return index;
		
		TValue value = _dataArray.Get(index);
		int new_index = _dataArray.MoveIndex(index, moveIndex);
		if (new_index != index)
			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Move, new_index, new Param1<TValue>(value)));
		
		return new_index;
	}

	TValue Get(TKey key)
	{
		return _data.Get(key);
	}

	TKey GetKey(int index)
	{
		return _data.GetKey(index);
	}

	bool Contains(TKey key)
	{
		return _data.Contains(key);
	}

	override int Count()
	{
		return _data.Count();
	}
};