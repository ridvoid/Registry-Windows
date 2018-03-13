#pragma once

#include "..\Classes\CommandLineArgument.h"
#include "..\Classes\Convert.h"
#include "..\Interfaces\ICommand.h"

namespace Seminar
{

	class IApplication
	{

		IApplication(const IApplication&) = delete;
		IApplication(IApplication&&) = delete;
		IApplication& operator = (const IApplication&) = delete;
		IApplication& operator = (IApplication&&) = delete;

		HINSTANCE hInstance{};

	protected:

		std::vector<std::wstring> vecArguments{};

		std::list<std::unique_ptr<ICommand>> listCommands{};

		IApplication(void) = default;

	public:

		virtual ~IApplication(void) = default;

		virtual IApplication& SetInstance(HINSTANCE) noexcept;
	
		virtual HINSTANCE GetInstance(void) const noexcept;

		virtual int Execute(void);

		virtual void ShowHelp(void) const = 0;

	protected:

		virtual IApplication& SaveArguments(void);

		virtual IApplication& ToLowerArguments(void);

		virtual IApplication& CheckArguments(void);

		virtual std::unique_ptr<ICommand> CreateCommand(const std::wstring&) const = 0;

		virtual void ExecuteCommands(void) const;

	};

}