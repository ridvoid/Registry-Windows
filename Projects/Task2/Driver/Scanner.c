
#include "Scanner.h"

//----------------------------------------------------------------------------------

VOID InitScanner(VOID)
{

	CreateEvent(&descriptors.keStart,
		SynchronizationEvent,
		FALSE);

	CreateEvent(&descriptors.keClose,
		NotificationEvent,
		FALSE);

}

//----------------------------------------------------------------------------------

NTSTATUS Scan(VOID)
{

	NTSTATUS status = OpenPipe();
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> Scan: Error OpenPipe = %x",
			status);
#endif

		return status;

	}

	status = CreateWorkers();
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> Scan: Error CreateWorkers = %x",
			status);
#endif

		
	}

	return status;

}

//----------------------------------------------------------------------------------

NTSTATUS OpenPipe(VOID)
{

	NTSTATUS status = STATUS_SUCCESS;
	BYTE i = null;

	for (; i < COUNT; ++i)
	{

		status = CreatePipe(&descriptors.hPipes[i]);
		if (!NT_SUCCESS(status))
		{
			
			ClosePipes();
			
			break;
			
		}

	}

	return status;

}

//----------------------------------------------------------------------------------

NTSTATUS CreateWorkers(VOID)
{

	NTSTATUS status = STATUS_SUCCESS;
	BYTE i = null;

	for (; i < COUNT; ++i)
	{

		HANDLE hThread = nullptr;

		status = CreateThread(Worker,
			&i,
			&hThread);
		if (!NT_SUCCESS(status))
			break;

		WaitEvent(&descriptors.keStart,
			nullptr);
			
		status = GetKthreadByHandle(hThread,
			&descriptors.hThreads[i]);

		CloseThread(hThread);

		if (!NT_SUCCESS(status))
			break;

	}
	
	if (!NT_SUCCESS(status))
		CloseScanner();
			
	return status;

}

//----------------------------------------------------------------------------------

VOID Worker(__in LPVOID lpv)
{

	NTSTATUS status = STATUS_SUCCESS;

	BYTE i = *(LPCBYTE)(lpv);

	SetEvent(&descriptors.keStart);

	RecScan(RootKeys[i],
		i);

	if (!IsClose())
	{

		status = Write(&bEnd,
			sizeof(bEnd),
			i);
		if (!NT_SUCCESS(status))
		{

#if DBG
			DbgPrint("ScanReg -> Worker: Failed Write = %x",
				status);
#endif

		}

	}

#if DBG
	DbgPrint("ScanReg -> Worker: Exit = %x",
		i);
#endif

	PsTerminateSystemThread(STATUS_SUCCESS);

}

//----------------------------------------------------------------------------------

VOID RecScan(__in LPCWSTR lpcwstrName,
	__in BYTE i)
{

	NTSTATUS status = STATUS_SUCCESS;
	
	HANDLE hKey = nullptr;

	LPLIST_KEYS lpListKeys = nullptr;

	if (IsClose())
		return;

	status = OpenKey(lpcwstrName,
		&hKey);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> RecScan: Failed OpenKey %ws = %x",
			lpcwstrName,
			status);
#endif

		return;

	}

	__try
	{

		PLIST_ENTRY pListEntry = nullptr;

		LPKEY_NAME lpKeyName = nullptr;

		status = Write((LPCBYTE)lpcwstrName,
			wcslen(lpcwstrName) * sizeof(WCHAR),
			i);
		if (!NT_SUCCESS(status))
		{

#if DBG
			DbgPrint("ScanReg -> RecScan: Failed Write = %x",
				status);
#endif

			return;

		}

		status = GetListSubKeys(lpcwstrName,
			hKey,
			&lpListKeys);
		if (!NT_SUCCESS(status))
		{

#if DBG
			DbgPrint("ScanReg -> RecScan: Failed GetListSubKeys %ws = %x",
				lpcwstrName,
				status);
#endif

			return;

		}

		for (pListEntry = lpListKeys->listKeys.Flink;
			pListEntry != &lpListKeys->listKeys;
			pListEntry = pListEntry->Flink)
		{

			lpKeyName = CONTAINING_RECORD(pListEntry,
				KEY_NAME,
				linkField);

			RecScan(lpKeyName->lpwstrName,
				i);

		}

	}
	__finally
	{

		CloseKey(hKey);

		FreeListSubKeys(lpListKeys);

	}

}

//----------------------------------------------------------------------------------

NTSTATUS Write(__in LPCBYTE lpcBuf,
	__in ULONG sizeBuf,
	__in BYTE i)
{

	return WriteToPipe(descriptors.hPipes[i],
		(LPCVOID)lpcBuf,
		sizeBuf);

}

//----------------------------------------------------------------------------------

bool IsClose(VOID)
{

	LARGE_INTEGER li = { null };

	return WaitEvent(&descriptors.keClose,
		&li) == STATUS_SUCCESS;

}

//----------------------------------------------------------------------------------

VOID CloseScanner(VOID)
{

	SetEvent(&descriptors.keClose);

	CloseWorkers();

	ClosePipes();
	
	ResetEvent(&descriptors.keClose);

}

//----------------------------------------------------------------------------------

VOID CloseWorkers(VOID)
{
	
	BYTE i = null;

	for (; i < COUNT; ++i)
	{

		if (!descriptors.hThreads[i])
			continue;

		WaitThread(descriptors.hThreads[i]);

		FreeThread(descriptors.hThreads[i]);

		descriptors.hThreads[i] = nullptr;
		
	}

}

//----------------------------------------------------------------------------------

VOID ClosePipes(VOID)
{

	BYTE i = null;

	for (; i < COUNT; ++i)
	{

		if (!descriptors.hPipes[i])
			continue;

		ClosePipe(descriptors.hPipes[i]);

		descriptors.hPipes[i] = nullptr;
		
	}

}

//----------------------------------------------------------------------------------

