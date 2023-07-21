class CF_Path
{
	static string DIRECTORY_SEPARATOR = "/";
	static string ALT_DIRECTORY_SEPARATOR = "\\";
	static string FILESYSTEM_IDENTIFIER = ":";

	static autoptr array<string> DIRECTORY_CHECKS = { DIRECTORY_SEPARATOR, ALT_DIRECTORY_SEPARATOR, FILESYSTEM_IDENTIFIER };

	/**
	 * @brief Returns the directory information for the specified path.
	 * 
	 * @param path The path of a file or directory.
	 * 
	 * @return Directory information for path. Returns an empty string if path does not contain directory information.
	 */
	static string GetDirectoryName(CF_String path)
	{
		path.Replace(CF_Path.ALT_DIRECTORY_SEPARATOR, CF_Path.DIRECTORY_SEPARATOR);

		int index = path.CF_LastIndexOf(CF_Path.DIRECTORY_SEPARATOR);
		if (index != -1)
		{
			return path.Substring(0, index) + CF_Path.DIRECTORY_SEPARATOR;
		}

		index = path.CF_LastIndexOf(CF_Path.FILESYSTEM_IDENTIFIER);
		if (index != -1)
		{
			return path.Substring(0, index) + CF_Path.FILESYSTEM_IDENTIFIER;
		}

		return string.Empty;
	}

	/**
	 * @brief Returns the file name and extension of the specified path string.
	 * 
	 * @param path The path string from which to obtain the file name and extension.
	 * 
	 * @return The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.
	 */
	static string GetFileName(string path)
	{
		return GetFileNameEx(path, GetDirectoryName(path));
	}

	/**
	 * @brief Returns the file name and extension of the specified path string.
	 * 
	 * @param path The path string from which to obtain the file name and extension.
	 * 
	 * @return The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.
	 */
	static string GetFileNameEx(string path, string folder)
	{
		int start = folder.Length();
		int end = path.Length() - folder.Length();
		if (end <= 0)
		{
			return string.Empty;
		}

		if (DIRECTORY_CHECKS.Find(path[end]) != -1)
		{
			return string.Empty;
		}

		return path.Substring(start, end);
	}

	/**
	 * @brief Returns the file name of the specified path string.
	 * 
	 * @param path The path string from which to obtain the file name.
	 * 
	 * @return The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.
	 */
	static string GetFileNameWithoutExtension(string path)
	{
		return GetFileNameWithoutExtensionEx(path, GetDirectoryName(path));
	}

	/**
	 * @brief Returns the file name of the specified path string.
	 * 
	 * @param path The path string from which to obtain the file name.
	 * 
	 * @return The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.
	 */
	static string GetFileNameWithoutExtensionEx(string path, string folder)
	{
		int start = folder.Length();
		int end = path.Length() - folder.Length();
		if (end <= 0)
		{
			return string.Empty;
		}

		if (DIRECTORY_CHECKS.Find(path[end]) != -1)
		{
			return string.Empty;
		}

		CF_String fileName = path.Substring(start, end);

		int index = fileName.CF_LastIndexOf(".");
		if (index != -1)
		{
			fileName = fileName.Substring(0, index);
		}
	
		return fileName;
	}

	/**
	 * @brief Returns the extension (including the period ".") of the specified path string.
	 * 
	 * @param path The path string from which to get the extension.
	 * 
	 * @return The path string from which to get the extension. If path does not have extension information, this method returns an empty string.
	 */
	static string GetExtension(CF_String path)
	{
		int index = path.CF_LastIndexOf(".");
		if (index == -1)
		{
			return string.Empty;
		}

		return path.Substring(index, path.Length() - index);
	}
};
