#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "io_buffer.hpp"
#define LN out.append("\n");

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
enum ARCH : Elf64_Half {
  I8038632 = 0x03,
  AMD866 = 0x3E,
  ARM32 = 0x28,
  ARM64 = 0xB7,
  RISCV = 0xF3,
  MIPS = 0x08,
  PowerPC = 0x14,
  PowerPC64 = 0x15,
};
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
        ARCH      e_machine;
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

#define CASE(x, y) case x: return y;
inline string checkArch(ARCH EMACHINE) {
  switch (EMACHINE) {
  CASE(I8038632, "Intel 80386 (x86 / 32-bit)")
  CASE(AMD866, "AMD x86-64 (AMD64 / 64-bit)")
  CASE(ARM32, "ARM (32-bit)")
  CASE(ARM64, "ARM 64-bit (AArch64)")
  CASE(RISCV, "RISC-V")
  CASE(MIPS, "MIPS")
  CASE(PowerPC, "PowerPC")    
  CASE(PowerPC64, "PowerPC 64-bit")
  default:
  return "Reserved for future use";    
}
}

int main(int argc, char *argv[]) {
   IOBuffer<4096> out;
   if (argc < 2) return 1;
   const string path = argv[1];
   out.append(path); LN
   Header header = read_elf_header(path.c_str());   
   out.append(header.size()); LN
   out.append(header.max_size()); LN
   ElfHeader elf_header;
   memcpy(&elf_header, header.data(), sizeof(ElfHeader));
   out.append((elf_header.magic[0] == 0x7F) ? "ELF" : "NOT ELF"); LN
   out.append(checkArch(elf_header.e_machine)); LN
   out.flush();
   return 0;
}
