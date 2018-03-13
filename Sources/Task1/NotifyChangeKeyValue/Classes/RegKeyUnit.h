#pragma once

#include "..\Interfaces\IUnit.h"
#include "..\..\..\Common\Classes\Exceptions.h"

namespace Seminar
{

	class RegKeyUnit : public IUnit
	{
		
		RegKeyUnit(void) = delete;
		RegKeyUnit(const RegKeyUnit&) = delete;
		RegKeyUnit(RegKeyUnit&&) = delete;
		RegKeyUnit& operator = (const RegKeyUnit&) = delete;
		RegKeyUnit& operator = (RegKeyUnit&&) = delete;

		using Unit = std::shared_ptr<IUnit>;

		std::list<Unit> list{};

		explicit RegKeyUnit(const std::wstring&) noexcept;

	public:

		virtual ~RegKeyUnit(void) = default;

		IUnit& Add(const std::shared_ptr<IUnit>&) override;

		DWORD GetType(void) const override;

		const std::vector<BYTE>& GetData(void) const override;

		const std::list<std::shared_ptr<IUnit>>& GetUnits(void) const override;

		static std::shared_ptr<IUnit> Create(const std::wstring&);

	};

}
