#pragma once

#include "..\Interfaces\IUnit.h"
#include "..\..\..\Common\Classes\Exceptions.h"

namespace Seminar
{

	class RegValueUnit : public IUnit
	{
		
		RegValueUnit(void) = delete;
		RegValueUnit(const RegValueUnit&) = delete;
		RegValueUnit(RegValueUnit&&) = delete;
		RegValueUnit& operator = (const RegValueUnit&) = delete;
		RegValueUnit& operator = (RegValueUnit&&) = delete;

		DWORD dwType{};

		std::vector<BYTE> vecData{};

		explicit RegValueUnit(const std::wstring&,
			DWORD,
			const std::vector<BYTE>&);

	public:

		virtual ~RegValueUnit(void) = default;

		IUnit& Add(const std::shared_ptr<IUnit>&) override;

		DWORD GetType(void) const override;

		const std::vector<BYTE>& GetData(void) const override;

		const std::list<std::shared_ptr<IUnit>>& GetUnits(void) const override;

		static std::shared_ptr<IUnit> Create(const std::wstring&,
			DWORD,
			const std::vector<BYTE>&);

	};

}