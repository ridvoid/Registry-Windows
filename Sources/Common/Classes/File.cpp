#pragma once
#include "File.h"

namespace Seminar
{

	File::File(const Settings& settings) : settings(settings) { }

	std::unique_ptr<IFile> File::Create(const Settings& settings)
	{

		return IFile::Create<File, Settings>(settings);

	}

	IFile& File::Create(void)
	{

		IFile::h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateFile(this->settings.wsFileName.c_str(),
			this->settings.dwDesiredAccess,
			this->settings.dwShareMode,
			this->settings.lpSecurityAttributes,
			this->settings.dwCreationDisposition,
			this->settings.dwFlagsAndAttributes,
			nullptr));
		if (!*IFile::h)
			throw FileException(L"Error CreateFile",
				GetLastError());

		return *this;

	}

	DWORD File::GetAttributes(const std::wstring& wsFile)
	{

		auto dwReturn = GetFileAttributes(wsFile.c_str());
		if (dwReturn == INVALID_FILE_ATTRIBUTES)
			throw FileException(L"Error GetFileAttributes",
				GetLastError());

		return dwReturn;

	}

	void File::Delete(const std::wstring& wsFile)
	{

		File::SetAttribute(wsFile);

		if (!DeleteFile(wsFile.c_str()))
			throw FileException(L"Error DeleteFile",
				GetLastError());

	}

	void File::SetAttribute(const std::wstring& wsFile,
		DWORD dwAttr)
	{

		if (!SetFileAttributes(wsFile.c_str(),
			dwAttr))
			throw FileException(L"Error SetFileAttributes",
				GetLastError());

	}

	IFile& File::Connect(LPOVERLAPPED) const
	{

		throw FileException(L"Connect",
			ERROR_NOT_SUPPORTED);

	}

	IFile& File::Disconnect(void) const
	{

		throw FileException(L"Disconnect",
			ERROR_NOT_SUPPORTED);

	}

	DWORD File::DeviceIoControl(DWORD,
		const std::vector<BYTE>&,
		std::vector<BYTE>&&,
		LPOVERLAPPED) const
	{

		throw FileException(L"DeviceIoControl",
			ERROR_NOT_SUPPORTED);

	}

}
