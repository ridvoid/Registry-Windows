#pragma once

#include "IReceiver.h"

namespace Seminar
{

	class ICommand
	{

		ICommand(const ICommand&) = delete;
		ICommand(ICommand&&) = delete;
		ICommand& operator = (const ICommand&) = delete;
		ICommand& operator = (ICommand&&) = delete;

	protected:

		const IReceiver* pIReceiver{};

		ICommand(const IReceiver* = {});

	public:
		
		virtual ~ICommand(void) = default;

		virtual void Execute(void) = 0;

	protected:

		virtual void OnAction(void) const;

		virtual void OnAction(const std::wstring&) const;

	};

}