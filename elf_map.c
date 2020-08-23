#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<elf.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdint.h>

void elf_header(Elf64_Ehdr **ehdr)
{
	int i=0;

	/*magic number see what type of file(ELF)*/
	while(i<4) 
	{
		printf("%c",(*ehdr)->e_ident[i]);

		if(i==3)
			printf("\n");

		i++;
	}

	/*class/File architecture*/
	if((*ehdr)->e_ident[EI_CLASS]==ELFCLASSNONE)
	{
		printf("invalid class/Architecture");
	}
	else if((*ehdr)->e_ident[EI_CLASS]==ELFCLASS32)
	{
		printf("32 bit\n");
	}
	else if((*ehdr)->e_ident[EI_CLASS]==ELFCLASS64)
	{
		printf("64 bit\n");
	}

	/*data encoding of the file*/
	if((*ehdr)->e_ident[EI_DATA]==ELFDATANONE)
	{
		printf("unknown data format\n");
	}
	else if((*ehdr)->e_ident[EI_DATA]==ELFDATA2LSB)
	{
		printf("Two's compliment, little-endian\n");
	}
	else if((*ehdr)->e_ident[EI_DATA]==ELFDATA2MSB)
	{
		printf("Two's compliment, big-endian\n");
	}

	/*ELF specification number*/
	if((*ehdr)->e_ident[EI_VERSION]==EV_NONE)
	{
		printf("Invalid version\n");
	}
	else if((*ehdr)->e_ident[EI_VERSION]==EV_CURRENT)
	{
		printf("Current Version\n");
	}

	/*OS and ABI file is designed for*/
	if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_SYSV)
	{
		printf("UNIX System V ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_HPUX)
	{
		printf("HP_UX ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_NETBSD)
	{
		printf("NetBSD ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_LINUX)
	{
		printf("Linux ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_SOLARIS)
	{
		printf("Solaris ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_IRIX)
	{
		printf("IRIX ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_FREEBSD)
	{
		printf("FreeBSD ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_TRU64)
	{
		printf("TRU64 UNIX ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_ARM)
	{
		printf("ARM architecture ABI\n");
	}
	else if((*ehdr)->e_ident[EI_OSABI]==ELFOSABI_STANDALONE)
	{
		printf("Stand-alone (embedded) ABI\n");
	}

	/*ABI Version*/
	printf("ABI Version:%d\n",(*ehdr)->e_ident[EI_ABIVERSION]);

	/*File type*/
	switch((*ehdr)->e_type)
	{
		case ET_NONE:
			printf("File type: Unknown\n");
			break;
		case ET_REL:
			printf("File type: Relocatable\n");
			break;
		case ET_EXEC:
			printf("File type: Executable\n");
			break;
		case ET_DYN:
			printf("File type: shared object\n");
			break;
		case ET_CORE:
			printf("File type: Core\n");
			break;
	}

	/*architecture type for file*/
	switch((*ehdr)->e_machine)
	{
		case EM_NONE:
			printf("An unkown machine\n");
			break;
		case EM_M32:
			printf("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			printf("Sun Microsystems SPARC\n");
			break;
		case EM_386:
			printf("Intel 80386\n");
			break;
		case EM_68K:
			printf("Motorola 68000\n");
			break;
		case EM_88K:
			printf("Motorola 88000\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS RS3000 (big-endian only)\n");
			break;
		case EM_PARISC:
			printf("HP/PA\n");
			break;
		case EM_SPARC32PLUS:
			printf("SPARC with enchanced instruction set\n");
			break;
		case EM_PPC:
			printf("PowerPC\n");
			break;
		case EM_PPC64:
			printf("PowerPC 64-bit\n");
			break;
		case EM_S390:
			printf("IBM S/390\n");
			break;
		case EM_ARM:
			printf("Advanced RISC Machines\n");
			break;
		case EM_SH:
			printf("Renesas SuperH\n");
			break;
		case EM_SPARCV9:
			printf("SPARC V9 64-bit\n");
			break;
		case EM_IA_64:
			printf("Intel Itanium\n");
			break;
		case EM_X86_64:
			printf("AMD X86-64\n");
			break;
		case EM_VAX:
			printf("DEC Vax\n");
			break;
	}

	/*File version*/
	switch((*ehdr)->e_version)
	{
		case EV_NONE:
			printf("Invalid Version\n");
			break;
		case EV_CURRENT:
			printf("Current Version\n");
			break;
	}

	/*Program Entry point address,convert to hexadecimal...*/
	printf("Program Entry point(in Decimal format):%d\n",(*ehdr)->e_entry);

	/*Program header table file offset in bytes*/
	printf("Start of Program Headers:%d\n",(*ehdr)->e_phoff);

	/*Section Header table offset in bytes,convert both to hex in future*/
	printf("Start of Section Headers:%d\n",(*ehdr)->e_shoff);

	/*Processor specific flags associated with the file*/
	printf("Flags:%d\n",(*ehdr)->e_flags);

	/*Size of the ELF header(this header)*/
	printf("Size of this ELF header:%d bytes\n",(*ehdr)->e_ehsize);

	/*size of program header structs*/
	printf("Size of program headers:%d bytes\n",(*ehdr)->e_phentsize);
	
	/*number of entries in the program header table*/
	printf("Number of program headers:%d\n",(*ehdr)->e_phnum);

	/*size of section header structs*/
	printf("Size of section headers:%d bytes\n",(*ehdr)->e_shentsize);

	/*number of entries in the section header table*/
	printf("Number of section headers:%d\n",(*ehdr)->e_shnum);

	/*Section header string table index*/
	printf("Section header string table index:%d\n",(*ehdr)->e_shstrndx);	
}

void print_segment_info(Elf64_Phdr phdr)
{
	printf("File offset of segment:%d bytes\n",phdr.p_offset);
	printf("Virtual address offset of segment in memory:%d bytes\n",phdr.p_vaddr);
	printf("Physical address:%d bytes\n",phdr.p_paddr);
	printf("Segment size on hdd:%d\n",phdr.p_filesz);
	printf("Segment size in memory:%d\n",phdr.p_memsz);
	printf("Segment flags:%d\n",phdr.p_flags);
	printf("Segment allignment in memory:%d bytes\n",phdr.p_align);
	
}

void program_header(Elf64_Phdr *phdr,int no_segs)
{

	/*Segment (program header) type*/
	//printf("%d\n",(*phdr)[1]->p_type);
	//printf("%d\n",(*phdr+seg_size)->p_type);
	//printf("%d\n",(*phdr+(seg_size*5))->p_type);

	printf("Type=\n");
	printf("Flag reference: Write = %d\t Read = %d\t Executable = %d\n",PF_W,PF_R,PF_X);

	for(int i=0; i<=no_segs;i++)
	{
		switch (phdr[i].p_type)
		{
			case PT_LOAD:
				printf("LOAD______\n");
				/*printf("file offset of segment:%d bytes\n",phdr[i].p_offset);
				printf("virtual address offset of segment in memory:%d bytes\n",phdr[i].p_vaddr);
				printf("Physical address:%d bytes\n",phdr[i].p_paddr);
				printf("Segment size on hdd:%d bytes\n",phdr[i].p_filesz);
				printf("segment size in memory:%d bytes\n",phdr[i].p_memsz);
				printf("Segment flags:%d\n",phdr[i].p_flags);
				printf("segment allignment in memory:%d bytes\n",phdr[i].p_align);*/
				print_segment_info(phdr[i]);
				printf("___________\n");
				break;
			case PT_DYNAMIC:
				printf("DYNAMIC_____\n");
				/*printf("file offset of segment:%d bytes\n",phdr[i].p_offset);
				printf("Virtual address offset of segment in memory:%d bytes\n",phdr[i].p_vaddr);
				printf("Physical address:%d\n",phdr[i].p_paddr);
				printf("Segment size on hdd:%d bytes\n",phdr[i].p_filesz);
				printf("Segment size in memory:%d bytes\n",phdr[i].p_memsz);
				printf("Segment flags:%d\n",phdr[i].p_flags);
				printf("Segment allignment in memory:%d bytes\n",phdr[i].p_align);*/
				print_segment_info(phdr[i]);
				printf("____________\n");
				break;
			case PT_INTERP:
				printf("INTERP______\n");
				/*printf("File offset of segment:%d bytes\n",phdr[i].p_offset);
				printf("Virtual address offset of segment in memory:%d bytes\n",phdr[i].p_vaddr);
				printf("Physical address:%d bytes\n",phdr[i].p_paddr);
				printf("Segment size on hdd:%d bytes\n",phdr[i].p_filesz);
				printf("Segment size in memory:%d bytes\n",phdr[i].p_memsz);
				printf("Segment flags:%d\n",phdr[i].p_flags);
				printf("Segment allignment in memory:%d bytes\n",phdr[i].p_align);*/
				print_segment_info(phdr[i]);
				printf("____________\n");
				break;
			case PT_NOTE:
				printf("NOTE_______\n");
				print_segment_info(phdr[i]);
				printf("___________\n");
				break;
			case PT_PHDR:
				printf("PHDR_______\n\n");
				print_segment_info(phdr[i]);
				printf("___________\n");
				break;
			case PT_GNU_STACK:
				printf("GNU_STACK______\n");
				print_segment_info(phdr[i]);
				printf("______________\n");
				break;

		}
		
	}
}

void section_header(Elf64_Shdr *shdr,int no_segs,char *StringTable)
{
	for(int i=0;i<=no_segs;i++)
	{
	        printf("_______________________________________________\n");	
		printf("section name=%s\n",&StringTable[shdr[i].sh_name]);
		printf("section type=");
		switch(shdr[i].sh_type)
		{
			case SHT_NULL:
				printf("NULL\n");
				break;
			case SHT_PROGBITS:
				printf("PROGBITS\n");
				break;
			case SHT_SYMTAB:
				printf("SYMTAB\n");
				break;
			case SHT_STRTAB:
				printf("STRTAB\n");
				break;
			case SHT_RELA:
				printf("RELA\n");
				break;
			case SHT_HASH:
				printf("HASH\n");
				break;
			case SHT_DYNAMIC:
				printf("DYNAMIC\n");
				break;
			case SHT_NOTE:
				printf("NOTE\n");
				break;
			case SHT_NOBITS:
				printf("NOBITS\n");
				break;
			case SHT_REL:
				printf("REL\n");
				break;
			case SHT_SHLIB:
				printf("SHLIB\n");
				break;
			case SHT_DYNSYM:
				printf("DYNSYM\n");
				break;
			case SHT_LOPROC:
				printf("LOPROC\n");
				break;
			case SHT_HIPROC:
				printf("HIPROC\n");
				break;
			case SHT_LOUSER:
				printf("LOUSER\n");
				break;
			case SHT_HIUSER:
				printf("HIUSER\n");
				break;

		}
		printf("Flags:%d\n",shdr[i].sh_flags);
		printf("Section address:%d bytes\n",shdr[i].sh_addr);
		printf("Section offset:%d bytes\n",shdr[i].sh_offset);
		printf("Section size:%d bytes\n",shdr[i].sh_size);
		printf("Section link:%d\n",shdr[i].sh_link);
		printf("Section info:%d\n",shdr[i].sh_info);
		printf("Section address alignment:%d\n",shdr[i].sh_addralign);
		printf("Size of table entries within section(if section contains table):%d\n",shdr[i].sh_entsize);

	}
}

int main(int argc,char **argv)
{
	int fd,i;
	uint8_t *mem;
	struct stat st;
	char *StringTable,*interp;

	/*hold the elf header struct, the roadmap of the file*/
	Elf64_Ehdr *ehdr;

	/*the Elf program header struct, to then access all the program header information for each
	 * segment*/
	Elf64_Phdr *phdr;

	/*the section header struct, to then access all the sectioon header information for each section
	 * within each segment*/
	Elf64_Shdr *shdr;

	/*open and map the file into memory to inspect*/
	if(argc<2)
	{
		printf("Usage:%s <executable>\n",argv[0]);
		exit(0);
	}
	if((fd = open(argv[1],O_RDONLY))<0)
	{
		perror("open():");
		exit(-1);
	}
	if(fstat(fd,&st)<0)
	{
		perror("fstat");
		exit(-1);
	}

	/*mapping the file into memory*/
	mem = mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if(mem==MAP_FAILED)
	{
		perror("mmap");
		exit(-1);
	}

	/*the elf header struct is at the first memory address index of the file, so we have our pointer
	 * point to that memory location , and set the pointer to type ehdr struct, as that's the data at
	 * that memory address*/
	ehdr = (Elf64_Ehdr *)mem;

	/*get the memory locations ofthe section header table offset and program header offset*/
	phdr = (Elf64_Phdr *)&mem[ehdr->e_phoff];
	shdr = (Elf64_Shdr *)&mem[ehdr->e_shoff];


	/*check the first bytes for what file is it etc.*/
//	printf("%s\n",ehdr->e_ident[EI_MAG1]);
//	elf_header(&ehdr);
//	program_header(phdr,ehdr->e_phnum);

	
	//need to set Stringtable so we can find out the names of the sections
	StringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];
	section_header(shdr,ehdr->e_shnum,StringTable);
}
