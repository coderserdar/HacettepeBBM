#ifndef __MEMORY_H
#define __MEMORY_H

#include <multiboot.h>
#include <stddef.h>

class Module
{
public:
	void* Start;
	void* End;
	const char* String;
	unsigned long Reserved;

	size_t Size() const
	{
		return (size_t) End - (size_t) Start;
	}
};

class Memory
{
public:
	static void Initialize(multiboot_info* info);

	static int ModuleCount;
	static Module* Modules;
};

class HighMemoryAllocator
{
private:
	static void Initialize(multiboot_info* info);
	static void RegisterBlock(void* block_start, void* block_end);

public:
	static void* KernelStart;
	static void* KernelEnd;

	static size_t TotalSize;
	static size_t AvailableMemory();

	static void* Allocate(size_t size);
	static void Free(void *pointer);

	static void PrintMemoryMap();

	friend class Memory;
};

class LowMemoryAllocator
{
private:
	static char* last;
	static char* limit;

	static void Initialize(size_t size);

public:
	static size_t TotalSize;
	static size_t AvailableMemory;

	static void* Allocate(size_t size);

	friend class Memory;
};

void TestHighMemoryAllocator();

#endif
