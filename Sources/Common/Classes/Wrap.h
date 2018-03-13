//---------------------------------------------------------------------------

#pragma once

#include "Exceptions.h"

//---------------------------------------------------------------------------

namespace Seminar
{

	namespace Wrap
	{

		namespace Common
		{

			class Handle
			{

				Handle(void) = delete;
				Handle(const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle& operator = (const Handle&) = delete;
				Handle& operator = (Handle&&) = delete;

			protected:

				HANDLE h{};

				explicit Handle(HANDLE) noexcept;

			public:
				
				virtual ~Handle(void) noexcept;

				template<typename T>
				static std::unique_ptr<Handle> Create(HANDLE h)
				{

					return std::unique_ptr<Handle>(new T(h));

				}

				operator HANDLE (void) const noexcept;

				bool operator ! (void) const noexcept;

				DWORD Wait(DWORD = INFINITE) const;

				static DWORD Wait(const std::vector<HANDLE>&,
					BOOL = TRUE,
					DWORD = INFINITE);

			};

		}

		namespace Reg
		{

			class Handle
			{

				Handle(void) = delete;
				Handle(const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle& operator = (const Handle&) = delete;
				Handle& operator = (Handle&&) = delete;

				HKEY h{};

				explicit Handle(HKEY) noexcept;

			public:
				
				~Handle(void) noexcept;

				static std::unique_ptr<Handle> Create(HKEY);

				operator HKEY (void) const noexcept;

				operator PHKEY (void) noexcept;

				bool operator != (LONG) const noexcept;

			};

		}
		
		namespace Service
		{

			class Handle
			{

				Handle(void) = delete;
				Handle(const Handle&) = delete;
				Handle & operator = (const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle & operator = (Handle&&) = delete;

				SC_HANDLE h{};

				explicit Handle(SC_HANDLE) noexcept;

			public:

				~Handle(void) noexcept;

				static std::unique_ptr<Handle> Create(SC_HANDLE);

				operator SC_HANDLE(void) const noexcept;

				bool operator ! (void) const noexcept;

			};

		}

	}

}

