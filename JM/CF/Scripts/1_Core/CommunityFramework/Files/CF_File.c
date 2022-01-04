class CF_File : Managed
{
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

		string fileName;
		FileAttr fileAttr;
		FindFileHandle handle = FindFile(pattern, fileName, fileAttr, flags);
		if (!handle)
		{
			return false;
		}

		CF_File file;
		while (true)
		{
			file = new CF_File();
			file.m_FileName = fileName;
			file.m_IsDirectory = fileAttr & FileAttr.DIRECTORY;
			file.m_IsHidden = fileAttr & FileAttr.HIDDEN;
			file.m_IsReadOnly = fileAttr & FileAttr.READONLY;
			file.m_IsValid = !(fileAttr & FileAttr.INVALID);
			files.Insert(file);

			if (!FindNextFile(handle, fileName, fileAttr))
			{
				break;
			}
		}

		CloseFindFile(handle);
		return true;
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

	bool SetFolder(string folder)
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

	bool Delete(string folder = "")
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Delete").Add(folder);
#endif

		if (folder != string.Empty && !SetFolder(folder))
		{
			return false;
		}

		return DeleteFile(m_Folder + m_FileName);
	}

	bool Rename(string name, string folder = "")
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Rename").Add(name).Add(folder);
#endif

		if (folder != string.Empty && !SetFolder(folder))
		{
			return false;
		}

		if (!CopyFile(m_Folder + m_FileName, m_Folder + name))
		{
			return false;
		}

		bool success = DeleteFile(m_Folder + m_FileName);
		if (!success)
		{
			CF_Log.Warn("Failed to delete original file in rename for file \"%1%2\"", m_Folder, m_FileName);
		}

		m_FileName = name;

		return true;
	}

	override string GetDebugName()
	{
		return "{filename=\"" + m_FileName + "\", directory=" + m_IsDirectory.ToString() + ", hidden=" + m_IsHidden.ToString() + ", readonly=" + m_IsReadOnly.ToString() + ", valid=" + m_IsValid.ToString() + "}";
	}
};
