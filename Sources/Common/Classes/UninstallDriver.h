#pragma once

#include "..\Interfaces\ICommand.h"
#include "Driver.h"
#include "File.h"

namespace Seminar
{

	class UninstallDriver : public ICommand
	{

		UninstallDriver(void) = delete;
		UninstallDriver(const UninstallDriver&) = delete;
		UninstallDriver(UninstallDriver&&) = delete;
		UninstallDriver& operator = (const UninstallDriver&) = delete;
		UninstallDriver& operator = (UninstallDriver&&) = delete;

		std::wstring wsPath{}, wsName{};

		explicit UninstallDriver(const IReceiver*,
			const std::wstring&,
			const std::wstring&) noexcept;

	public:

		virtual ~UninstallDriver(void) = default;

		static std::unique_ptr<ICommand> Create(const IReceiver*,
			const std::wstring&,
			const std::wstring&);

		void Execute(void) override;

	};

}
