class CF_File : Managed
{
	protected string m_Directory;
	protected string m_FileName;
	protected string m_Extension;

	protected bool m_IsDirectory;
	protected bool m_IsHidden;
	protected bool m_IsReadOnly;
	protected bool m_IsValid;

	/**
	 * @brief Constructor
	 * 
	 * @param path No operation perform if path is empty string
	 */
	void CF_File(string path = "")
	{
		m_IsValid = true;

		// Default constructor
		if (path == string.Empty)
		{
			return;
		}

		string fileName;
		FileAttr fileAttr;
		FindFileHandle handle = FindFile(path, fileName, fileAttr, FindFileFlags.ALL);
		if (!handle)
		{
			return;
		}
		
		_SetFolder(CF_Path.GetDirectoryName(path));
		_SetFileName(fileName);
		_SetAttributes(fileAttr);
		
		CloseFindFile(handle);
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
		return m_IsValid;
	}

	/**
	 * @brief Returns the path, including file name and extension if they exist
	 */
	string GetFullPath()
	{
		return m_Directory + m_FileName + m_Extension;
	}

	/**
	 * @brief Returns the file name and extension
	 */
	string GetFileName()
	{
		return m_FileName + m_Extension;
	}

	/**
	 * @brief Returns the file name without the extension 
	 */
	string GetFileNameWithoutExtension()
	{
		return m_FileName;
	}

	/**
	 * @brief Returns the extension (including the period ".")
	 */
	string GetExtension()
	{
		return m_Extension;
	}

	/**
	 * @brief Returns the full path of the parent folder
	 */
	string GetDirectory()
	{
		return m_Directory;
	}

	/**
	 * @brief Creates and opens a new instance of a FileStream for the current file
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

		return new CF_FileStream(GetFullPath(), mode);
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

		return DeleteFile(GetFullPath());
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
		if (FileExist(m_Directory + name))
		{
			return false;
		}

		// Copy file to new name
		if (!CopyFile(GetFullPath(), m_Directory + name))
		{
			return false;
		}

		// Delete old file
		bool success = DeleteFile(GetFullPath());
		if (!success)
		{
			CF_Log.Warn("Failed to delete original file in rename for file \"%1\"", GetFullPath());
		}

		_SetFileName(name);

		return true;
	}

	/**
	 * @brief Moves the file to the new path (copy to folder, then delete original)
	 * 
	 * @param path The new path
	 * 
	 * @return true if the operation was successful
	 */
	bool Move(string path)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Move").Add(path);
#endif

		if (!IsValid())
		{
			return false;
		}

		string folder = CF_Path.GetDirectoryName(path);
		string name = CF_Path.GetFileNameEx(path, folder);

		// File isn't being renamed in move
		if (name == string.Empty)
		{
			name = GetFileName();
		}

		// Check if the file already exists at the destination
		if (FileExist(folder + name))
		{
			return false;
		}

		if (!CopyFile(GetFullPath(), folder + name))
		{
			return false;
		}

		// Delete old file
		bool success = DeleteFile(GetFullPath());
		if (!success)
		{
			CF_Log.Warn("Failed to delete original file in move for file \"%1\"", GetFullPath());
		}

		_SetFolder(folder);
		_SetFileName(name);

		return true;
	}

	/**
	 * @brief Copies the file to the new path
	 * 
	 * @param path The new path
	 * 
	 * @return true if the operation was successful
	 */
	bool Copy(string path)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Move").Add(path);
#endif

		if (!IsValid())
		{
			return false;
		}

		string folder = CF_Path.GetDirectoryName(path);
		string name = CF_Path.GetFileNameEx(path, folder);

		// File isn't being renamed in move
		if (name == string.Empty)
		{
			name = GetFileName();
		}

		// Check if the file already exists at the destination
		if (FileExist(folder + name))
		{
			CF_Log.Warn("The file already exists at \"%1\".", folder + name);
			return false;
		}

		if (!CopyFile(GetFullPath(), folder + name))
		{
			CF_Log.Warn("Failed to copy file to \"%1\".", folder + name);
			return false;
		}

		return true;
	}

	/**
	 * @brief Copies the file to the new path, returning the instance of the file
	 * 
	 * @param path The new path
	 * @param [out] newFile Outputs the new instance of the file
	 * 
	 * @return true if the operation was successful
	 */
	bool Copy(string path, out CF_File newFile)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Copy").Add(path);
#endif

		if (!IsValid())
		{
			return false;
		}

		string folder = CF_Path.GetDirectoryName(path);
		string name = CF_Path.GetFileNameEx(path, folder);

		// File isn't being renamed in move
		if (name == string.Empty)
		{
			name = GetFileName();
		}

		// Check if the file already exists at the destination
		if (FileExist(folder + name))
		{
			CF_Log.Warn("The file already exists at \"%1\".", folder + name);
			return false;
		}

		if (!CopyFile(GetFullPath(), folder + name))
		{
			CF_Log.Warn("Failed to copy file to \"%1\".", folder + name);
			return false;
		}

		newFile = new CF_File(path);

		return true;
	}

	override string GetDebugName()
	{
		return "{path=\"" + GetFullPath() + "\", filename=\"" + GetFileName() + "\", directory=" + m_IsDirectory.ToString() + ", hidden=" + m_IsHidden.ToString() + ", readonly=" + m_IsReadOnly.ToString() + ", valid=" + m_IsValid.ToString() + "}";
	}

	void _SetFolder(string folder)
	{
		m_Directory = folder;
	}

	void _SetFileName(CF_String fileName)
	{
		int index = fileName.CF_LastIndexOf(".");
		if (index == -1)
		{
			m_FileName = fileName;
			m_Extension = "";
			return;
		}

		m_Extension = fileName.Substring(index, fileName.Length() - index);
		m_FileName = fileName.Substring(0, fileName.Length() - m_Extension.Length());
	}

	void _SetAttributes(FileAttr fileAttr)
	{
		m_IsDirectory = (fileAttr & FileAttr.DIRECTORY) != 0;
		m_IsHidden = (fileAttr & FileAttr.HIDDEN) != 0;
		m_IsReadOnly = (fileAttr & FileAttr.READONLY) != 0;
		m_IsValid = (fileAttr & FileAttr.INVALID) != 0;
	}
};
