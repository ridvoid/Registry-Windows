#include "..\..\..\..\Sources\Task2\Classes\Application.h"

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE,
	LPWSTR,
	int)
{

	auto iReturn{ -1 };

	try
	{

		iReturn = Seminar::Application::GetInstance().SetInstance(hInstance).Execute();

	}
	catch (const Seminar::WinApiException& ex)
	{

		if (ex.GetErrCode())
			iReturn = static_cast<int>(ex.GetErrCode());

		MessageBox({},
			ex.What().c_str(),
			L"ScanReg",
			{});

	}
	catch (const std::exception& ex)
	{

		MessageBoxA({},
			ex.what(),
			"ScanReg",
			{});

	}
	catch (...)
	{

		MessageBox({},
			L"Unhandled exception...",
			L"ScanReg",
			{});

	}

	return iReturn;

}