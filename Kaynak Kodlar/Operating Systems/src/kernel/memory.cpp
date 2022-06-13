#include <memory.h>
#include <system.h>

#include <stdio.h>
#include <stdlib.h>

#define RESERVED_LOWMEM	0x1000		// 16K of lower memory is reserved for emergency use
#define FOUR_GB_LIMIT	0xffffffff	// 4 Gigabyte limit

struct AllocationBlock
{
	size_t size;
	bool used;

	AllocationBlock *next;
	AllocationBlock *prev;

	unsigned checksum;

	char data[];

	void* operator new(size_t size, void *p) { return p; }

	void UpdateChecksum()
	{
		checksum = (unsigned)size ^ (unsigned)used ^ (unsigned)prev ^ (unsigned)next;
	}

	void VerifyBlock()
	{
		if(checksum != ((unsigned)size ^ (unsigned)used ^ (unsigned)prev ^ (unsigned)next))
			DumpInfoAndPanic("checksum error");

		if(next != NULL && (size_t) next != (size_t) this + size + sizeof(AllocationBlock))
			DumpInfoAndPanic("size mismatch");

		if(next != NULL && next <= this)
			DumpInfoAndPanic("next item is before the current one");

		if(prev != NULL && prev >= this)
			DumpInfoAndPanic("previous item is after the current one");
	}

private:
	void DumpInfoAndPanic(const char* error)
	{
		System::Panic("Memory corruption, %s in block at %p.\n"
				"[ used = %d, size = 0x%x, prev = %p, next = %p,\n  checksum = 0x%x, mismatch = 0x%x ]",
				error, this, used, size, prev, next, checksum,
				(unsigned)size ^ (unsigned)used ^ (unsigned)prev ^ (unsigned)next ^ checksum);
	}
};

class MemoryBlock
{
private:
	AllocationBlock* base;
	AllocationBlock* last;
	void* limit;

	void* AllocateFromBlock(AllocationBlock* block, size_t size)
	{
		block->VerifyBlock();

		AllocationBlock* next;

		next = new ((char*) block + sizeof(AllocationBlock) + size) AllocationBlock();

		next->size = block->size - sizeof(AllocationBlock) - size;
		next->next = block->next;
		next->prev = block;
		
		next->used = false;

		next->UpdateChecksum();

		block->size = size;
		block->next = next;

		block->used = true;

		block->UpdateChecksum();

		if(last == block)
			last = next;

		return block->data;
	}

public:
	MemoryBlock* next;

	void* operator new(size_t size) { return LowMemoryAllocator::Allocate(size); }
	void operator delete(void* p) { }

	MemoryBlock(void *base, size_t size)
	{
		printk("  Available memory block at %p with length %uK\n", base, size / 1024);

		this->base = new (base) AllocationBlock();

		this->base->size = size - sizeof(AllocationBlock);
		this->base->used = false;

		this->base->prev = NULL;
		this->base->next = NULL;

		this->base->UpdateChecksum();

		last = this->base;

		limit = (char*) base + size;
	}

	void* Allocate(size_t size)
	{
		for(AllocationBlock* block = last; block != NULL; block = block->next)
			if(block->size >= size)
				return AllocateFromBlock(block, size);

		for(AllocationBlock* block = base; block != last; block = block->next)
			if(block->size >= size)
				return AllocateFromBlock(block, size);

		return NULL;
	}

	void Free(void* pointer)
	{
		AllocationBlock* block = (AllocationBlock*) pointer - 1;

		block->VerifyBlock();

		if(!block->used)
			System::Panic("Trying to free unused memory block");

		block->used = false;

		if(block->next != NULL)
		{
			block->next->VerifyBlock();

			if(!block->next->used)
			{
				if(last == block->next)
					last = block;

				block->size += block->next->size + sizeof(AllocationBlock);
				block->next = block->next->next;

				if(block->next != NULL)
				{
					block->next->prev = block;
					block->next->UpdateChecksum();
				}
			}
		}

		if(block->prev != NULL)
		{
			block->prev->VerifyBlock();

			if(!block->prev->used)
			{
				if(last == block)
					last = block->prev;

				block->prev->size += block->size + sizeof(AllocationBlock);
				block->prev->next = block->next;

				if(block->next != NULL)
				{
					block->next->prev = block->prev;
					block->next->UpdateChecksum();
				}

				block->prev->UpdateChecksum();
			}
		}

		block->UpdateChecksum();
	}

	bool Contains(void* pointer) const
	{
		return pointer >= base && pointer < limit;
	}

	size_t AvailableMemory() const
	{
		size_t retval = 0;

		for(AllocationBlock* block = base; block != NULL; block = block->next)
		{
			block->VerifyBlock();

			if(!block->used)
				retval += block->size;
		}

		return retval;
	}

	void PrintMemoryMap() const
	{
		for(AllocationBlock* block = base; block != NULL; block = block->next)
		{
			printk("    Block at %p [ used = %d, prev = %p, next = %p, size = %u ]\n",
					block, block->used, block->prev, block->next, block->size);
			block->VerifyBlock();
		}
	}
};

int Memory::ModuleCount;
Module* Memory::Modules;

void Memory::Initialize(multiboot_info* info)
{
	if(info->flags & MBI_MEMORY == 0)
		System::Panic("No memory information available from boot loader.");

	if(info->flags & MBI_MODULES != 0)
	{
		ModuleCount = info->mods_count;
		Modules = (Module*) info->modules;
	}
	else
	{
		ModuleCount = 0;
		Modules = NULL;
	}

	LowMemoryAllocator::Initialize(info->mem_lower);

	HighMemoryAllocator::Initialize(info);

	printk("\n");
	printk("Total available memory is %uK (High) + %uK (Low)\n", 
			HighMemoryAllocator::TotalSize / 1024,
			LowMemoryAllocator::AvailableMemory / 1024);
	printk("\n");
}

char* LowMemoryAllocator::last;
char* LowMemoryAllocator::limit;
size_t LowMemoryAllocator::TotalSize;
size_t LowMemoryAllocator::AvailableMemory;

void LowMemoryAllocator::Initialize(size_t size)
{
	if(size < 64)
		System::Panic("Less than 64K lower memory available.");

	printk("Using %dK low memory\n", size - RESERVED_LOWMEM / 1024);

	size *= 1024;

	last = (char*) RESERVED_LOWMEM;	// We reserve lowest 16K for emergency use
	limit = (char*) size;
	
	TotalSize = AvailableMemory = size - RESERVED_LOWMEM;
}

void* LowMemoryAllocator::Allocate(size_t size)
{
	if(last + size >= limit)
		return NULL;

	void* retval = last;

	last += size;
	AvailableMemory -= size;

	return retval;
}

extern int __image_begin;
extern int __image_end;

void* HighMemoryAllocator::KernelStart = &__image_begin;
void* HighMemoryAllocator::KernelEnd = &__image_end;

void HighMemoryAllocator::Initialize(multiboot_info* info)
{
	printk("Initializing upper memory:\n");
	printk("  Kernel image from %p to %p\n", KernelStart, KernelEnd);

	for(int i = 0; i < Memory::ModuleCount; i++)
	{
		printk("  Module '%s' from %p to %p\n",
				Memory::Modules[i].String,
				Memory::Modules[i].Start,
				Memory::Modules[i].End);

		// Enlarge kernel image to include modules
		if(Memory::Modules[i].Start < KernelStart)
			KernelStart = Memory::Modules[i].Start;

		if(Memory::Modules[i].End > KernelEnd)
			KernelEnd = Memory::Modules[i].End;
	}

	// Enlarge the image to include all the page (4K) boundary
	KernelStart = (void*) (((size_t) KernelStart / 4096) * 4096);
	KernelEnd = (void*) (((size_t) KernelEnd / 4096 + 1) * 4096);

	if(Memory::ModuleCount != 0)
		printk("  Combined image from %p to %p\n", KernelStart, KernelEnd);

	if(info->flags && MBI_MEMMAP)
	{
		memory_map* map;

		for(size_t base = info->mmap_addr;
				base < info->mmap_addr + info->mmap_length;
				base += map->size + sizeof(size_t))
		{
			map = (memory_map*) base;

			// Available block below 4GB
			if(!map->base_addr_high && map->type == 1)
			{
				unsigned long long length = map->length_low;

				if(map->length_high)
					length = FOUR_GB_LIMIT;

				unsigned long long limit = map->base_addr_low + length;

				if(limit > FOUR_GB_LIMIT)
					limit = FOUR_GB_LIMIT;
				
				RegisterBlock((void*) map->base_addr_low, (void*) limit);
			}
		}
	}

	TotalSize = AvailableMemory();
}

MemoryBlock* memory_list;

size_t HighMemoryAllocator::TotalSize;

size_t HighMemoryAllocator::AvailableMemory()
{
	size_t retval = 0;

	for(MemoryBlock* allocator = memory_list; allocator != NULL; allocator = allocator->next)
		retval += allocator->AvailableMemory();

	return retval;
}

void HighMemoryAllocator::RegisterBlock(void* block_start, void* block_end)
{
	if(block_start < (void*) 0x100000)
		block_start = (void*) 0x100000;

	if(block_start >= KernelStart && block_start < KernelEnd)
		block_start = KernelEnd;

	if(block_end >= KernelStart && block_end < KernelEnd)
		block_end = KernelStart;

	// Skip lower memory and kernel areas
	if(block_start >= block_end)
		return;

	MemoryBlock* new_block = new MemoryBlock(block_start,
			(size_t)block_end - (size_t)block_start);

	new_block->next = memory_list;
	memory_list = new_block;
}

void* HighMemoryAllocator::Allocate(size_t size)
{
	for(MemoryBlock* allocator = memory_list; allocator != NULL; allocator = allocator->next)
	{
		void* retval = allocator->Allocate(size);
		if(retval != NULL)
			return retval;
	}

	return NULL;
}

void HighMemoryAllocator::Free(void* pointer)
{
	if(pointer == NULL)
		return;

	for(MemoryBlock* allocator = memory_list; allocator != NULL; allocator = allocator->next)
		if(allocator->Contains(pointer))
		{
			allocator->Free(pointer);
			return;
		}
}

void HighMemoryAllocator::PrintMemoryMap()
{
	for(MemoryBlock* allocator = memory_list; allocator != NULL; allocator = allocator->next)
	{
		printk("  Allocation group at %p:\n", allocator);
		allocator->PrintMemoryMap();
	}
}

extern "C" void* kalloc(size_t size)
{
	return HighMemoryAllocator::Allocate(size);
}

extern "C" void kfree(void* pointer)
{
	HighMemoryAllocator::Free(pointer);
}
