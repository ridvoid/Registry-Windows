#pragma once

#include "..\Interfaces\IEvent.h"

namespace Seminar
{

	class AutoEvent : public IEvent
	{

		AutoEvent(void) = delete;
		AutoEvent(const AutoEvent&) = delete;
		AutoEvent& operator = (const AutoEvent&) = delete;
		AutoEvent(AutoEvent&&) = delete;
		AutoEvent& operator = (AutoEvent&&) = delete;

	public:

		using IEvent::IEvent;
		
		virtual ~AutoEvent(void) = default;

		void Reset(void) const override;

		static std::unique_ptr<IEvent> Create(LPSECURITY_ATTRIBUTES = {},
			BOOL = {},
			const std::wstring& = {});

	};

}