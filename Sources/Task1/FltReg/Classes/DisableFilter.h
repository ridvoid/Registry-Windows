#pragma once

#include "..\..\..\Common\Interfaces\ICommand.h"
#include "..\..\..\Common\Classes\Driver.h"

namespace Seminar
{

	class DisableFilter : public ICommand
	{

		DisableFilter(void) = delete;
		DisableFilter(const DisableFilter&) = delete;
		DisableFilter(DisableFilter&&) = delete;
		DisableFilter& operator = (const DisableFilter&) = delete;
		DisableFilter& operator = (DisableFilter&&) = delete;

		std::wstring wsName{};

		explicit DisableFilter(const IReceiver*,
			const std::wstring&) noexcept;

	public:

		virtual ~DisableFilter(void) = default;

		static std::unique_ptr<ICommand> Create(const IReceiver*,
			const std::wstring&);

		void Execute(void) override;

	};

}
