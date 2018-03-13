#pragma once

#include "Header.h"

//----------------------------------------------------------------------------------

static const UNICODE_STRING usPipeName = RTL_CONSTANT_STRING(L"\\??\\pipe\\{BA9510F6-C5A2-4755-BC94-2896E5DB3B06}");

NTSTATUS CreatePipe(__out PHANDLE);

NTSTATUS WriteToPipe(__in HANDLE,
	__in LPCVOID,
	__in ULONG);

VOID ClosePipe(__in HANDLE);

//----------------------------------------------------------------------------------
