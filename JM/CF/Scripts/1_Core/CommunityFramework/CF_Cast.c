class CF_Cast<Class U, Class V>
{
	static V Reinterpret(U src)
	{
		U src_arr[1];
		src_arr[0] = src;
		V dst_arr[1];

		copyarray(dst_arr, src_arr);

		return dst_arr[0];
	}
};
