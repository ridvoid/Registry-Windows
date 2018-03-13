
#include "RegKeyBuilderUnit.h"

namespace Seminar
{

	RegKeyBuilderUnit::RegKeyBuilderUnit(const std::wstring& wsName) noexcept : wsName(wsName) { }

	std::unique_ptr<IBuilderUnit> RegKeyBuilderUnit::Create(const std::wstring& wsName)
	{

		return std::unique_ptr<IBuilderUnit>(new RegKeyBuilderUnit(wsName));

	}

	std::shared_ptr<IUnit> RegKeyBuilderUnit::Build(void)
	{

		return std::move(this->CreateNewUnit().SaveKeyValues().AddValuesToKey().ptrUnit);
		
	}

	RegKeyBuilderUnit& RegKeyBuilderUnit::CreateNewUnit(void)
	{

		IBuilderUnit::ptrUnit = RegKeyUnit::Create(this->wsName);

		return *this;

	}

	RegKeyBuilderUnit& RegKeyBuilderUnit::SaveKeyValues(void)
	{

		this->listValues = Registry::Open(this->wsName)->GetValues();

		return *this;

	}

	RegKeyBuilderUnit& RegKeyBuilderUnit::AddValuesToKey(void)
	{

		for (const auto& i : this->listValues)
			IBuilderUnit::ptrUnit->Add(RegValueUnit::Create(i.wsName,
				i.type,
				i.vecData));

		return *this;

	}

}
