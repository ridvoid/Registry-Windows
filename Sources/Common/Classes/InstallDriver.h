#pragma once

#include "..\Interfaces\ICommand.h"
#include "Res.h"
#include "Convert.h"
#include "Driver.h"

namespace Seminar
{

	class InstallDriver : public ICommand
	{

		InstallDriver(void) = delete;
		InstallDriver(const InstallDriver&) = delete;
		InstallDriver(InstallDriver&&) = delete;
		InstallDriver& operator = (const InstallDriver&) = delete;
		InstallDriver& operator = (InstallDriver&&) = delete;

		std::wstring wsPath{}, wsName{};

		DWORD dwRes{};

		explicit InstallDriver(const IReceiver*,
			const std::wstring&,
			const std::wstring&,
			DWORD) noexcept;

	public:

		virtual ~InstallDriver(void) = default;

		static std::unique_ptr<ICommand> Create(const IReceiver*,
			const std::wstring&,
			const std::wstring&,
			DWORD);

		void Execute(void) override;
		
	private:

		const InstallDriver& SaveDriverFromResourceToFile(void) const;

		void Install(void) const;

	};

}
