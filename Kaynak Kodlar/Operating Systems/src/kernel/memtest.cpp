#include <memory.h>
#include <stdio.h>

#define POINTER_COUNT	100
#define MIN_SIZE	5
#define MAX_SIZE	18

size_t RandSize()
{
	static int last = MIN_SIZE;

	if(last > MAX_SIZE)
		last = MIN_SIZE;

	return (1 << last++) + 1;
}

void TestHighMemoryAllocator()
{
	unsigned char* pointers[POINTER_COUNT];
	int count = 0;

	printk(" >> Available Memory = %u\n", HighMemoryAllocator::AvailableMemory());
	printk("Allocating and clearing %d blocks: ", POINTER_COUNT);

	for(int i = 0; i < POINTER_COUNT; i++)
	{
		size_t size = RandSize();

		pointers[i] = (unsigned char*) HighMemoryAllocator::Allocate(size);

		if(pointers[i] == NULL)
			printk("X");
		else
		{
			for(size_t j = 0; j < size; j++)
				pointers[i][j] = (unsigned char) (i ^ j ^ size);

			count++;
			printk(".");
		}
	}

	printk("done.\n");
	printk(" >> Available Memory = %u\n", HighMemoryAllocator::AvailableMemory());
	printk("Freeing pointers: ");

	for(int i = 0; count; i = (i + 7) % POINTER_COUNT)
		if(pointers[i] != NULL)
		{
			HighMemoryAllocator::Free(pointers[i]);
			pointers[i] = NULL;

			count--;
		}

	printk("done.\n");
	printk(" >> Available Memory = %u\n", HighMemoryAllocator::AvailableMemory());

	HighMemoryAllocator::PrintMemoryMap();
}
