#ifndef __MULTIBOOT_H
#define __MULTIBOOT_H

typedef struct aout_symbol_table
{
	unsigned long tabsize;
	unsigned long strsize;
	void* addr;
	unsigned long reserved;
} aout_symbol_table_t;
     
/* The section header table for ELF. */
typedef struct elf_section_header_table
{
	unsigned long num;
	unsigned long size;
	void* addr;
	unsigned long shndx;
} elf_section_header_table_t;

typedef struct module
{
	unsigned long mod_start;
	unsigned long mod_end;
	char* string;
	unsigned long reserved;
};

typedef struct memory_map
{
	unsigned long size;
	unsigned long base_addr_low;
	unsigned long base_addr_high;
	unsigned long length_low;
	unsigned long length_high;
	unsigned long type;
};

#define MBI_MEMORY	0x01
#define MBI_BOOT_DEVICE	0x02
#define MBI_CMDLINE	0x04
#define MBI_MODULES	0x08
#define MBI_AOUT_TABLE	0x10
#define MBI_ELF_TABLE	0x20
#define MBI_MEMMAP	0x40

/* The Multiboot information.  */
typedef struct multiboot_info
{
	unsigned long flags;
	unsigned long mem_lower;
	unsigned long mem_upper;
	unsigned long boot_device;
	char* cmdline;
	unsigned long mods_count;
	module *modules;
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	unsigned long mmap_length;
	unsigned long mmap_addr;
};

#endif
