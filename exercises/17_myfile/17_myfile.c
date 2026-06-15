#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    case ET_NONE:
      type_str = "NONE";
      break;
    case ET_REL:
      type_str = "REL (Relocatable file)";
      break;
    case ET_EXEC:
      type_str = "EXEC (Executable file)";
      break;
    case ET_DYN:
      type_str = "DYN (Shared Object/PIE)";
      break;
    case ET_CORE:
      type_str = "CORE (Core file)";
      break;
    default:
      type_str = "UNKNOWN";
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  for (int i = 0; i < 2; i++) {
    fd = open(filepath[i], O_RDONLY);
    if (fd < 0) {
      printf("Cannot open file %s\n", filepath[i]);
      continue;
    }

    if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
      printf("Cannot read ELF header from %s\n", filepath[i]);
      close(fd);
      continue;
    }

    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || ehdr.e_ident[EI_MAG3] != ELFMAG3) {
      printf("%s is not a valid ELF file\n", filepath[i]);
      close(fd);
      continue;
    }

    printf("\n=== File: %s ===\n", filepath[i]);
    print_elf_type(ehdr.e_type);

    close(fd);
  }
  
  return 0;
}
