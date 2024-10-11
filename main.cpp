#include <ntifs.h>
#include "ref.h"

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT drv, PUNICODE_STRING)
{
	// RAII
	NTSTATUS status = STATUS_SUCCESS;
	PVOID    p1 = nullptr, p2 = nullptr;
	do
	{
		p1 = ExAllocatePool(NonPagedPool, 0x1234);
		if (p1 == nullptr)
		{
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}
		// ExFreePool
		// RAII 类， 模板类  `_Fn`
		// success
		p2 = MmMapIoSpace({ 0xfee00000 }, 0x10, MmNonCached);
		if (p2 == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		// do some things
	} while (false);

	// clean up
	if (p1)
	{
		ExFreePool(p1);
	}
	if (p2)
	{
		MmUnmapIoSpace(p2, 0x10);
	}
	return status;
}