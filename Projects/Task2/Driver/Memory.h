#pragma once

#include "Header.h"

//----------------------------------------------------------------------------------

#define TAG 'Junk'

NTSTATUS CreateNewMemory(SIZE_T,
	__out LPVOID*);

NTSTATUS CreateListKeys(__out LPLIST_KEYS*);

NTSTATUS CreateKeyName(__out LPKEY_NAME*);

NTSTATUS CreateString(__in SIZE_T,
	__out LPWSTR*);

VOID FreeKeyName(__in LPKEY_NAME);

VOID FreeListKeys(__in LPLIST_KEYS);

VOID FreeMemory(__in LPVOID);

//----------------------------------------------------------------------------------
