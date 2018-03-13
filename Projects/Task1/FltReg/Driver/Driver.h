#pragma once

#include <Wdm.h>

//----------------------------------------------------------------------------------

#define nullptr 0
#define null 0

static const UNICODE_STRING usAltitude = RTL_CONSTANT_STRING(L"360001");

static const UNICODE_STRING usAutoRunKey = RTL_CONSTANT_STRING(L"\\Microsoft\\Windows\\CurrentVersion\\Run");

static LARGE_INTEGER liCookie = { null };

//----------------------------------------------------------------------------------

DRIVER_INITIALIZE DriverEntry;
NTSTATUS DriverEntry(__in PDRIVER_OBJECT,
	__in PUNICODE_STRING);

DRIVER_UNLOAD OnUnload;
VOID OnUnload(__in PDRIVER_OBJECT);

EX_CALLBACK_FUNCTION RegistryFilter;
NTSTATUS RegistryFilter(__in PVOID,
	__in PVOID,
	__in PVOID);

//----------------------------------------------------------------------------------
