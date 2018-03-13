#pragma once

#include "DisableFilter.h"

namespace Seminar
{

	DisableFilter::DisableFilter(const IReceiver* pReceiver,
		const std::wstring& wsName) noexcept 
		: 
		ICommand(pReceiver),
		wsName(wsName) 
		{ }

	std::unique_ptr<ICommand> DisableFilter::Create(const IReceiver* pReceiver,
		const std::wstring& wsName)
	{

		return std::unique_ptr<ICommand>(new DisableFilter(pReceiver,
			wsName));

	}
	
	void DisableFilter::Execute(void)
	{

		Driver::Unload(this->wsName);

		std::wostringstream wos;

		wos << this->wsName << L" -> disabled" << std::endl;

		ICommand::OnAction(wos.str());

	}

}
