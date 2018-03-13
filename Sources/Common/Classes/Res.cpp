
#include "Res.h"

namespace Seminar
{

	void Res::SaveResourceByNameToFile(const std::wstring& wsFile,
		LPCWSTR lpcwsName,
		LPCWSTR lpcwsType)
	{
		
		auto vecBuf = Res::GetResourceByName(GetModuleHandle({}),
			lpcwsName,
			lpcwsType);

		std::ofstream ofs(wsFile,
			std::ios::binary);
		if (!ofs)
			throw ResourceException(L"Error save resource to file",
				::GetLastError());

		std::copy(vecBuf.cbegin(),
			vecBuf.cend(),
			std::ostream_iterator<BYTE>(ofs));

	}

	std::vector<BYTE> Res::GetResourceByName(HMODULE hMod,
		LPCWSTR lpcwsName,
		LPCWSTR lpcwsType)
	{
		
		auto hRc = FindResource(hMod,
			lpcwsName,
			lpcwsType);
		if (!hRc)
			throw ResourceException(L"Error FindResource",
				GetLastError());

		auto dwSize = SizeofResource(hMod,
			hRc);
		if (!dwSize)
			throw ResourceException(L"Error SizeofResource",
				GetLastError());

		auto hGlob = LoadResource(hMod,
			hRc);
		if (!hGlob)
			throw ResourceException(L"Error LoadResource",
				GetLastError());

		return std::vector<BYTE>(static_cast<LPCBYTE>(LockResource(hGlob)),
			static_cast<LPCBYTE>(LockResource(hGlob)) + static_cast<std::size_t>(dwSize));

	}

}

