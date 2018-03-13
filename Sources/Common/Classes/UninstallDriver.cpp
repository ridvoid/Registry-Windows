#pragma once

#include "UninstallDriver.h"

namespace Seminar
{

	UninstallDriver::UninstallDriver(const IReceiver* pReciever,
		const std::wstring& wsPath,
		const std::wstring& wsName) noexcept 
		: 
		ICommand(pReciever),
		wsPath(wsPath), 
		wsName(wsName) 
		{ }

	std::unique_ptr<ICommand> UninstallDriver::Create(const IReceiver* pReciever,
		const std::wstring& wsPath,
		const std::wstring& wsName)
	{

		return std::unique_ptr<ICommand>(new UninstallDriver(pReciever,
			wsPath,
			wsName));

	}
	
	void UninstallDriver::Execute(void)
	{

		Driver::Uninstall(this->wsName);

		std::wostringstream wos;

		wos << this->wsName << L" -> deleted" << std::endl;

		ICommand::OnAction(wos.str());

		File::Delete(this->wsPath);

	}

}
