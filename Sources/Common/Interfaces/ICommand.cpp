#pragma once

#include "ICommand.h"

namespace Seminar
{

	ICommand::ICommand(const IReceiver* pIReceiver) : pIReceiver(pIReceiver) { }

	void ICommand::OnAction(void) const
	{

		if (this->pIReceiver)
			this->pIReceiver->Action();

	}

	void ICommand::OnAction(const std::wstring& ws) const
	{

		if (this->pIReceiver)
			this->pIReceiver->Action(ws);

	}

}