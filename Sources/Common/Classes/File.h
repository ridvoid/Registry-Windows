#pragma once

#include "..\Interfaces\IFile.h"

namespace Seminar
{

	class File : public IFile
	{

		File(void) = default;
		File(const File&) = delete;
		File(File&&) = delete;
		File& operator = (const File&) = delete;
		File& operator = (File&&) = delete;

	public:

		struct Settings
		{

			std::wstring wsFileName{};
			DWORD dwDesiredAccess{ GENERIC_READ };
			DWORD dwShareMode{ FILE_SHARE_READ };
			LPSECURITY_ATTRIBUTES lpSecurityAttributes{};
			DWORD dwCreationDisposition{ OPEN_EXISTING };
			DWORD dwFlagsAndAttributes{ FILE_ATTRIBUTE_NORMAL };
			HANDLE hTemplateFile{};

		};

	protected:

		Settings settings{};

	public:

		explicit File(const Settings&);

		virtual ~File(void) = default;

		static std::unique_ptr<IFile> Create(const Settings&);
		
	protected:

		IFile& Create(void) override;

	public:

		static DWORD GetAttributes(const std::wstring&);

		static void Delete(const std::wstring&);

		static void SetAttribute(const std::wstring&,
			DWORD = FILE_ATTRIBUTE_NORMAL);
		
	private:
	
		IFile& Connect(LPOVERLAPPED = {}) const override;

		IFile& Disconnect(void) const override;

		DWORD DeviceIoControl(DWORD,
			const std::vector<BYTE>&,
			std::vector<BYTE>&&,
			LPOVERLAPPED = {}) const override;

	};

}
