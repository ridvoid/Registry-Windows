#pragma once

#include "..\..\Common\Header.h"

namespace Seminar
{

	class IScanner
	{

		IScanner(const IScanner&) = delete;
		IScanner(IScanner&&) = delete;
		IScanner& operator = (const IScanner&) = delete;
		IScanner& operator = (IScanner&&) = delete;

	public:

		IScanner(void) = default;
		
		virtual ~IScanner(void) = default;

		virtual std::vector<BYTE> Scan(const std::vector<BYTE>&) = 0;

	};

}
