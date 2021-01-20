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

	bool Insert(TKey key, TValue value)
	{
		if (_data.Insert(key, value))
		{
			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Insert, _dataArray.Insert(value), new Param1<TValue>(value)));
			return true;
		}

		return false;
	}

	void Remove(TKey key)
	{
		if (_data.Contains(key))
		{
			TValue value = _data.Get(key);
			_data.Remove(key);

			int remove_index = _dataArray.Find(value);
			if (remove_index >= 0) _dataArray.RemoveOrdered(remove_index);

			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, remove_index, new Param1<TValue>(value)));
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