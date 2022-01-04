class CF_File : Managed
{
	static string DIRECTORY_SEPARATOR = "/";
	static string FILESYSTEM_IDENTIFIER = ":";

	protected string m_FileName;
	protected string m_Folder;
	protected bool m_IsDirectory;
	protected bool m_IsHidden;
	protected bool m_IsReadOnly;
	protected bool m_IsValid;

	/**
	 * @param pattern The search pattern
	 * @param [inout] files An array where the list of files will be written to
	 * @param flags If it should be looked in directories or .pak files, or both
	 * 
	 * @return If the pattern was valid
	 */
	static bool Find(string pattern, inout array<ref CF_File> files, FindFileFlags flags = 2)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3("CF_File", "Find").Add(pattern).Add(files).Add(flags);
#endif

		if (!files)
		{
			files = new array<ref CF_File>();
		}

		pattern.Replace("\\", CF_File.DIRECTORY_SEPARATOR);

		string fileName;
		FileAttr fileAttr;
		FindFileHandle handle = FindFile(pattern, fileName, fileAttr, flags);
		if (!handle)
		{
			return false;
		}

		string folder = PatternToFolder(pattern);

		CF_File file;
		while (true)
		{
			file = new CF_File();
			file.m_FileName = fileName;

			if (file.SetFolder(folder))
			{
				file.m_IsDirectory = fileAttr & FileAttr.DIRECTORY;
				file.m_IsHidden = fileAttr & FileAttr.HIDDEN;
				file.m_IsReadOnly = fileAttr & FileAttr.READONLY;
				file.m_IsValid = !(fileAttr & FileAttr.INVALID);
				files.Insert(file);
			}

			if (!FindNextFile(handle, fileName, fileAttr))
			{
				break;
			}
		}

		CloseFindFile(handle);
		return true;
	}

	static string PatternToFolder(string pattern)
	{
		int index;
		CF_String folder = pattern;

		index = folder.CF_LastIndexOf(CF_File.DIRECTORY_SEPARATOR);
		if (index != -1)
		{
			return folder.Substring(0, index) + CF_File.DIRECTORY_SEPARATOR;
		}

		index = folder.CF_LastIndexOf(CF_File.FILESYSTEM_IDENTIFIER);
		if (index != -1)
		{
			return folder.Substring(0, index) + CF_File.FILESYSTEM_IDENTIFIER;
		}

		return "";
	}

	bool IsDirectory()
	{
		return m_IsDirectory;
	}

	bool IsHidden()
	{
		return m_IsHidden;
	}

	bool IsReadOnly()
	{
		return m_IsReadOnly;
	}

	bool IsValid()
	{
		if (m_Folder == string.Empty)
		{
			return false;
		}

		return m_IsValid;
	}

	string GetFileName()
	{
		return m_FileName;
	}

	/**
	 * @brief Sets the folder the file is in
	 *
	 * @param folder The folder the file is in
	 * 
	 * @return true if the file does exist in the designated folder
	 */
	protected bool SetFolder(string folder)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetFolder").Add(folder);
#endif

		if (!FileExist(folder + m_FileName))
		{
			CF_Log.Error("Failed to set folder for file \"%1\" to \"%2\"", m_FileName, folder);
			return false;
		}

		m_Folder = folder;
		return true;
	}

	string GetFolder()
	{
		return m_Folder;
	}

	/**
	 * @brief Creates and opens a new instance of a FileStream for the current file
	 * 
	 * @note 'SetFolder' must be called on this instance beforehand
	 * 
	 * @param mode Sets the file mode the stream will be opened in
	 * 
	 * @return new instance of CF_FileStream
	 */
	CF_Stream CreateStream(FileMode mode)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "CreateStream").Add(mode);
#endif

		if (!IsValid())
		{
			return null;
		}

		return new CF_FileStream(m_Folder + m_FileName, mode);
	}

	/**
	 * @brief Deletes the current file
	 * 
	 * @return true if the operation was successful
	 */
	bool Delete()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Delete");
#endif

		if (!IsValid())
		{
			return false;
		}

		return DeleteFile(m_Folder + m_FileName);
	}

	/**
	 * @brief Renames the current file (copy to new name, then delete original)
	 * 
	 * @param name The new name of the file
	 * 
	 * @return true if the operation was successful
	 */
	bool Rename(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Rename").Add(name);
#endif

		if (!IsValid())
		{
			return false;
		}

		// Check if the file already exists at the destination
		if (FileExist(m_Folder + name))
		{
			return false;
		}

		// Copy file to new name
		if (!CopyFile(m_Folder + m_FileName, m_Folder + name))
		{
			return false;
		}

		// Delete old file
		bool success = DeleteFile(m_Folder + m_FileName);
		if (!success)
		{
			CF_Log.Warn("Failed to delete original file in rename for file \"%1%2\"", m_Folder, m_FileName);
		}

		m_FileName = name;

		return true;
	}

	/**
	 * @brief Moves the file to the new folder (copy to folder, then delete original)
	 * 
	 * @param folder The new parent folder
	 * @param name The new name of the file
	 * 
	 * @return true if the operation was successful
	 */
	bool Move(string folder, string name = "")
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Move").Add(folder).Add(name);
#endif

		if (!IsValid())
		{
			return false;
		}

		// File isn't being renamed in move
		if (name == string.Empty)
		{
			name = m_FileName;
		}

		// Check if the file already exists at the destination
		if (FileExist(folder + name))
		{
			return false;
		}

		if (!CopyFile(m_Folder + m_FileName, folder + name))
		{
			return false;
		}

		// Delete old file
		bool success = DeleteFile(m_Folder + m_FileName);
		if (!success)
		{
			CF_Log.Warn("Failed to delete original file in move for file \"%1%2\"", m_Folder, m_FileName);
		}

		m_FileName = name;
		m_Folder = folder;

		return true;
	}

	override string GetDebugName()
	{
		return "{path=\"" + m_Folder + m_FileName + "\", filename=\"" + m_FileName + "\", directory=" + m_IsDirectory.ToString() + ", hidden=" + m_IsHidden.ToString() + ", readonly=" + m_IsReadOnly.ToString() + ", valid=" + m_IsValid.ToString() + "}";
	}
};
