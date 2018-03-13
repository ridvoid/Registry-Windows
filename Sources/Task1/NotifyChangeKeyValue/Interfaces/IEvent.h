#pragma once

#include "..\..\..\Common\Classes\Wrap.h"

namespace Seminar
{

	class IEvent
	{

		IEvent(void) = delete;
		IEvent(const IEvent&) = delete;
		IEvent& operator = (const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
		IEvent& operator = (IEvent&&) = delete;

	protected:

		using Handle = std::unique_ptr<Wrap::Common::Handle>;

		Handle h{};
		
	public:

		explicit IEvent(Handle) noexcept;

		virtual ~IEvent(void) = default;

		void Set(void) const;

		virtual void Reset(void) const = 0;

		DWORD Wait(DWORD dwWait = INFINITE) const;

		operator HANDLE (void) const noexcept;

	protected:

		template<typename T>
		static std::unique_ptr<IEvent> Create(LPSECURITY_ATTRIBUTES lpSecAttr,
			BOOL bManualReset,
			BOOL bInitialState,
			const std::wstring& wsName)
		{

			auto h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateEvent(lpSecAttr,
				bManualReset,
				bInitialState,
				wsName.c_str()));
			if (!*h)
				throw IEventException(L"Error CreateEvent",
					GetLastError());

			return std::unique_ptr<IEvent>(new T(std::move(h)));
				
		}

	};

}