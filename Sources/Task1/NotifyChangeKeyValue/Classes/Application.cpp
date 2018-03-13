
#include "Application.h"

namespace Seminar
{

	const Application::NameKeys Application::nameKeys =
	{  
	
		L"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
	
	};

	Application::GuardKeys Application::guardKeys;

	IApplication& Application::GetInstance(void)
	{

		static Application instance;

		return instance;

	}

	int Application::Execute(void)
	{

		for (const auto& i : Application::nameKeys)
		{

			auto ptr = this->CreateCommand(i);

			ptr->Execute();

			Application::guardKeys.emplace_back(std::move(ptr));

		}

		this->ShowHelp();

		return {};

	}

	void Application::ShowHelp(void) const
	{

		std::wcout << L"To exit press enter..." << std::endl << std::endl;

		std::wcin.get();

	}

	std::unique_ptr<ICommand> Application::CreateCommand(const std::wstring& wsCommand) const
	{

		return Seminar::GuardRegKey::Create(wsCommand);

	}

}
