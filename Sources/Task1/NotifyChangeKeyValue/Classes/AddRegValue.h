#pragma once

#include "..\Interfaces\IRestoreRegValue.h"

namespace Seminar
{

	class AddRegValue : public IRestoreRegValue
	{

		AddRegValue(const AddRegValue&) = delete;
		AddRegValue(AddRegValue&&) = delete;
		AddRegValue& operator = (const AddRegValue&) = delete;
		AddRegValue& operator = (AddRegValue&&) = delete;

	public:

		using IRestoreRegValue::IRestoreRegValue;

		virtual ~AddRegValue(void) = default;

		void Execute(void) override;

	};

}