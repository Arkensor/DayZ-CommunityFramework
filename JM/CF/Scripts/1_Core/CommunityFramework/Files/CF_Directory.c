class CF_Directory
{
	/**
	 * @param pattern The search pattern
	 * @param [inout] files An array where the list of files will be written to
	 * @param flags If it should be looked in directories or .pak files, or both
	 * 
	 * @return If the pattern was valid
	 */
	static bool GetFiles(string pattern, inout array<ref CF_File> files, FindFileFlags flags = 2)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3("CF_Directory", "GetFiles").Add(pattern).Add(files).Add(flags);
#endif

		if (!files)
		{
			files = new array<ref CF_File>();
		}

		pattern.Replace("\\", CF_Path.DIRECTORY_SEPARATOR);

		string fileName;
		FileAttr fileAttr;
		FindFileHandle handle = FindFile(pattern, fileName, fileAttr, flags);
		if (!handle)
		{
			return false;
		}

		string folder = CF_Path.GetDirectoryName(pattern);

		CF_File file;
		while (true)
		{
			file = new CF_File();

			file._SetFileName(fileName);
			file._SetFolder(folder);
			file._SetAttributes(fileAttr);

			files.Insert(file);

			if (!FindNextFile(handle, fileName, fileAttr))
			{
				break;
			}
		}

		CloseFindFile(handle);
		
		return true;
	}
};
