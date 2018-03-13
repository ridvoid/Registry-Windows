

#include "Device.h"

namespace Seminar
{

	std::unique_ptr<IFile> Device::Create(const std::wstring& wsName)
	{

		std::wostringstream wos;
		wos << L"\\\\.\\" << wsName;

		File::Settings settings{};
		settings.wsFileName = wos.str();
		settings.dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		settings.dwCreationDisposition = OPEN_EXISTING;

		return IFile::Create<Device, File::Settings>(settings);
	
	}

	DWORD Device::DeviceIoControl(DWORD dwIoControlCode,
			const std::vector<BYTE>& vecIn,
			std::vector<BYTE>&& vecOut,
			LPOVERLAPPED lpOverlapped) const
	{

		DWORD dwReturn{};

		if(!::DeviceIoControl(*this,
			dwIoControlCode,
			const_cast<std::vector<BYTE>&>(vecIn).data(),
			static_cast<DWORD>(const_cast<std::vector<BYTE>&>(vecIn).size()),
			vecOut.data(),
			static_cast<DWORD>(vecOut.size()),
			&dwReturn,
			lpOverlapped))
			throw DeviceException(L"Error DeviceIoControl",
				GetLastError());

		return dwReturn;

	}

}
