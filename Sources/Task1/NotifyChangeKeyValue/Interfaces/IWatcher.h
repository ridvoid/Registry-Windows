#pragma once

#include "..\..\..\Common\Header.h"
#include "..\Interfaces\IObserver.h"

namespace Seminar
{

	class IWatcher : public Subject
	{

		IWatcher(const IWatcher&) = delete;
		IWatcher(IWatcher&&) = delete;
		IWatcher& operator = (const IWatcher&) = delete;
		IWatcher& operator = (IWatcher&&) = delete;

	protected:

		IWatcher(void) = default;

	public:

		virtual ~IWatcher(void) = default;

		virtual IWatcher& Watch(void) = 0;

	};

}
