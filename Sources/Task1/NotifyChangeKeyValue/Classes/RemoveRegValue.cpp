
#include "RemoveRegValue.h"

namespace Seminar
{

	void RemoveRegValue::Execute(void)
	{

		Registry::Open(IRestoreRegValue::wsName,
			Registry::Access::KeySetValue)->DeleteValue(IRestoreRegValue::regValue->GetName());

		IRestoreRegValue::Show(L"Removed value");

	}

}