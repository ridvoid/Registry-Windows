#include "Driver.h"

//-------------------------------------------------------------------------------------

NTSTATUS DriverEntry(__in PDRIVER_OBJECT pDriverObject,
	__in PUNICODE_STRING pUnicodeString)
{

	NTSTATUS status = STATUS_SUCCESS;

	pDriverObject->DriverUnload = OnUnload;

	status = CmRegisterCallbackEx(RegistryFilter,
		&usAltitude,
		pDriverObject,
		nullptr,
		&liCookie,
		nullptr);
	if (!NT_SUCCESS(status))
	{

#if DBG

		DbgPrint("RegDrvFlt -> DriverEntry: Failed CmRegisterCallbackEx = %x",
			status);
#endif

	}
	else
	{

#if DBG

		DbgPrint("RegDrvFlt -> DriverEntry: OK");

#endif

	}

	return status;
	
}

//-------------------------------------------------------------------------------------

VOID OnUnload(__in PDRIVER_OBJECT DriverObject)
{

	NTSTATUS status = CmUnRegisterCallback(liCookie);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("RegDrvFlt -> OnUnloadDriver: Failed CmUnRegisterCallback = %x",
			status);
#endif

	}
	else
	{

#if DBG
		DbgPrint("RegDrvFlt -> OnUnloadDriver: OK");
#endif

	}

}

//-------------------------------------------------------------------------------------

NTSTATUS RegistryFilter(__in PVOID context,
	__in PVOID argument1,
	__in PVOID argument2)
{
	
	NTSTATUS status = STATUS_SUCCESS;

	REG_NOTIFY_CLASS regNotifyClass = (REG_NOTIFY_CLASS)(ULONG_PTR)argument1;

	PREG_CREATE_KEY_INFORMATION pRegCreateKeyInfo = nullptr;

	__try
	{

		switch (regNotifyClass)
		{

		case RegNtPreCreateKeyEx:
		case RegNtPreOpenKeyEx:
			pRegCreateKeyInfo = (PREG_CREATE_KEY_INFORMATION)argument2;
			if (pRegCreateKeyInfo->CompleteName->Length > usAutoRunKey.Length)
			{

				if (wcsstr(pRegCreateKeyInfo->CompleteName->Buffer,
					usAutoRunKey.Buffer))
				{

#if DBG
					DbgPrint("RegDrvFlt -> RegistryFilter: Key = %ws",
						pRegCreateKeyInfo->CompleteName->Buffer);
#endif

					status = STATUS_ACCESS_DENIED;

				}

			}

		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER){ }

	return status;

}

//-------------------------------------------------------------------------------------
