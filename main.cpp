#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "io_buffer.hpp"

using namespace std;
typedef array<char, 0x40> Header;
Header read_elf_header(const char* ruta_archivo) {
    FILE* archivo = fopen(ruta_archivo, "rb");
    if (!archivo) return {};
    setvbuf(archivo, nullptr, _IONBF, 0);
    Header buffer{};
    fread(buffer.data(), 1, buffer.size(), archivo);
    fclose(archivo);
    return buffer;
}
#define EI_NIDENT 16
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
#pragma pack(push, 1)
struct ElfHeader {
        uint8_t  magic[4];       // Offsets 0x00-0x03 (4 bytes)
        uint8_t  ei_class;       // Offset  0x04      (1 byte)
        uint8_t  ei_data;        // Offset  0x05      (1 byte)
        uint8_t  ei_version;     // Offset  0x06      (1 byte)
        uint8_t  ei_osabi;       // Offset  0x07      (1 byte)
        uint8_t  ei_abiversion;  // Offset  0x08      (1 byte)
        uint8_t  ei_pad[7];      // Offsets 0x09-0x0F (7 bytes)
        Elf64_Half      e_type;
        Elf64_Half      e_machine;
        Elf64_Word      e_version;
        Elf64_Addr      e_entry;
        Elf64_Off       e_phoff;
        Elf64_Off       e_shoff;
        Elf64_Word      e_flags;
        Elf64_Half      e_ehsize;
        Elf64_Half      e_phentsize;
        Elf64_Half      e_phnum;
        Elf64_Half      e_shentsize;
        Elf64_Half      e_shnum;
        Elf64_Half      e_shtrndx;
};
#pragma pack(pop)

int main(int argc, char *argv[]) {
   IOBuffer<4096> out;
   if (argc < 2) return 1;
   const string path = argv[1];
   out.append(path);
   Header header = read_elf_header(path.c_str());   
   out.append(header.size());
   out.append(header.max_size());
   ElfHeader elf_header;
   memcpy(&elf_header, header.data(), sizeof(ElfHeader));
   out.append((elf_header.magic[0] == 0x7F) ? "ELF" : "NOT ELF");
   out.append(elf_header.e_machine);
   out.flush();
   return 0;
}
