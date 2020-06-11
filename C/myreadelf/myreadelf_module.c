#include "myreadelf_module.h"
//
//----------
char* get_elf_class(int ei_class ){
    char* es_class=malloc(sizeof(char)*10);
    es_class[0]='\0';
    switch (ei_class) {
        case ELFCLASSNONE:
        strcat(es_class,"Invalid");
        return es_class;
        break;
	
        case ELFCLASS32:
        strcat(es_class,"ELF32");
        return es_class;
        break;

        case ELFCLASS64:
        strcat(es_class,"ELF64");
        return es_class;
        break;

        default:
        strcat(es_class," ");
        return es_class;
        break;
    }
}
//
char* get_elf_data_encoding (int ei_encoding){
    switch (ei_encoding){
    case ELFDATANONE: return "aucun";
    case ELFDATA2LSB: return "complément à 2, système à octets de poids faible d'abord (little endian)";
    case ELFDATA2MSB: return "complément à 2, système à octets de poids fort d'abord (big endian)";
    default:          return "Inconnu";
    }
}
//
char* get_elf_version(int ei_version){
    switch(ei_version){
        case EV_CURRENT: return "(current)";
        case EV_NONE:    return "";
        default:         return "Inconnu";
    }
}
//
char* get_elf_os_abi(int ei_os_abi){
    switch (ei_os_abi){
    case ELFOSABI_NONE:		return "UNIX - System V";
    case ELFOSABI_HPUX:		return "UNIX - HP-UX";
    case ELFOSABI_NETBSD:	return "UNIX - NetBSD";
    case ELFOSABI_GNU:		return "UNIX - GNU";
    case ELFOSABI_SOLARIS:	return "UNIX - Solaris";
    case ELFOSABI_AIX:		return "UNIX - AIX";
    case ELFOSABI_IRIX:		return "UNIX - IRIX";
    case ELFOSABI_FREEBSD:	return "UNIX - FreeBSD";
    case ELFOSABI_TRU64:	return "UNIX - TRU64";
    case ELFOSABI_MODESTO:	return "Novell - Modesto";
    case ELFOSABI_OPENBSD:	return "UNIX - OpenBSD";
    default:                return "Inconnu";
    }
}
//
char* get_elf_type(int e_type){
    switch (e_type){
    case ET_NONE:	return "NONE (Aucun)";
    case ET_REL:	return "REL (Fichier de réadressage)";
    case ET_EXEC:	return "EXEC (Fichier exécutable)";
    case ET_DYN:	return "DYN (Fichier objet partagé)";
    case ET_CORE:	return "CORE (Fichier principal)";
    default:        return "Inconnu";
    }
}
//
char* get_elf_machine(int e_machine){
    switch (e_machine){
    case EM_NONE:		return "None";
    case EM_AARCH64:	return "AArch64";
    case EM_M32:		return "WE32100";
    case EM_SPARC:		return "Sparc";
    case EM_386:		return "Intel 80386";
    case EM_68K:		return "MC68000";
    case EM_88K:		return "MC88000";
    case EM_860:		return "Intel 80860";
    case EM_MIPS:		return "MIPS R3000";
    case EM_S370:		return "IBM System/370";
    case EM_MIPS_RS3_LE:return "MIPS R4000 big-endian";
    case EM_PARISC:		return "HPPA";
    case EM_SPARC32PLUS:return "Sparc v8+" ;
    case EM_960:		return "Intel 90860";
    case EM_PPC:		return "PowerPC";
    case EM_PPC64:		return "PowerPC64";
    case EM_FR20:		return "Fujitsu FR20";
    case EM_RH32:		return "TRW RH32";
    case EM_ARM:		return "ARM";
    case EM_SH:			return "Renesas / SuperH SH";
    case EM_SPARCV9:	return "Sparc v9";
    case EM_TRICORE:	return "Siemens Tricore";
    case EM_ARC:		return "ARC";
    case EM_H8_300:		return "Renesas H8/300";
    case EM_H8_300H:	return "Renesas H8/300H";
    case EM_H8S:		return "Renesas H8S";
    case EM_H8_500:		return "Renesas H8/500";
    case EM_IA_64:		return "Intel IA-64";
    case EM_MIPS_X:		return "Stanford MIPS-X";
    case EM_COLDFIRE:	return "Motorola Coldfire";
    case EM_ALPHA:		return "Alpha";
    case EM_D10V:		return "d10v";
    case EM_D30V:		return "d30v";
    case EM_M32R:		return "Renesas M32R (formerly Mitsubishi M32r)";
    case EM_V800:		return "Renesas V850 (using RH850 ABI)";
    case EM_V850:		return "Renesas V850";
    case EM_MN10300:	return "mn10300";
    case EM_MN10200:	return "mn10200";
    case EM_FR30:		return "Fujitsu FR30";
    case EM_PJ:			return "picoJava";
    case EM_MMA:		return "Fujitsu Multimedia Accelerator";
    case EM_PCP:		return "Siemens PCP";
    case EM_NCPU:		return "Sony nCPU embedded RISC processor";
    case EM_NDR1:		return "Denso NDR1 microprocesspr";
    case EM_STARCORE:	return "Motorola Star*Core processor";
    case EM_ME16:		return "Toyota ME16 processor";
    case EM_ST100:		return "STMicroelectronics ST100 processor";
    case EM_TINYJ:		return "Advanced Logic Corp. TinyJ embedded processor";
    case EM_PDSP:		return "Sony DSP processor";
    case EM_FX66:		return "Siemens FX66 microcontroller";
    case EM_ST9PLUS:	return "STMicroelectronics ST9+ 8/16 bit microcontroller";
    case EM_ST7:		return "STMicroelectronics ST7 8-bit microcontroller";
    case EM_68HC16:		return "Motorola MC68HC16 Microcontroller";
    case EM_68HC12:		return "Motorola MC68HC12 Microcontroller";
    case EM_68HC11:		return "Motorola MC68HC11 Microcontroller";
    case EM_68HC08:		return "Motorola MC68HC08 Microcontroller";
    case EM_68HC05:		return "Motorola MC68HC05 Microcontroller";
    case EM_SVX:		return "Silicon Graphics SVx";
    case EM_ST19:		return "STMicroelectronics ST19 8-bit microcontroller";
    case EM_VAX:		return "Digital VAX";
    case EM_AVR:		return "Atmel AVR 8-bit microcontroller";
    case EM_CRIS:		return "Axis Communications 32-bit embedded processor";
    case EM_JAVELIN:	return "Infineon Technologies 32-bit embedded cpu";
    case EM_FIREPATH:	return "Element 14 64-bit DSP processor";
    case EM_ZSP:		return "LSI Logic's 16-bit DSP processor";
    case EM_MMIX:		return "Donald Knuth's educational 64-bit processor";
    case EM_HUANY:		return "Harvard Universitys's machine-independent object format";
    case EM_PRISM:		return "Vitesse Prism";
    case EM_X86_64:		return "Advanced Micro Devices X86-64";
    case EM_S390:		return "IBM S/390";
    case EM_XTENSA:		return "Tensilica Xtensa Processor";
    case EM_TILEPRO:	return "Tilera TILEPro multicore architecture family";
    case EM_TILEGX:		return "Tilera TILE-Gx multicore architecture family";
    default:            return "Inconnu";
    }
}
//
void read_elf_header(const char* elfFile) {
    
    
    sprintf(debug_str, "The elfFile is << %s >>\n", elfFile);
    debug_print(debug_str);


    /*
    unsigned char	e_ident[EI_NIDENT];	// Magic number and other info 
    Elf64_Half	e_type;			// Object file type 
    Elf64_Half	e_machine;		// Architecture 
    Elf64_Word	e_version;		// Object file version 
    Elf64_Addr	e_entry;		// Entry point virtual address 
    Elf64_Off	e_phoff;		// Program header table file offset 
    Elf64_Off	e_shoff;		// Section header table file offset 
    Elf64_Word	e_flags;		// Processor-specific flags 
    Elf64_Half	e_ehsize;		// ELF header size in bytes 
    Elf64_Half	e_phentsize;	// Program header table entry size 
    Elf64_Half	e_phnum;		// Program header table entry count 
    Elf64_Half	e_shentsize;    // Section header table entry size 
    Elf64_Half	e_shnum;		// Section header table entry count 
    Elf64_Half	e_shstrndx;		// Section header string table index 
    */
    FILE* file = fopen(elfFile, "rb");
    //
    if(file) {
        //
        char buff[EI_CLASS+1];
        int count = fread(&buff, 1, (EI_CLASS+1)*sizeof(char), file);
        if(count!=(EI_CLASS+1)*sizeof(char)){exit(-1);}
        int iec = (int) buff[EI_CLASS];
        char* elf_class = get_elf_class(iec);

        //
        if( 0 == memcmp(elf_class,"ELF64",5) ){
            #ifdef DEBUG
            printf("(DEBUG) Classe: ELF64\n");
            #endif
            fclose(file);
            file = fopen(elfFile, "rb");
            Elf64_Ehdr hdr;
            count = fread(&hdr, 1, sizeof(hdr), file);
            if(count!=sizeof(hdr)){exit(-1);}
            read_elf_header_64(hdr);
        }else if( 0 == memcmp(elf_class,"ELF32",5) ){
            #ifdef DEBUG
            printf("(DEBUG) Classe: ELF32\n");
            #endif
            fclose(file);
            file = fopen(elfFile, "rb");
            Elf32_Ehdr hdr;
            count = fread(&hdr, 1, sizeof(hdr), file);
            if(count!=sizeof(hdr)){exit(-1);}
            read_elf_header_32(hdr);
        }else{
            fclose(file);
            exit(-1);
        }
        fclose(file);
    }else{
        printf("File does not exist\n");
        fclose(file);
        exit(-1);
    }
}
//
void read_elf_header_64(Elf64_Ehdr header){

        // check so its really an elf file
        if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
        // this is a valid elf file
        printf("En-tête ELF:\n");
        printf("  Magique: ");
        for(int i=0;i<EI_NIDENT;i++){printf("%02x ",header.e_ident[i]);}
        }
        printf("\n");
        int ei_class = header.e_ident[EI_CLASS];
        printf("  Classe:                            %s", get_elf_class(ei_class));
        printf("\n");
        int ei_data = header.e_ident[EI_DATA];
        printf("  Données:                           %s", get_elf_data_encoding(ei_data));
        printf("\n");
        int ei_version = header.e_ident[EI_VERSION];
        printf("  Version:                           %d %s", ei_version, get_elf_version(ei_version));
        printf("\n");
        printf("  OS/ABI:                            %s", get_elf_os_abi(header.e_ident[EI_OSABI]));
        printf("\n");
        printf("  Version ABI:                       %d", header.e_ident[EI_ABIVERSION]);
        printf("\n");
        printf("  Type:                              %s", get_elf_type(header.e_type));
        printf("\n");
        printf("  Machine:                           %s", get_elf_machine(header.e_machine));
        printf("\n");
        printf("  Version:                           0x%lx", (long unsigned int) header.e_version);
        printf("\n");
        printf("  Adresse du point d'entrée:         0x%lx", (long unsigned int) header.e_entry);
        printf("\n");
        printf("  Début des en-têtes de programme :  %d", (int) header.e_phoff);
        printf(" (octets dans le fichier)");
        printf("\n");
        printf("  Début des en-têtes de section :    %d", (int) header.e_shoff);
        printf(" (octets dans le fichier)");
        printf("\n");
        printf("  Fanions:                           0x%lx", (unsigned long) header.e_flags);
        printf("\n");
        printf("  Taille de cet en-tête:             %ld (octets)",(long) header.e_ehsize);
	    printf("\n"); 
        printf("  Taille de l'en-tête du programme:  %ld (octets)", (long) header.e_phentsize);
        printf("\n");
        printf("  Nombre d'en-tête du programme:     %ld", (long) header.e_phnum);
        printf("\n");
        printf("  Taille des en-têtes de section:    %ld (octets)", (long) header.e_shentsize);
        printf("\n");
        printf("  Nombre d'en-têtes de section:      %ld", (long) header.e_shnum);
        printf("\n");
        printf("  Table d'indexes des chaînes d'en-tête de section: %ld", (long) header.e_shstrndx);
        printf("\n\n");
        //
}
//
void read_elf_header_32(Elf32_Ehdr header){

        // check so its really an elf file
        if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
        // this is a valid elf file
        printf("En-tête ELF:\n");
        printf("  Magique: ");
        for(int i=0;i<EI_NIDENT;i++){printf("%02x ",header.e_ident[i]);}
        }
        printf("\n");
        int ei_class = header.e_ident[EI_CLASS];
        printf("  Classe:                            %s", get_elf_class(ei_class));
        printf("\n");
        int ei_data = header.e_ident[EI_DATA];
        printf("  Données:                           %s", get_elf_data_encoding(ei_data));
        printf("\n");
        int ei_version = header.e_ident[EI_VERSION];
        printf("  Version:                           %d %s", ei_version, get_elf_version(ei_version));
        printf("\n");
        printf("  OS/ABI:                            %s", get_elf_os_abi(header.e_ident[EI_OSABI]));
        printf("\n");
        printf("  Version ABI:                       %d", header.e_ident[EI_ABIVERSION]);
        printf("\n");
        printf("  Type:                              %s", get_elf_type(header.e_type));
        printf("\n");
        printf("  Machine:                           %s", get_elf_machine(header.e_machine));
        printf("\n");
        printf("  Version:                           0x%lx", (long unsigned int) header.e_version);
        printf("\n");
        printf("  Adresse du point d'entrée:         0x%lx", (long unsigned int) header.e_entry);
        printf("\n");
        printf("  Début des en-têtes de programme :  %d", (int) header.e_phoff);
        printf(" (octets dans le fichier)");
        printf("\n");
        printf("  Début des en-têtes de section :    %d", (int) header.e_shoff);
        printf(" (octets dans le fichier)");
        printf("\n");
        printf("  Fanions:                           0x%lx", (unsigned long) header.e_flags);
        printf("\n");
        printf("  Taille de cet en-tête:             %ld (octets)",(long) header.e_ehsize);
	    printf("\n"); 
        printf("  Taille de l'en-tête du programme:  %ld (octets)", (long) header.e_phentsize);
        printf("\n");
        printf("  Nombre d'en-tête du programme:     %ld", (long) header.e_phnum);
        printf("\n");
        printf("  Taille des en-têtes de section:    %ld (octets)", (long) header.e_shentsize);
        printf("\n");
        printf("  Nombre d'en-têtes de section:      %ld", (long) header.e_shnum);
        printf("\n");
        printf("  Table d'indexes des chaînes d'en-tête de section: %ld", (long) header.e_shstrndx);
        printf("\n\n");
        //
}
//
void read_elf_section( char* elfFile, char* section ){
    sprintf(debug_str, "(DEBUG) read_elf_section(%s, %s)\n",elfFile,section);
    debug_print(debug_str);

    FILE* file = fopen(elfFile, "rb");
    //
    if(file) {
        //
        char buff[EI_CLASS+1];
        int count = fread(&buff, 1, (EI_CLASS+1)*sizeof(char), file);
        if(count!=(EI_CLASS+1)*sizeof(char)){exit(-1);}
        int iec = (int) buff[EI_CLASS];
        char* elf_class = get_elf_class(iec);

        //
        if( 0 == memcmp(elf_class,"ELF64",5) ){
            
            debug_print("(DEBUG) Classe: ELF64\n");
            //fclose(file);

            //file = fopen(elfFile, "rb");
            rewind(file);

            Elf64_Ehdr hdr;
            count = fread(&hdr, 1, sizeof(hdr), file);
            if(count!=sizeof(hdr)){exit(-1);}

            //positionnement à la table des header de section
            fseek(file, hdr.e_shoff, SEEK_SET);

            // lecture de tout les headers de section
            Elf64_Shdr shdr[hdr.e_shnum];
            count = fread(&shdr, hdr.e_shnum, sizeof(Elf64_Shdr), file);
            if(count!=sizeof(Elf64_Shdr)){exit(-1);}

            // cherchons la section .rodata
            // pour cela, on cherche la string ".rodata" dans la section name.
            // La position relative de cette string nous permettra de trouver
            // la ligne correspondant à cette section dans la table des headers
            // et ainsi nous permettra d'avoir accès à l'offset de la section.
            // 
            // Le header de la section name est à la ligne  hdr.e_shstrndx
            // La chaine de caractères des noms de section est donc à l'offset
            //--> names_offset = shdr[hdr.e_shstrndx].sh_offset ;
            //En scannant cette chaine et en repérant la position pos de ".rodata"
            // on détermine rodata_sh_name = names_offset - pos
            // ensuite, on cherche la ligne i de shdr[i] 
            // telle que shdr[i].sh_name==rodata_sh_name
            // Cette ligne i_rodata nous permet d'accéder à shdr[i_rodata].sh_offset
            // qui est l'offset de la section .rodata

            // positionnement à la section des noms
            int idx = hdr.e_shstrndx;
            int offset = shdr[idx].sh_offset;
            fseek(file, offset, SEEK_SET);

            // lecture des noms
            char str_name[shdr[idx].sh_size];
                        
            count = fread(&str_name, 1, shdr[idx].sh_size, file);
            int section_pos = find_section_name(str_name,shdr[idx].sh_size,section,strlen(section));
            if(section_pos == -1){
                printf("Section %s does not exist !\n",section);
                return;
            }else{

                sprintf(debug_str,"(DEBUG) position of section %s is %d\n",section,section_pos);
                debug_print(debug_str);
                for(int i = 0;i<shdr[idx].sh_size;i++){
                    if(i==section_pos){
                        sprintf(debug_str, "(DEBUG) %d %c  <====\n",i,str_name[i]);
                        debug_print(debug_str);
                    }else{
                        sprintf(debug_str, "(DEBUG) %d %c\n",i,str_name[i]);
                        debug_print(debug_str);
                    }
                }
                debug_print("\n");

                // On a la section_pos. On cherche le header dont shdr[i].sh_name
                // vaut section_pos.
                idx = 0;
                while(shdr[idx].sh_name!=section_pos){idx++;}
                int section_idx = idx;
                int section_offset = shdr[section_idx].sh_offset;
                int section_size   = shdr[section_idx].sh_size;
                int section_addr   = shdr[section_idx].sh_addr;

                fseek(file, section_offset, SEEK_SET);
                char section_block[section_size];
                count = fread(&section_block, 1, section_size, file);

                
                for(int i = 0 ; i<(double)section_size/(double)16 ; i++){
                    printf("0x%08x",section_addr+16*i);
                    for(int j = 0 ; j < 4 ; j++){
                        printf(" ");
                        for(int k = 0 ; k<4 ; k++){
                        printf("%02x",section_block[i*16+j*4+k]);
                        }
                    }
                    printf(" ");
                    for(int j = 0 ; j<16 ; j++){
                        printf("%c",section_block[i*16+j]);
                    }
                    printf("\n");
                }
            }
        //
        }else if( 0 == memcmp(elf_class,"ELF32",5) ){
            
            debug_print("(DEBUG) Classe: ELF32\n");
            
            //
            //fclose(file);

            //file = fopen(elfFile, "rb");
            rewind(file);

            Elf32_Ehdr hdr;
            count = fread(&hdr, 1, sizeof(hdr), file);
            if(count!=sizeof(hdr)){exit(-1);}

            //positionnement à la table des header de section
            fseek(file, hdr.e_shoff, SEEK_SET);

            // lecture de tout les headers de section
            Elf32_Shdr shdr[hdr.e_shnum];
            count = fread(&shdr, hdr.e_shnum, sizeof(Elf32_Shdr), file);
            if(count!=sizeof(Elf32_Shdr)){exit(-1);}

            // cherchons la section .rodata
            // pour cela, on cherche la string ".rodata" dans la section name.
            // La position relative de cette string nous permettra de trouver
            // la ligne correspondant à cette section dans la table des headers
            // et ainsi nous permettra d'avoir accès à l'offset de la section.
            // 
            // Le header de la section name est à la ligne  hdr.e_shstrndx
            // La chaine de caractères des noms de section est donc à l'offset
            //--> names_offset = shdr[hdr.e_shstrndx].sh_offset ;
            //En scannant cette chaine et en repérant la position pos de ".rodata"
            // on détermine rodata_sh_name = names_offset - pos
            // ensuite, on cherche la ligne i de shdr[i] 
            // telle que shdr[i].sh_name==rodata_sh_name
            // Cette ligne i_rodata nous permet d'accéder à shdr[i_rodata].sh_offset
            // qui est l'offset de la section .rodata

            // positionnement à la section des noms
            int idx = hdr.e_shstrndx;
            int offset = shdr[idx].sh_offset;
            fseek(file, offset, SEEK_SET);

            // lecture des noms
            char str_name[shdr[idx].sh_size];
                        
            count = fread(&str_name, 1, shdr[idx].sh_size, file);
            int section_pos = find_section_name(str_name,shdr[idx].sh_size,section,strlen(section));
            if(section_pos == -1){
                printf("Section %s does not exist !\n",section);
                return;
            }else{

                sprintf(debug_str, "(DEBUG) position of section %s is %d\n",section,section_pos);
                debug_print(debug_str);
                for(int i = 0;i<shdr[idx].sh_size;i++){
                    if(i==section_pos){
                        sprintf(debug_str, "(DEBUG) %d %c  <====\n",i,str_name[i]);
                        debug_print(debug_str);
                    }else{
                        sprintf(debug_str, "(DEBUG) %d %c\n",i,str_name[i]);
                        debug_print(debug_str);
                    }
                }
                debug_print("\n");

                // On a la section_pos. On cherche le header dont shdr[i].sh_name
                // vaut section_pos.
                idx = 0;
                while(shdr[idx].sh_name!=section_pos){idx++;}
                int section_idx = idx;
                int section_offset = shdr[section_idx].sh_offset;
                int section_size   = shdr[section_idx].sh_size;
                int section_addr   = shdr[section_idx].sh_addr;

                fseek(file, section_offset, SEEK_SET);
                char section_block[section_size];
                count = fread(&section_block, 1, section_size, file);

                
                for(int i = 0 ; i<(double)section_size/(double)16 ; i++){
                    printf("0x%08x",section_addr+16*i);
                    for(int j = 0 ; j < 4 ; j++){
                        printf(" ");
                        for(int k = 0 ; k<4 ; k++){
                        printf("%02x",section_block[i*16+j*4+k]);
                        }
                    }
                    printf(" ");
                    for(int j = 0 ; j<16 ; j++){
                        printf("%c",section_block[i*16+j]);
                    }
                    printf("\n");
                }
            }
            //
        }else{
            fclose(file);
            exit(-1);
        }
        fclose(file);
    }else{
        printf("File does not exist\n");
        exit(-1);
    }
    //
}
//
int find_section_name(char*str_name,int l_name,char* section,int l_section) {
    for(int i = 0;i<l_name-l_section;i++){
        int j = 0;
        while(str_name[i+j]==section[j] && j<l_section){
            j++;
            if(j==l_section){return i;}
        }
    }
    return -1;
}