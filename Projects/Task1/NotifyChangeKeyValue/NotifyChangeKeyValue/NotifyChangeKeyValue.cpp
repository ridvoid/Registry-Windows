// NotifyChangeKeyValue.cpp : Defines the entry point for the console application.
//

#include "..\..\..\..\Sources\Task1\NotifyChangeKeyValue\Classes\Application.h"

int main()
{

	_wsetlocale(LC_ALL,
		L".866");

	auto iReturn = -1;

	try
	{

		iReturn = Seminar::Application::GetInstance().Execute();

	}
	catch (const Seminar::WinApiException& ex)
	{

		std::wcout << ex.What();

		if (ex.GetErrCode())
			iReturn = static_cast<int>(ex.GetErrCode());

	}
	catch (const std::exception& ex)
	{

		std::cout << ex.what() << std::endl;

	}
	catch (...)
	{
		
		std::wcout << L"Unhandled exception" << std::endl;

	}

	return iReturn;

}

