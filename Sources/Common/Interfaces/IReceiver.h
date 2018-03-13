#pragma once

#include "..\Header.h"

namespace Seminar
{

	class IReceiver
	{

		IReceiver(const IReceiver&) = delete;
		IReceiver(IReceiver&&) = delete;
		IReceiver& operator = (const IReceiver&) = delete;
		IReceiver& operator = (IReceiver&&) = delete;

	protected:

		IReceiver(void) = default;

	public:
		
		virtual ~IReceiver(void) = default;

		virtual void Action(void) const = 0;

		virtual void Action(const std::wstring&) const = 0;

	};

}