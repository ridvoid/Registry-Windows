#include "Wrap.h"

namespace Seminar
{

	namespace Wrap
	{

		namespace Common
		{

			Handle::Handle(HANDLE h) noexcept : h(h) { }

			Handle::~Handle(void) noexcept
			{

				if (this->h && this->h != INVALID_HANDLE_VALUE)
					CloseHandle(this->h);

			}

			Handle::operator HANDLE(void) const noexcept
			{

				return this->h;

			}

			bool Handle::operator !(void) const noexcept
			{

				return !this->h || this->h == INVALID_HANDLE_VALUE;

			}

			DWORD Handle::Wait(DWORD dwPeriod) const
			{

				auto dwReturn = WaitForSingleObject(h,
					dwPeriod);
				if (dwReturn == WAIT_FAILED)
					throw HandleException(L"Error WaitForSingleObject",
						GetLastError());

				return dwReturn;

			}

			DWORD Handle::Wait(const std::vector<HANDLE>& vecHandles,
				BOOL bWaitAll,
				DWORD dwPeriod)
			{

				auto dwReturn = WaitForMultipleObjects(static_cast<DWORD>(vecHandles.size()),
					vecHandles.data(),
					bWaitAll,
					dwPeriod);
				if (dwReturn == WAIT_FAILED)
					throw HandleException(L"Error WaitForMultipleObjects",
						GetLastError());

				return dwReturn;

			}

		}

		namespace Reg
		{

			Handle::Handle(HKEY h) noexcept : h(h) { }

			Handle::~Handle(void) noexcept
			{

				if (this->h)
					RegCloseKey(this->h);

			}

			std::unique_ptr<Handle> Handle::Create(HKEY h)
			{

				return std::unique_ptr<Handle>(new Handle(h));

			}

			Handle::operator HKEY (void) const noexcept
			{

				return this->h;

			}

			Handle::operator PHKEY (void) noexcept
			{

				return &this->h;

			}

			bool Handle::operator != (LONG lValue) const noexcept
			{

				return ERROR_SUCCESS != lValue;

			}

		}

		namespace Service
		{

			Handle::Handle(SC_HANDLE h) noexcept : h(h) { }

			Handle::~Handle(void) noexcept
			{

				if (this->h)
					CloseServiceHandle(this->h);

			}

			std::unique_ptr<Handle> Handle::Create(SC_HANDLE h)
			{

				return std::unique_ptr<Handle>(new Handle(h));

			}

			Handle::operator SC_HANDLE(void) const noexcept
			{

				return this->h;

			}

			bool Handle::operator ! (void) const noexcept
			{

				return !this->h;

			}

		}

	}

}


