#pragma once
#include "Convert.h"

namespace Seminar
{

	std::wstring Convert::ToLower(const std::wstring& ws)
	{

		auto wsReturn = std::wstring(ws.size(), 
			{});
		
		std::transform(ws.cbegin(),
			ws.cend(),
			wsReturn.begin(),
			std::tolower);
		
		return wsReturn;

	}

	std::wstring Convert::EnvironmentPathToAbsolutePath(const std::wstring& wsPath)
	{

		auto sizeStart = wsPath.find('%');
		if (sizeStart == std::wstring::npos)
			return wsPath;

		auto sizeEnd = wsPath.find('%',
			sizeStart + std::size_t(1)) + std::size_t(1);
		if (sizeEnd == std::wstring::npos)
			return wsPath;

		std::wstring wsName(Convert::sizeMaxPathLen,
			{});

		auto dwSize = ExpandEnvironmentStrings(wsPath.substr(sizeStart, sizeEnd).c_str(),
			&wsName[0],
			static_cast<DWORD>(wsName.size()));
		if (!dwSize)
			throw ConvertException(L"Error ExpandEnvironmentStrings",
				GetLastError());

		std::wostringstream stream;
		stream << wsName.c_str() << wsPath.substr(sizeEnd);
		return stream.str();

	}

	std::wstring Convert::ToString(const std::vector<BYTE>& vec)
	{

		std::wstring wsReturn(vec.size() / sizeof(WCHAR) + 1,
			{});

		memcpy_s(&wsReturn[0],
			vec.size(),
			vec.data(),
			vec.size());

		return wsReturn.c_str();

	}

	std::wstring Convert::ToUnicode(const std::string& str,
		bool bException)
	{

		std::wstring wsReturn(str.size() + std::size_t(1),
			{ });

#pragma warning(push)
#pragma warning(disable : 4267)
		auto iRet = ::MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			str.c_str(),
			str.size(),
			&wsReturn[0],
			static_cast<int>(wsReturn.size()));
#pragma warning(pop)

		if (!iRet)
		{

			if (bException)
				throw ConvertException(L"Error MultiByteToWideChar",
					GetLastError());
			else
				wsReturn = {};
		
		}

		return wsReturn.c_str();

	}

}


