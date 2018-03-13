
#include "ChangeRegValue.h"

namespace Seminar
{

	void ChangeRegValue::Execute(void)
	{

		Registry::Open(IRestoreRegValue::wsName,
			Registry::Access::KeySetValue)->SetValue(Registry::KeyValue(IRestoreRegValue::regValue->GetName(),
				static_cast<Registry::Type>(IRestoreRegValue::regValue->GetType()),
				IRestoreRegValue::regValue->GetData()));

		IRestoreRegValue::Show(L"Changed value");

	}

}
