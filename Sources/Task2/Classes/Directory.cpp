
#include "Directory.h"

namespace Seminar
{

	std::wstring Directory::GetCurDir(void)
	{

		std::wstring wsReturn(Directory::sizeMaxPathLen,
			{});

		auto dwResult = GetModuleFileName({},
			&wsReturn[0],
			static_cast<DWORD>(wsReturn.size() - 1));
		if (!dwResult)
			throw DirectoryException(L"Error GetModuleFileName",
				GetLastError());

		wsReturn.resize(dwResult);

		auto sizePos = wsReturn.rfind('\\');
		if(sizePos == std::wstring::npos)
			throw DirectoryException(L"Error",
				ERROR_INVALID_PARAMETER);

		return wsReturn.substr({},
			sizePos);

	}

}