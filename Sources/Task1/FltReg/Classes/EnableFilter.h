#pragma once

#include "..\..\..\Common\Interfaces\ICommand.h"
#include "..\..\..\Common\Classes\Driver.h"

namespace Seminar
{

	class EnableFilter : public ICommand
	{

		EnableFilter(void) = delete;
		EnableFilter(const EnableFilter&) = delete;
		EnableFilter(EnableFilter&&) = delete;
		EnableFilter& operator = (const EnableFilter&) = delete;
		EnableFilter& operator = (EnableFilter&&) = delete;

		std::wstring wsName{};

		explicit EnableFilter(const IReceiver*,
			const std::wstring&) noexcept;

	public:

		virtual ~EnableFilter(void) = default;

		static std::unique_ptr<ICommand> Create(const IReceiver*,
			const std::wstring&);

		void Execute(void) override;

	};

}
