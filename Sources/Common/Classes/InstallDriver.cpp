#pragma once

#include "InstallDriver.h"

namespace Seminar
{

	InstallDriver::InstallDriver(const IReceiver* IReceiver,
		const std::wstring& wsPath,
		const std::wstring& wsName,
		DWORD dwRes) noexcept 
		: 
		ICommand(IReceiver), 
		wsPath(wsPath), 
		wsName(wsName), 
		dwRes(dwRes) 
		{ }

	std::unique_ptr<ICommand> InstallDriver::Create(const IReceiver* IReceiver, 
		const std::wstring& wsPath,
		const std::wstring& wsName,
		DWORD dwRes)
	{

		return std::unique_ptr<ICommand>(new InstallDriver(IReceiver,
			wsPath,
			wsName,
			dwRes));

	}
	
	void InstallDriver::Execute(void)
	{

		this->SaveDriverFromResourceToFile().Install();

		std::wostringstream wos;

		wos << this->wsName << L" -> installed" << std::endl;
		
		ICommand::OnAction(wos.str());

	}

	const InstallDriver& InstallDriver::SaveDriverFromResourceToFile(void) const
	{

		Res::SaveResourceByNameToFile(this->wsPath,
			MAKEINTRESOURCE(this->dwRes),
			RT_RCDATA);

		return *this;

	}

	void InstallDriver::Install(void) const
	{

		Driver::Install(this->wsPath,
			this->wsName);

	}

}
