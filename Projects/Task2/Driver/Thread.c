#include "Thread.h"

//-------------------------------------------------------------------------------------

NTSTATUS CreateThread(__in PKSTART_ROUTINE pStartRountine,
	__in LPVOID lpv,
	__out PHANDLE pHandle)
{

	NTSTATUS status = STATUS_SUCCESS;

	HANDLE hThread = nullptr;
	
	OBJECT_ATTRIBUTES objAttr = { null };

	InitializeObjectAttributes(&objAttr,
		nullptr,
		OBJ_KERNEL_HANDLE,
		nullptr,
		nullptr);

	return PsCreateSystemThread(pHandle,
		THREAD_ALL_ACCESS,
		&objAttr,
		nullptr,
		nullptr,
		pStartRountine,
		lpv);

}

//-------------------------------------------------------------------------------------

NTSTATUS GetKthreadByHandle(__in HANDLE hThread,
	__out PKTHREAD* ppKthread)
{

	return ObReferenceObjectByHandle(hThread,
		THREAD_ALL_ACCESS,
		nullptr,
		KernelMode,
		(LPVOID*)ppKthread,
		nullptr);

}

//-------------------------------------------------------------------------------------

VOID CloseThread(__in HANDLE hThread)
{

	if (!hThread)
		return;

	ZwClose(hThread);

}

//-------------------------------------------------------------------------------------

NTSTATUS WaitThread(__in PKTHREAD pKthread)
{

	return KeWaitForSingleObject(pKthread,
		Executive,
		KernelMode,
		FALSE,
		nullptr);

}

//-------------------------------------------------------------------------------------

VOID FreeThread(__in PKTHREAD pKthread)
{

	if (!pKthread)
		return;

	ObDereferenceObject(pKthread);

}

//-------------------------------------------------------------------------------------
