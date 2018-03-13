#pragma once

#include "Wrap.h"

namespace Seminar
{

	class Driver
	{

		Driver(void) = delete;
		Driver(const Driver&) = delete;
		Driver(Driver&&) = delete;
		Driver& operator = (const Driver&) = delete;
		Driver& operator = (Driver&&) = delete;
		~Driver(void) = delete;

		using Handle = std::unique_ptr<Wrap::Service::Handle>;

	public:

		static void Install(const std::wstring&,
			const std::wstring&);

		static void Load(const std::wstring&);

		static void Unload(const std::wstring&);

		static void Uninstall(const std::wstring&);

	private:

		static Handle OpenManager(DWORD = SC_MANAGER_ALL_ACCESS);

		static Handle OpenService(const Handle&,
			const std::wstring&,
			DWORD = SERVICE_ALL_ACCESS);

	};

}
