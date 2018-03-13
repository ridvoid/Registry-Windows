
#include "CommandLineArgument.h"

namespace Seminar
{

	std::vector<std::wstring> CommandLineArgument::GetCommandLines(void)
	{

		auto nArgs{0};

		auto pszArglist = CommandLineToArgvW(GetCommandLine(),
			&nArgs);
		if (!pszArglist)
			throw CommandLineArgumentException(L"Error CommandLineToArgvW",
				GetLastError());
	
		std::vector<std::wstring> vecReturn;
		for (auto i{0}; i < nArgs; i++)
			vecReturn.emplace_back(pszArglist[i]);

		LocalFree(pszArglist);

		return vecReturn;

	}
}
