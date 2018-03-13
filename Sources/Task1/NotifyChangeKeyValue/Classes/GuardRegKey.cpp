
#include "GuardRegKey.h"

namespace Seminar
{

	std::mutex GuardRegKey::mutex{};

	GuardRegKey::GuardRegKey(const std::wstring& wsName) noexcept : wsName(wsName) { }

	std::unique_ptr<ICommand> GuardRegKey::Create(const std::wstring& wsName)
	{

		return std::unique_ptr<ICommand>(new GuardRegKey(wsName));

	}

	void GuardRegKey::Execute(void)
	{

		this->CreateBuilder().SaveCurrentValues().CreateWatcher();

	}

	void GuardRegKey::Update(const Subject* pSubject,
		LPCVOID) noexcept
	{

		if (this->watcher.get() != pSubject)
			return;
		
		try
		{
			
			this->SaveModifyValues().RestoreValues().watcher->Watch();

		}
		catch (const WinApiException& ex)
		{

			std::wcout << std::endl << ex.What() << std::endl;

		}
		catch (const std::exception& ex)
		{

			std::cout << std::endl << ex.what() << std::endl;

		}
		catch (...)
		{

			std::wcout << L"Unhandled exception..." << std::endl;

		}

	}

	GuardRegKey& GuardRegKey::CreateBuilder(void)
	{

		this->builder = RegKeyBuilderUnit::Create(GuardRegKey::wsName);

		return *this;

	}

	GuardRegKey& GuardRegKey::SaveCurrentValues(void)
	{

		this->currentKey = this->builder->Build();

		return *this;

	}

	GuardRegKey& GuardRegKey::CreateWatcher(void)
	{

		(this->watcher = RegKeyWatcher::Create(GuardRegKey::wsName,
			Registry::Notify::RegNotiFyChangeAll))->Watch().Attach(this);
			
		return *this;

	}

	GuardRegKey& GuardRegKey::SaveModifyValues(void)
	{

		this->modifyKey = this->builder->Build();

		return *this;

	}

	GuardRegKey& GuardRegKey::RestoreValues(void)
	{

		Restore restore{};
		
		if (this->currentKey->GetUnits().size() > this->modifyKey->GetUnits().size())
			restore = GuardRegKey::GetRestore<AddRegValue>(this,
				this->currentKey->GetUnits(),
				this->modifyKey->GetUnits(),
				this->wsName);
		else if(this->currentKey->GetUnits().size() < this->modifyKey->GetUnits().size())
			restore = GuardRegKey::GetRestore<RemoveRegValue>(this, 
				this->modifyKey->GetUnits(),
				this->currentKey->GetUnits(),
				this->wsName);
		else
			restore = GuardRegKey::GetRestore<ChangeRegValue>(this, 
				this->currentKey->GetUnits(),
				this->modifyKey->GetUnits(),
				this->wsName);
		
		if(restore.get())
			restore->Execute();

		return *this;

	}

	void GuardRegKey::Action(void) const
	{ 
	
		throw NotSupportedException(L"Action",
			ERROR_NOT_SUPPORTED);
	
	}

	void GuardRegKey::Action(const std::wstring& ws) const
	{

		std::unique_lock<std::mutex> lock(GuardRegKey::mutex);

		std::wcout << ws << std::endl;

	}

}
