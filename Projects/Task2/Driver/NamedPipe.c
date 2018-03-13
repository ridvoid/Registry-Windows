
#include "NamedPipe.h"

//-------------------------------------------------------------------------------------

NTSTATUS CreatePipe(__out PHANDLE pHandle)
{

	OBJECT_ATTRIBUTES objAttr = { null };
	IO_STATUS_BLOCK ioStatBlock = { null };

	InitializeObjectAttributes(&objAttr,
		(PUNICODE_STRING)&usPipeName,
		OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
		nullptr,
		nullptr);

	return ZwCreateFile(pHandle,
		GENERIC_WRITE,
		&objAttr,
		&ioStatBlock,
		nullptr,
		FILE_ATTRIBUTE_NORMAL,
		null,
		FILE_OPEN,
		FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_ALERT,
		nullptr,
		null);

}

//-------------------------------------------------------------------------------------

NTSTATUS WriteToPipe(__in HANDLE hPipe,
	__in LPCVOID lpcvBuf,
	__in ULONG ulSizeBuf)
{

	IO_STATUS_BLOCK ioStatBlock = { null };
	
	return ZwWriteFile(hPipe,
		null,
		nullptr,
		nullptr,
		&ioStatBlock,
		lpcvBuf,
		ulSizeBuf,
		nullptr,
		nullptr);

}

//-------------------------------------------------------------------------------------

VOID ClosePipe(__in HANDLE hPipe)
{

	if (!hPipe)
		return;

	ZwClose(hPipe);

}

//-------------------------------------------------------------------------------------

