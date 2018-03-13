#pragma once

#include "..\Interfaces\IRestoreRegValue.h"


namespace Seminar
{

	class ChangeRegValue : public IRestoreRegValue
	{

		ChangeRegValue(const ChangeRegValue&) = delete;
		ChangeRegValue(ChangeRegValue&&) = delete;
		ChangeRegValue& operator = (const ChangeRegValue&) = delete;
		ChangeRegValue& operator = (ChangeRegValue&&) = delete;

	public:

		using IRestoreRegValue::IRestoreRegValue;

		virtual ~ChangeRegValue(void) = default;

		void Execute(void) override;

	};

}