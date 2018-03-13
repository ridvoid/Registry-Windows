#pragma once

#include "..\Interfaces\IRestoreRegValue.h"

namespace Seminar
{

	class RemoveRegValue : public IRestoreRegValue
	{

		RemoveRegValue(const RemoveRegValue&) = delete;
		RemoveRegValue(RemoveRegValue&&) = delete;
		RemoveRegValue& operator = (const RemoveRegValue&) = delete;
		RemoveRegValue& operator = (RemoveRegValue&&) = delete;

	public:

		using IRestoreRegValue::IRestoreRegValue;

		virtual ~RemoveRegValue(void) = default;

		void Execute(void) override;

	};

}