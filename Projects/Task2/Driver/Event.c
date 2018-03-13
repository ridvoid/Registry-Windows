#include "Event.h"

//-------------------------------------------------------------------------------------

VOID CreateEvent(__out PRKEVENT pkEvent,
	__in EVENT_TYPE eventType,
	__in BOOLEAN bState)
{

	KeInitializeEvent(pkEvent,
		eventType,
		bState);

}

//-------------------------------------------------------------------------------------

NTSTATUS WaitEvent(__in PRKEVENT pkEvent,
	__in PLARGE_INTEGER pliTimeout)
{

	return KeWaitForSingleObject(pkEvent,
		Executive,
		KernelMode,
		FALSE,
		pliTimeout);

}

//-------------------------------------------------------------------------------------

LONG SetEvent(__in PRKEVENT pkEvent)
{

	return KeSetEvent(pkEvent,
		IO_NO_INCREMENT,
		FALSE);

}

//-------------------------------------------------------------------------------------

LONG ResetEvent(__in PRKEVENT pkEvent)
{

	return KeResetEvent(pkEvent);

}

//-------------------------------------------------------------------------------------




