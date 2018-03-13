// FltReg.cpp : Defines the entry point for the console application.
//


#include "..\..\..\..\..\Sources\Task1\FltReg\Classes\Application.h"

int main()
{

	auto iReturn = -1;

	try
	{

		iReturn = Seminar::Application::GetInstance().Execute();

	}
	catch (const Seminar::CommandLineArgumentException& ex)
	{

		std::wcout << ex.What() << std::endl << std::endl;

		Seminar::Application::GetInstance().ShowHelp();

	}
	catch (const Seminar::WinApiException& ex)
	{

		std::wcout << ex.What() << std::endl;

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
