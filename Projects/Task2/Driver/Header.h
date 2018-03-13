#pragma once

#include <Ntddk.h>
#include <Wdm.h>
#include <strsafe.h>

//----------------------------------------------------------------------------------

#define nullptr 0
#define null 0

typedef void* LPVOID;
typedef const LPVOID LPCVOID;
typedef ULONG* LPULONG;
typedef unsigned char BYTE;
typedef unsigned char bool;
typedef const BYTE* LPCBYTE;

//----------------------------------------------------------------------------------

typedef struct _KEY_NAME
{

	LPWSTR lpwstrName;

	LIST_ENTRY linkField;

}KEY_NAME, *LPKEY_NAME;

typedef struct _LIST_KEYS
{

	LIST_ENTRY listKeys;

}LIST_KEYS, *LPLIST_KEYS;

//----------------------------------------------------------------------------------
