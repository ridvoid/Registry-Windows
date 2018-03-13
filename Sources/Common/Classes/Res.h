#pragma once

#include "Exceptions.h"
#include "Convert.h"

namespace Seminar
{

	class Res
	{

		Res(void) = delete;
		Res(const Res&) = delete;
		Res(Res&&) = delete;
		Res& operator = (const Res&) = delete;
		Res& operator = (Res&&) = delete;
		~Res(void) = delete;

	public:

		static void SaveResourceByNameToFile(const std::wstring&,
			LPCWSTR,
			LPCWSTR);

	private:

		static std::vector<BYTE> GetResourceByName(HMODULE,
			LPCWSTR,
			LPCWSTR);

	};

}
