#pragma once

#include "AutoEvent.h"

namespace Seminar
{

	void AutoEvent::Reset(void) const
	{

		throw NotSupportedException(L"Reset",
			ERROR_INVALID_PARAMETER);

	}

	std::unique_ptr<IEvent> AutoEvent::Create(LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		BOOL bInitialState,
		const std::wstring& wsName)
	{

		return IEvent::Create<AutoEvent>(lpSecurityAttributes,
			FALSE,
			bInitialState,
			wsName);

	}

}