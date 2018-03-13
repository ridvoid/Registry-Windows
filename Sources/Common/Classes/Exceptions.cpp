
#include "Exceptions.h"


namespace Seminar
{

	WinApiException::WinApiException(const std::wstring& wsText,
		DWORD dwErrCode) noexcept : wsText(wsText), dwErrCode(dwErrCode) { }

	std::wstring WinApiException::What(void) const
	{

		if (!this->dwErrCode)
			return this->wsText;

		LPVOID lpMsgBuf{};

		if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			{},
			this->dwErrCode,
			MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
			reinterpret_cast<LPWSTR>(&lpMsgBuf),
			{},
			{}))
			return this->wsText;

		std::wostringstream wos{};
		wos << this->wsText << std::endl;
		wos << L"Error code " << this->dwErrCode << std::endl;
		wos << reinterpret_cast<LPCWSTR>(lpMsgBuf);
		
		LocalFree(lpMsgBuf);

		return wos.str();

	}

	DWORD WinApiException::GetErrCode(void) const noexcept
	{

		return this->dwErrCode;

	}

}
