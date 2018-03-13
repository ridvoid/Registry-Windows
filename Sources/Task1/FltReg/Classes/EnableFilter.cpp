#pragma once

#include "EnableFilter.h"

namespace Seminar
{

	EnableFilter::EnableFilter(const IReceiver* pReceiver,
		const std::wstring& wsName) noexcept 
		: 
		ICommand(pReceiver), 
		wsName(wsName) 
		{ }

	std::unique_ptr<ICommand> EnableFilter::Create(const IReceiver* pReceiver,
		const std::wstring& wsName)
	{

		return std::unique_ptr<ICommand>(new EnableFilter(pReceiver,
			wsName));

	}
	
	void EnableFilter::Execute(void)
	{

		Driver::Load(this->wsName);

		std::wostringstream wos;

		wos << this->wsName << L" -> enabled" << std::endl;

		ICommand::OnAction(wos.str());

	}

}
