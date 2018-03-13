#include "Memory.h"

//-------------------------------------------------------------------------------------

NTSTATUS CreateNewMemory(SIZE_T size,
	__out LPVOID* lppv)
{

	LPVOID lpv = ExAllocatePoolWithTag(PagedPool,
		size,
		TAG);
	if (!lpv)
		return STATUS_INSUFFICIENT_RESOURCES;

	RtlZeroMemory(lpv,
		size);

	*lppv = lpv;

	return STATUS_SUCCESS;

}

//-------------------------------------------------------------------------------------

NTSTATUS CreateListKeys(__out LPLIST_KEYS* lppListKeys)
{

	LPLIST_KEYS lpListKeys = nullptr;

	NTSTATUS status = CreateNewMemory(sizeof(LIST_KEYS),
		&lpListKeys);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> CreateListKeys: Failed CreateNewMemory = %x",
			status);
#endif

		return status;

	}

	InitializeListHead(&lpListKeys->listKeys);

	*lppListKeys = lpListKeys;

	return status;

}

//-------------------------------------------------------------------------------------

NTSTATUS CreateKeyName(__out LPKEY_NAME* lppKeyName)
{

	LPKEY_NAME lpKeyName = nullptr;

	NTSTATUS status = CreateNewMemory(sizeof(KEY_NAME),
		&lpKeyName);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> CreateKeyName: Failed CreateNewMemory = %x",
			status);
#endif

		return status;

	}

	*lppKeyName = lpKeyName;

	return status;

}

//-------------------------------------------------------------------------------------

NTSTATUS CreateString(__in SIZE_T size,
	__out LPWSTR* lppwstr)
{

	LPWSTR lpwstr = nullptr;

	NTSTATUS status = CreateNewMemory(size * sizeof(WCHAR),
		&lpwstr);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> CreateString: Failed CreateNewMemory = %x",
			status);
#endif

		return status;

	}

	*lppwstr = lpwstr;

	return status;

}

//-------------------------------------------------------------------------------------

VOID FreeKeyName(__in LPKEY_NAME lpKeyName)
{

	if (!lpKeyName)
		return;

	FreeMemory(lpKeyName->lpwstrName);

	FreeMemory(lpKeyName);

}

//-------------------------------------------------------------------------------------

VOID FreeListKeys(__in LPLIST_KEYS lpListKeys)
{

	LPKEY_NAME lpKeyName = nullptr;

	PLIST_ENTRY pListEntry = nullptr;

	if (!lpListKeys)
		return;
	
	pListEntry = RemoveHeadList(&lpListKeys->listKeys);
	while (pListEntry != &lpListKeys->listKeys)
	{

		lpKeyName = CONTAINING_RECORD(pListEntry,
			KEY_NAME,
			linkField);

		FreeKeyName(lpKeyName);

		pListEntry = RemoveHeadList(&lpListKeys->listKeys);

	}

	FreeMemory(lpListKeys);

}

//-------------------------------------------------------------------------------------

VOID FreeMemory(LPVOID lpv)
{

	if (!lpv)
		return;

	ExFreePoolWithTag(lpv,
		TAG);

}

//-------------------------------------------------------------------------------------

