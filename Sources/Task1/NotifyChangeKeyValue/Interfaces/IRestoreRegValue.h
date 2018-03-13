#pragma once

#include "..\..\..\Common\Header.h"
#include "..\Interfaces\IUnit.h"
#include "..\..\..\Common\Classes\Registry.h"
#include "..\..\..\Common\Interfaces\ICommand.h"

namespace Seminar
{

	class IRestoreRegValue : public ICommand
	{

		IRestoreRegValue(void) = delete;
		IRestoreRegValue(const IRestoreRegValue&) = delete;
		IRestoreRegValue(IRestoreRegValue&&) = delete;
		IRestoreRegValue& operator = (const IRestoreRegValue&) = delete;
		IRestoreRegValue& operator = (IRestoreRegValue&&) = delete;

	protected:

		std::wstring wsName{};

		using RegValue = std::shared_ptr<IUnit>;
		RegValue regValue{};

	public:

		explicit IRestoreRegValue(const IReceiver*,
			const std::wstring&,
			const RegValue&) noexcept;

		virtual ~IRestoreRegValue(void) = default;

		template<typename T>
		static std::unique_ptr<ICommand> Create(const IReceiver* pReceiver,
			const std::wstring& wsName,
			const RegValue& regValue)
		{

			return std::unique_ptr<IRestoreRegValue>(new T(pReceiver,
				wsName,
				regValue));

		}

	protected:

		void Show(const std::wstring&) const;

	};

}
