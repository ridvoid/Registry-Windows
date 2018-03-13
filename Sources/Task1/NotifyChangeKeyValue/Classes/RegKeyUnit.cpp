#include "RegKeyUnit.h"


namespace Seminar
{

	RegKeyUnit::RegKeyUnit(const std::wstring& wsName) noexcept : IUnit(wsName) { }

	IUnit& RegKeyUnit::Add(const std::shared_ptr<IUnit>& uptrUnit)
	{

		this->list.emplace_back(std::move(uptrUnit));

		return *this;

	}

	DWORD RegKeyUnit::GetType(void) const
	{

		throw NotSupportedException(L"Not suppoted RegKeyUnit::GetType");

	}

	const std::vector<BYTE>& RegKeyUnit::GetData(void) const
	{

		throw NotSupportedException(L"Not suppoted RegKeyUnit::GetData");

	}

	const std::list<std::shared_ptr<IUnit>>& RegKeyUnit::GetUnits(void) const
	{

		return this->list;

	}

	std::shared_ptr<IUnit> RegKeyUnit::Create(const std::wstring& wsName)
	{

		return std::shared_ptr<IUnit>(new RegKeyUnit(wsName));

	}

}