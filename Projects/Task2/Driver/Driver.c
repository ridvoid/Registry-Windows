#include "Driver.h"

//-------------------------------------------------------------------------------------

NTSTATUS DriverEntry(__in PDRIVER_OBJECT pDriverObject,
	__in PUNICODE_STRING pUnicodeString)
{

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT pdo = nullptr;
	
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = OnIoctl;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;
	pDriverObject->DriverUnload = OnUnload;

	status = IoCreateDevice(pDriverObject,
		null,
		(PUNICODE_STRING)&usDevName,
		FILE_DEVICE_UNKNOWN,
		null,
		TRUE,
		&pdo);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> DriverEntry: Failed IoCreateDevice = %x",
			status);
#endif

		return status;

	}

	pdo->Flags |= DO_BUFFERED_IO;

	status = IoCreateSymbolicLink((PUNICODE_STRING)&usSymLink,
		(PUNICODE_STRING)&usDevName);
	if (!NT_SUCCESS(status))
	{

#if DBG
		DbgPrint("ScanReg -> DriverEntry: Failed IoCreateSymbolicLink = %x",
			status);
#endif

		IoDeleteDevice(pdo);

	}
	else
	{

#if DBG
		DbgPrint("ScanReg -> DriverEntry = OK");
#endif

	}

	return status;

}

//-------------------------------------------------------------------------------------

NTSTATUS OnCreate(__in PDEVICE_OBJECT pDeviceObject,
	__in PIRP pIrp)
{
	
	InitScanner();

#if DBG
		DbgPrint("ScanReg -> OnCreate: OK");
#endif

	return CompleteRequest(pIrp,
		STATUS_SUCCESS,
		null);

}

//-------------------------------------------------------------------------------------

NTSTATUS OnIoctl(__in PDEVICE_OBJECT pDeviceObject,
	__in PIRP pIrp)
{

	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION psl = IoGetCurrentIrpStackLocation(pIrp);
	
	switch (psl->Parameters.DeviceIoControl.IoControlCode)
	{

	case IOCTL_SCAN:

		status = Scan();

		break;

	default:

		status = STATUS_INVALID_PARAMETER;

#if DBG
		DbgPrint("ScanReg -> OnIoctl: Invalid IOCTL");
#endif

	}

	return CompleteRequest(pIrp,
		status,
		null);

}

//----------------------------------------------------------------------------------

NTSTATUS OnClose(__in PDEVICE_OBJECT pDeviceObject,
	__in PIRP pIrp)
{
	
	CloseScanner();

#if DBG
	DbgPrint("ScanReg -> OnClose: OK");
#endif

	return CompleteRequest(pIrp,
		STATUS_SUCCESS,
		null);

}

//----------------------------------------------------------------------------------

VOID OnUnload(__in PDRIVER_OBJECT pDriverObject)
{

	IoDeleteSymbolicLink((PUNICODE_STRING)&usSymLink);

	IoDeleteDevice(pDriverObject->DeviceObject);

#if DBG
	DbgPrint("ScanReg -> OnUnload = OK");
#endif

}

//----------------------------------------------------------------------------------

NTSTATUS CompleteRequest(__in PIRP pIrp,
	__in NTSTATUS status,
	__in ULONG_PTR ulptrSize)
{

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = ulptrSize;

	IoCompleteRequest(pIrp,
		IO_NO_INCREMENT);

	return status;

}

//----------------------------------------------------------------------------------
