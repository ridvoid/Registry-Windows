#pragma once

#include "Ioctl.h"
#include "Scanner.h"

//----------------------------------------------------------------------------------

static const UNICODE_STRING usDevName = RTL_CONSTANT_STRING(L"\\Device\\{BA9510F6-C5A2-4755-BC94-2896E5DB3B06}");

static const UNICODE_STRING usSymLink = RTL_CONSTANT_STRING(L"\\DosDevices\\{BA9510F6-C5A2-4755-BC94-2896E5DB3B06}");

//----------------------------------------------------------------------------------

DRIVER_INITIALIZE DriverEntry;
NTSTATUS DriverEntry(__in PDRIVER_OBJECT,
	__in PUNICODE_STRING);

__drv_dispatchType(IRP_MJ_CREATE)
DRIVER_DISPATCH OnCreate;
NTSTATUS OnCreate(__in PDEVICE_OBJECT,
	__in PIRP);

__drv_dispatchType(IRP_MJ_DEVICE_CONTROL)
DRIVER_DISPATCH OnIoctl;
NTSTATUS OnIoctl(__in PDEVICE_OBJECT,
	__in PIRP);

__drv_dispatchType(IRP_MJ_CLOSE)
DRIVER_DISPATCH OnClose;
NTSTATUS OnClose(__in PDEVICE_OBJECT,
	__in PIRP);

DRIVER_UNLOAD OnUnload;
VOID OnUnload(__in PDRIVER_OBJECT);

NTSTATUS CompleteRequest(__in PIRP,
	__in NTSTATUS,
	__in ULONG_PTR);

//----------------------------------------------------------------------------------
