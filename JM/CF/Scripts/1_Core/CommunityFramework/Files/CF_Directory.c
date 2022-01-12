class CF_Directory
{
	/**
	 * @param pattern The search pattern
	 * @param [inout] files An array where the list of files will be written to
	 * @param flags If it should be looked in directories or .pak files, or both
	 * 
	 * @return If any files were found that matched the pattern
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

	/**
	 * @brief Creates all directories and subdirectories in the specified path unless they already exist. 
	 * 
	 * @param directory The directory to create.
	 * 
	 * @return If the directories could be created
	 */
	static bool CreateDirectory(string directory)
	{
		array<string> directories();
		string path = directory;

		string previousPath = "";
		while (true)
		{
			previousPath = path;
			if (FileExist(previousPath))
			{
				break;
			}
			
			path = CF_Path.GetDirectoryName(path);
			if (previousPath == path)
			{
				path = previousPath;
				break;
			}
			
			if (previousPath[previousPath.Length() - 1] == CF_Path.FILESYSTEM_IDENTIFIER)
			{
				return false;
			}
			
			directory = CF_Path.GetFileNameEx(previousPath, path);
			directory = directory.Substring(0, directory.Length() - 1);

			directories.Insert(directory);
		}

		for (int i = directories.Count() - 1; i >= 0; i--)
		{
			path = path + directories[i] + CF_Path.DIRECTORY_SEPARATOR;
			
			if (!MakeDirectory(path))
			{
				return false;
			}
		}

		return true;
	}
};
