#pragma once

#include <Wdm.h>

#define IOCTL_SCAN \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)