#pragma once

#include "Header.h"

//----------------------------------------------------------------------------------

VOID CreateEvent(__out PRKEVENT,
	__in EVENT_TYPE,
	__in BOOLEAN);

NTSTATUS WaitEvent(__in PRKEVENT,
	__in PLARGE_INTEGER);

LONG SetEvent(__in PRKEVENT);

LONG ResetEvent(__in PRKEVENT);

//----------------------------------------------------------------------------------
