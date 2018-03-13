#pragma once

#include "Header.h"
#include "Memory.h"

//----------------------------------------------------------------------------------

NTSTATUS OpenKey(__in LPCWSTR,
	__out PHANDLE);

NTSTATUS GetListSubKeys(__in LPCWSTR,
	__in HANDLE,
	__out LPLIST_KEYS*);

static NTSTATUS GetSizeFullKeyInfo(__in HANDLE,
	__out LPULONG);

static NTSTATUS GetCountSubKeys(__in HANDLE,
	__out LPULONG);

static NTSTATUS GetSizeKeyName(__in HANDLE,
	__in ULONG,
	__out LPULONG);

static NTSTATUS GetKeyName(__in LPCWSTR,
	__in HANDLE,
	__in ULONG,
	__out LPKEY_NAME*);

VOID FreeListSubKeys(__in LPLIST_KEYS);

VOID CloseKey(__in HANDLE);

//----------------------------------------------------------------------------------

