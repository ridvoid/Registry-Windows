
#include "Application.h"

namespace Seminar
{

	const std::wstring Application::wsDriverPath(L"%SystemRoot%\\System32\\Drivers\\FltReg.sys"), 
		Application::wsDriverName(L"FltReg");

	const std::wstring Application::wsInstall(L"install"), 
		Application::wsEnable(L"enable"), 
		Application::wsDisable(L"disable"), 
		Application::wsUninstall(L"uninstall");
	
	Application& Application::GetInstance(void)
	{

		static Application instance;

		return instance;

	}

	int Application::Execute(void)
	{

		std::wcout << std::endl;

		IApplication::Execute();

		this->CheckArguments();

		IApplication::ExecuteCommands();

		return{};

	}

	void Application::ShowHelp(void) const
	{

		std::wcout << L"Description commands:" << std::endl;

		std::wcout << L"install - install driver to system" << std::endl;

		std::wcout << L"enable - enable registry filter" << std::endl;

		std::wcout << L"disable - disable registry filter" << std::endl;

		std::wcout << L"uninstall - uninstall driver from system" << std::endl << std::endl;

		std::wcout << L"Example: FltReg.exe install enable" << std::endl << std::endl;

	}

	IApplication& Application::CheckArguments(void)
	{

		IApplication::CheckArguments();

		for (const auto& i : IApplication::vecArguments)
			this->listCommands.emplace_back(this->CreateCommand(i));

		return *this;

	}

	std::unique_ptr<ICommand> Application::CreateCommand(const std::wstring& wsName) const
	{

		if (wsName == Application::wsInstall)
		{

			DWORD dwResId{};

#ifndef _WIN64
			dwResId = IDR_RCDATA1;
#else
			dwResId = IDR_RCDATA2;
#endif

			return InstallDriver::Create(this,
				Convert::EnvironmentPathToAbsolutePath(Application::wsDriverPath),
				Application::wsDriverName,
				dwResId);

		}

		if (wsName == Application::wsEnable)
			return EnableFilter::Create(this,
				Application::wsDriverName);

		if (wsName == Application::wsDisable)
			return DisableFilter::Create(this,
				Application::wsDriverName);

		if (wsName == Application::wsUninstall)
			return UninstallDriver::Create(this,
				Convert::EnvironmentPathToAbsolutePath(Application::wsDriverPath),
				Application::wsDriverName);

		throw CommandLineArgumentException(L"Invalid command line arguments");

	}

	void Application::Action(void) const
	{

		throw NotSupportedException(L"Action",
			ERROR_NOT_SUPPORTED);

	}

	void Application::Action(const std::wstring& ws) const
	{

		std::wcout << ws << std::endl;

	}

}
