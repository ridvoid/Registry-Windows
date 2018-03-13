#pragma once

#include "Header.h"

//----------------------------------------------------------------------------------

NTSTATUS CreateThread(__in PKSTART_ROUTINE,
	__in LPVOID,
	__out PHANDLE);

NTSTATUS GetKthreadByHandle(__in HANDLE,
	__out PKTHREAD*);

NTSTATUS WaitThread(__in PKTHREAD);

VOID CloseThread(__in HANDLE);

VOID FreeThread(__in PKTHREAD);

//----------------------------------------------------------------------------------
