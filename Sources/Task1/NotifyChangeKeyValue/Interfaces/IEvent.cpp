#pragma once

#include "IEvent.h"

namespace Seminar
{

	IEvent::IEvent(Handle h) noexcept : h(std::move(h)) { }

	void IEvent::Set(void) const
	{

		if (!SetEvent(*this->h))
			throw IEventException(L"Error SetEvent",
				GetLastError());

	}

	DWORD IEvent::Wait(DWORD dwWait) const
	{

		return this->h->Wait(dwWait);

	}

	IEvent::operator HANDLE (void) const noexcept
	{

		return *this->h;

	}

}