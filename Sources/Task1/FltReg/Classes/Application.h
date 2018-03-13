#pragma once

#include "..\..\..\Common\Interfaces\IApplication.h"
#include "..\..\..\Common\Interfaces\IReceiver.h"
#include "..\..\..\Common\Classes\CommandLineArgument.h"
#include "..\..\..\Common\Classes\Convert.h"
#include "..\..\..\Common\Classes\InstallDriver.h"
#include "..\..\FltReg\Classes\EnableFilter.h"
#include "..\..\FltReg\Classes\DisableFilter.h"
#include "..\..\..\Common\Classes\UninstallDriver.h"
#include "..\..\..\..\Projects\Task1\FltReg\User\FltReg\resource.h"

namespace Seminar
{

	class Application : public IApplication, IReceiver
	{

		Application(void) = default;
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		static const std::wstring wsDriverPath, wsDriverName;
		
		static const std::wstring wsInstall, wsEnable, wsDisable, wsUninstall;

	public:

		virtual ~Application(void) = default;

		static Application& GetInstance(void);

		int Execute(void) override;

		void ShowHelp(void) const override;

	private:

		IApplication& CheckArguments(void) override;

		std::unique_ptr<ICommand> CreateCommand(const std::wstring&) const override;

		void Action(void) const override;

		void Action(const std::wstring&) const override;

	};

}
