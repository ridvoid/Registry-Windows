#pragma once

#include "IUnit.h"

namespace Seminar
{

	class IBuilderUnit
	{

		IBuilderUnit(const IBuilderUnit&) = delete;
		IBuilderUnit& operator = (const IBuilderUnit&) = delete;
		IBuilderUnit(IBuilderUnit&&) = delete;
		IBuilderUnit& operator = (IBuilderUnit&&) = delete;

	protected:

		IBuilderUnit(void) = default;
		
		std::shared_ptr<IUnit> ptrUnit{};

	public:

		virtual ~IBuilderUnit(void) = default;

		virtual std::shared_ptr<IUnit> Build(void) = 0;

	};

}