#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <winnt.h>
#include <winternl.h>
using namespace std;

struct _LIST_ENTRY *link, *item;
struct _PEB *peb;
struct _PEB_LDR_DATA *ldr;

int main(void)
{
	__asm
	{
		mov eax, fs:[0x30]
		mov peb, eax
	}

	ldr = peb->Ldr;
	link = &ldr->InMemoryOrderModuleList;

	for (item = link->Flink; item != link; item = item->Flink)
	{
		struct _LDR_DATA_TABLE_ENTRY *entry = CONTAINING_RECORD(item, struct _LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		printf("Dll location: ");
		wprintf(L"%ls", entry->FullDllName.Buffer);
		printf("\nDll base address: 0x%x\n\n", (int)entry->DllBase);
	}
}
