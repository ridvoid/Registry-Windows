
#include "Header.h"
#include "NamedPipe.h"
#include "Registry.h"
#include "Thread.h"
#include "Event.h"

//----------------------------------------------------------------------------------

static const BYTE bEnd = 0xFF;

#define COUNT 2

static LPCWSTR RootKeys[COUNT] =
{

	L"\\Registry\\Machine",
	L"\\Registry\\User"

};

typedef struct _DESCRIPTORS
{

	HANDLE hPipes[COUNT];
	PKTHREAD hThreads[COUNT];
	KEVENT keStart;
	KEVENT keClose;

}DESCRIPTORS, *LPDESCRIPTORS;

static DESCRIPTORS descriptors = { null };

//----------------------------------------------------------------------------------

VOID InitScanner(VOID);

NTSTATUS Scan(VOID);

static NTSTATUS OpenPipe(VOID);

static NTSTATUS CreateWorkers(VOID);

KSTART_ROUTINE Worker;
static VOID Worker(__in LPVOID);

static VOID RecScan(__in LPCWSTR,
	__in BYTE);

static NTSTATUS Write(__in LPCBYTE,
	__in ULONG,
	__in BYTE);

static bool IsClose(VOID);

VOID CloseScanner(VOID);

static VOID CloseWorkers(VOID);

static VOID ClosePipes(VOID);

//----------------------------------------------------------------------------------
