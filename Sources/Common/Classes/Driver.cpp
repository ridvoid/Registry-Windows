
#include "Driver.h"

namespace Seminar
{

	void Driver::Install(const std::wstring& wsDrivePath,
		const std::wstring& wsDeviceName)
	{

		auto h = Wrap::Service::Handle::Create(CreateService(*Driver::OpenManager(),
			wsDeviceName.c_str(),
			wsDeviceName.c_str(),
			SERVICE_ALL_ACCESS,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			wsDrivePath.c_str(),
			{},
			{},
			{},
			{},
			{}));
		if (!*h)
		{

			auto dwErrCode = GetLastError();
			if (dwErrCode != ERROR_SERVICE_EXISTS)
				throw DriverException(L"Error CreateService",
					dwErrCode);

		}

	}

	void Driver::Load(const std::wstring& wsDeviceName)
	{

		auto h = Driver::OpenService(Driver::OpenManager(),
			wsDeviceName,
			SERVICE_START);

		if (!StartService(*h,
			{},
			{}))
		{

			auto err = GetLastError();
			if (err != ERROR_SERVICE_ALREADY_RUNNING)
				throw DriverException(L"Error StartService",
					err);

		}

	}

	void Driver::Unload(const std::wstring& wsDeviceName)
	{

		auto h = Driver::OpenService(Driver::OpenManager(),
			wsDeviceName,
			SERVICE_STOP);

		SERVICE_STATUS ss{};
		if (!ControlService(*h,
			SERVICE_CONTROL_STOP,
			&ss))
			throw DriverException(L"Error ControlService",
				GetLastError());

	}

	void Driver::Uninstall(const std::wstring& wsDeviceName)
	{

		auto h = Driver::OpenService(Driver::OpenManager(),
			wsDeviceName,
			SERVICE_ALL_ACCESS);

		if (!DeleteService(*h))
			throw DriverException(L"Error DeleteService",
				GetLastError());

	}

	Driver::Handle Driver::OpenManager(DWORD dwAccess)
	{

		auto h = Wrap::Service::Handle::Create(OpenSCManager({},
			{},
			dwAccess));
		if (!*h)
			throw DriverException(L"Error OpenSCManager",
				GetLastError());

		return h;

	}

	Driver::Handle Driver::OpenService(const Driver::Handle& uPtrMng,
		const std::wstring& wsName,
		DWORD dwAccess)
	{

		auto h = Wrap::Service::Handle::Create(::OpenService(*uPtrMng,
			wsName.c_str(),
			dwAccess));
		if (!*h)
			throw DriverException(L"Error OpenService",
				GetLastError());

		return h;

	}

}

