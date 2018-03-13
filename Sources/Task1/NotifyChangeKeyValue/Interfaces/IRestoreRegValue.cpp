
#include "IRestoreRegValue.h"

namespace Seminar
{

	IRestoreRegValue::IRestoreRegValue(const IReceiver* pReceiver,
		const std::wstring& wsName,
		const RegValue& regValue) noexcept 
		: 
		ICommand(pReceiver),
		wsName(wsName), 
		regValue(regValue) 
		{ }

	void IRestoreRegValue::Show(const std::wstring& ws) const
	{

		std::wostringstream wos;

		wos << this->wsName << std::endl;

		wos << ws << L" \"" << this->regValue->GetName() << L"\"" << std::endl;

		std::copy(this->regValue->GetData().cbegin(),
			this->regValue->GetData().cend(),
			std::ostream_iterator<BYTE, wchar_t>(wos, L" "));

		wos << std::endl;

		ICommand::OnAction(wos.str());

	}

}
