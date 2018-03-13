#pragma once

#include "..\..\..\Common\Interfaces\IApplication.h"
#include "..\..\NotifyChangeKeyValue\Classes\GuardRegKey.h"

namespace Seminar
{

	class Application : public IApplication
	{

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		using NameKeys = std::vector<std::wstring>;
		static const NameKeys nameKeys;
		
		using GuardKeys = std::list<std::unique_ptr<ICommand>>;
		static GuardKeys guardKeys;

	public:

		Application(void) = default;

		virtual ~Application(void) = default;

		static IApplication& GetInstance(void);

		int Execute(void) override;

		void ShowHelp(void) const override;


	private:

		std::unique_ptr<ICommand> CreateCommand(const std::wstring&) const override;

	};

}