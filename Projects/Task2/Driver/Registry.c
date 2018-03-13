#include "Registry.h"

//----------------------------------------------------------------------------------

NTSTATUS OpenKey(__in LPCWSTR lpcwstrName,
	__out PHANDLE phKey)
{

	UNICODE_STRING usName = { null };

	OBJECT_ATTRIBUTES objAttr = { null };

	RtlInitUnicodeString(&usName,
		lpcwstrName);

	InitializeObjectAttributes(&objAttr,
		&usName,
		OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
		nullptr,
		nullptr);

	return ZwOpenKey(phKey,
		KEY_READ,
		&objAttr);
	
}

//----------------------------------------------------------------------------------

NTSTATUS GetListSubKeys(__in LPCWSTR lpcwstrName,
	__in HANDLE hKey,
	__out LPLIST_KEYS* lppListKeys)
{

	NTSTATUS status = STATUS_SUCCESS;

	LPLIST_KEYS lpListKeys = nullptr;

	ULONG i = null, ulCount = null;

	status = GetCountSubKeys(hKey,
		&ulCount);
	if (!NT_SUCCESS(status))
		return status;

	status = CreateListKeys(&lpListKeys);
	if (!NT_SUCCESS(status))
		return status;

	__try
	{

		for (; i < ulCount; ++i)
		{

			LPKEY_NAME lpKeyName = nullptr;
			
			status = GetKeyName(lpcwstrName,
				hKey,
				i,
				&lpKeyName);
			if (!NT_SUCCESS(status))
			{

				if (status != STATUS_NO_MORE_ENTRIES)
					return status;
				else
					return STATUS_SUCCESS;

			}

			InsertTailList(&lpListKeys->listKeys,
				&lpKeyName->linkField);

		}

	}
	__finally
	{
	
		if (!NT_SUCCESS(status))
			FreeListSubKeys(lpListKeys);
		else
			*lppListKeys = lpListKeys;

	}

	return status;

}

//----------------------------------------------------------------------------------

NTSTATUS GetSizeFullKeyInfo(__in HANDLE hKey,
	__out LPULONG lpulSize)
{

	ULONG ulSize = null;

	NTSTATUS status = ZwQueryKey(hKey,
		KeyFullInformation,
		nullptr,
		null,
		&ulSize);
	if (status != STATUS_BUFFER_TOO_SMALL && 
		status != STATUS_BUFFER_OVERFLOW && 
		!ulSize)
		return status;

	*lpulSize = ulSize;

	return STATUS_SUCCESS;

}

//----------------------------------------------------------------------------------

NTSTATUS GetCountSubKeys(__in HANDLE hKey,
	__out LPULONG lpulCount)
{

	NTSTATUS status = STATUS_SUCCESS;

	PKEY_FULL_INFORMATION lpKeyFullInfo = nullptr;

	ULONG ulSize = null;

	status = GetSizeFullKeyInfo(hKey,
		&ulSize);
	if (!NT_SUCCESS(status))
		return status;

	status = CreateNewMemory(ulSize,
		&lpKeyFullInfo);
	if (!NT_SUCCESS(status))
		return status;

	__try
	{

		status = ZwQueryKey(hKey,
			KeyFullInformation,
			lpKeyFullInfo,
			ulSize,
			&ulSize);
		if (!NT_SUCCESS(status))
			return status;

		*lpulCount = lpKeyFullInfo->SubKeys;

	}
	__finally
	{

		FreeMemory(lpKeyFullInfo);
		
	}

	return status;

}

//----------------------------------------------------------------------------------

NTSTATUS GetSizeKeyName(__in HANDLE hKey,
	__in ULONG i,
	__out LPULONG lpulSize)
{

	ULONG ulSize = null;

	NTSTATUS status = ZwEnumerateKey(hKey,
		i,
		KeyBasicInformation,
		nullptr,
		null,
		&ulSize);
	if (status != STATUS_BUFFER_TOO_SMALL && 
		status != STATUS_BUFFER_OVERFLOW && 
		!ulSize)
		return status;

	*lpulSize = ulSize;

	return STATUS_SUCCESS;

}

//----------------------------------------------------------------------------------

NTSTATUS GetKeyName(__in LPCWSTR lpcwstrName,
	__in HANDLE hKey,
	__in ULONG i,
	__out LPKEY_NAME* lppKeyName)
{

	NTSTATUS status = STATUS_SUCCESS;

	PKEY_BASIC_INFORMATION lpKeyBasicInfo = nullptr;

	LPKEY_NAME lpKeyName = nullptr;

	ULONG ulFullNameLen = null;

	ULONG ulSize = null;

	status = GetSizeKeyName(hKey,
		i,
		&ulSize);
	if (!NT_SUCCESS(status))
		return status;

	status = CreateNewMemory(ulSize,
		&lpKeyBasicInfo);
	if (!NT_SUCCESS(status))
		return status;

	__try
	{

		status = ZwEnumerateKey(hKey,
			i,
			KeyBasicInformation,
			lpKeyBasicInfo,
			ulSize,
			&ulSize);
		if (!NT_SUCCESS(status))
			return status;

		status = CreateKeyName(&lpKeyName);
		if (!NT_SUCCESS(status))
			return status;

		ulFullNameLen = wcslen(lpcwstrName) + lpKeyBasicInfo->NameLength / sizeof(WCHAR) + sizeof(WCHAR);

		status = CreateString(ulFullNameLen,
			&lpKeyName->lpwstrName);
		if (!NT_SUCCESS(status))
			return status;

		swprintf_s(lpKeyName->lpwstrName,
			ulFullNameLen,
			L"%s\\",
			lpcwstrName);

		RtlCopyMemory(&lpKeyName->lpwstrName[wcslen(lpKeyName->lpwstrName)],
			lpKeyBasicInfo->Name,
			lpKeyBasicInfo->NameLength);

		lpKeyName->lpwstrName[ulFullNameLen - 1] = '\0';

	}
	__finally
	{

		FreeMemory(lpKeyBasicInfo);

		if (!NT_SUCCESS(status))
			FreeKeyName(lpKeyName);
		else
			*lppKeyName = lpKeyName;

	}

	return status;

}

//----------------------------------------------------------------------------------

VOID FreeListSubKeys(__in LPLIST_KEYS lpListKeys)
{

	FreeListKeys(lpListKeys);

}

//----------------------------------------------------------------------------------

VOID CloseKey(__in HANDLE hKey)
{

	if (!hKey)
		return;

	ZwClose(hKey);

}

//----------------------------------------------------------------------------------
