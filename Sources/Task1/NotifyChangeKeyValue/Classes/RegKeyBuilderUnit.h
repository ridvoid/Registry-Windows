#pragma once

#include "..\Interfaces\IBuilderUnit.h"
#include "..\Classes\RegKeyUnit.h"
#include "..\Classes\RegValueUnit.h"
#include "..\..\..\Common\Classes\Registry.h"

namespace Seminar
{

	class RegKeyBuilderUnit : public IBuilderUnit
	{

		RegKeyBuilderUnit(void) = delete;
		RegKeyBuilderUnit(const RegKeyBuilderUnit&) = delete;
		RegKeyBuilderUnit& operator = (const RegKeyBuilderUnit&) = delete;
		RegKeyBuilderUnit(RegKeyBuilderUnit&&) = delete;
		RegKeyBuilderUnit& operator = (RegKeyBuilderUnit&&) = delete;

		std::wstring wsName{};

		using KeyValue = Registry::KeyValue;
		std::list<KeyValue> listValues{};

		explicit RegKeyBuilderUnit(const std::wstring&) noexcept;

	public:

		virtual ~RegKeyBuilderUnit(void) = default;

		static std::unique_ptr<IBuilderUnit> Create(const std::wstring&);

		std::shared_ptr<IUnit> Build(void) override;

	private:

		RegKeyBuilderUnit& CreateNewUnit(void);

		RegKeyBuilderUnit& SaveKeyValues(void);

		RegKeyBuilderUnit& AddValuesToKey(void);

	};

}