#include "RegValueUnit.h"

namespace Seminar
{

	RegValueUnit::RegValueUnit(const std::wstring& wsName,
		DWORD dwType,
		const std::vector<BYTE>& vecData) : 
		IUnit(wsName), 
		dwType(dwType), 
		vecData(vecData){ }

	IUnit& RegValueUnit::Add(const std::shared_ptr<IUnit>&)
	{

		throw NotSupportedException(L"Not suppoted RegValueUnit::Add");

	}

	DWORD RegValueUnit::GetType(void) const
	{

		return this->dwType;

	}

	const std::vector<BYTE>& RegValueUnit::GetData(void) const
	{

		return this->vecData;

	}

	const std::list<std::shared_ptr<IUnit>>& RegValueUnit::GetUnits(void) const
	{

		throw NotSupportedException(L"Not suppoted RegValueUnit::GetUnits");

	}

	std::shared_ptr<IUnit> RegValueUnit::Create(const std::wstring& wsName,
		DWORD dwType,
		const std::vector<BYTE>& vecData)
	{

		return std::shared_ptr<IUnit>(new RegValueUnit(wsName,
			dwType,
			vecData));

	}

}
