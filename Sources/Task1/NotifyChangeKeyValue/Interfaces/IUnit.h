#pragma once

#include "..\..\..\Common\Header.h"

namespace Seminar
{

	class IUnit
	{

		IUnit(void) = delete;
		IUnit(const IUnit&) = delete;
		IUnit(IUnit&&) = delete;
		IUnit& operator = (const IUnit&) = delete;
		IUnit& operator = (IUnit&&) = delete;

		std::wstring wsName{};

	protected:

		explicit IUnit(const std::wstring& wsName) noexcept : wsName(wsName) { }

	public:

		virtual ~IUnit(void) = default;

		std::wstring GetName(void) const noexcept
		{

			return this->wsName;

		}

		virtual IUnit& Add(const std::shared_ptr<IUnit>&) = 0;

		virtual DWORD GetType(void) const = 0;

		virtual const std::vector<BYTE>& GetData(void) const = 0;

		virtual const std::list<std::shared_ptr<IUnit>>& GetUnits(void) const = 0;

	};

}
