
#include "IApplication.h"

namespace Seminar
{

	IApplication& IApplication::SetInstance(HINSTANCE hInstance) noexcept
	{

		this->hInstance = hInstance;

		return *this;

	}

	HINSTANCE IApplication::GetInstance(void) const noexcept
	{

		return this->hInstance;

	}

	int IApplication::Execute(void)
	{

		this->SaveArguments().ToLowerArguments();

		return{};

	}

	IApplication& IApplication::SaveArguments(void)
	{

		this->vecArguments = CommandLineArgument::GetCommandLines();

		this->vecArguments.erase(this->vecArguments.cbegin());

		return *this;

	}

	IApplication& IApplication::ToLowerArguments(void)
	{

		for (auto& i : this->vecArguments)
			i = Convert::ToLower(i);

		return *this;

	}

	IApplication& IApplication::CheckArguments(void)
	{

		if (!this->vecArguments.size())
			throw CommandLineArgumentException(L"Invalid command line arguments");

		return *this;

	}

	void IApplication::ExecuteCommands(void) const
	{

		for (const auto& i : IApplication::listCommands)
			i->Execute();

	}

}