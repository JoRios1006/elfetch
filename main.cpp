#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "io_buffer.hpp"
#define LN out.append("\n");

using namespace std;
using Header = array<char, 64>;
auto read_elf_header(const char* ruta_archivo) -> Header{
  FILE* archivo = fopen(ruta_archivo, "rb");
  if (!archivo) return {};
  setvbuf(archivo, nullptr, _IONBF, 0);
  Header buffer{};
  fread(buffer.data(), 1, buffer.size(), archivo);
  fclose(archivo);
  return buffer;
}

using Elf64_Byte = uint8_t;
using Elf64_Half = uint16_t;
using Elf64_Word = uint32_t;
using Elf64_Addr = uint64_t;
using Elf64_Off = uint64_t;
enum ARCH : Elf64_Half { //NOLINT(performance-enum-size)
  I8038632 = 0x03,
  AMD866 = 0x3E,
  ARM32 = 0x28,
  ARM64 = 0xB7,
  RISCV = 0xF3,
  MIPS = 0x08,
  PowerPC = 0x14,
  PowerPC64 = 0x15,
};

enum class E_TYPE : Elf64_Half { //NOLINT(performance-enum-size)
  None = 0,
  Relocatable = 1,
  Executable = 2,
  SharedObject = 3,
  Core = 4
};

enum class E_OSABI : Elf64_Byte {
  NONE    = 0,
  HPUX    = 1,
  NETBSD  = 2,
  LINUX   = 3,
  SOLARIS = 6,
  AIX     = 7,
  IRIX    = 8,
  FREEBSD = 9,
  TRU64   = 10,
  MODESTO = 11,
  OPENBSD = 12,
  OPENVMS = 13,
  NSK     = 14,
};

#pragma pack(push, 1)
struct ElfHeader {
  Elf64_Byte      magic[4];       // Offsets 0x00-0x03 (4 bytes) // NOLINT(modernize-avoid-c-arrays)
  Elf64_Byte      ei_class;       // Offset  0x04      (1 byte)
  Elf64_Byte      ei_data;        // Offset  0x05      (1 byte)
  Elf64_Byte      ei_version;     // Offset  0x06      (1 byte)
  E_OSABI         ei_osabi;       // Offset  0x07      (1 byte)
  Elf64_Byte      ei_abiversion;  // Offset  0x08      (1 byte)
  Elf64_Byte      ei_pad[7];      // Offsets 0x09-0x0F (7 bytes) // NOLINT(modernize-avoid-c-arrays)
  E_TYPE          e_type;
  ARCH            e_machine;
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
inline auto checkArch(ARCH EMACHINE) -> string {
  switch (EMACHINE) {
  CASE(ARCH::I8038632, "Intel 80386 (x86 / 32-bit)")
  CASE(ARCH::AMD866, "AMD x86-64 (AMD64 / 64-bit)")
  CASE(ARCH::ARM32, "ARM (32-bit)")
  CASE(ARCH::ARM64, "ARM 64-bit (AArch64)")
  CASE(ARCH::RISCV, "RISC-V")
  CASE(ARCH::MIPS, "MIPS")
  CASE(ARCH::PowerPC, "PowerPC")    
  CASE(ARCH::PowerPC64, "PowerPC 64-bit")
  default: return "Reserved for future use";    
  }
}

inline auto checkType(E_TYPE TYPE) -> string {
  switch (TYPE) {
  CASE(E_TYPE::None, "NONE (Desconocido)")
  CASE(E_TYPE::Relocatable, "REL (Archivo Relocatable)")
  CASE(E_TYPE::Executable, "EXEC (Ejecutable)")
  CASE(E_TYPE::SharedObject, "DYN (Librería Compartida / PIE)")
  CASE(E_TYPE::Core, "CORE (Core Dump)")
  default: return "Desconocido / Específico del procesador";
  }
}

inline auto checkOSABI(E_OSABI OSABI) -> string {
  switch (OSABI) {
  CASE(E_OSABI::NONE, "No extensions or unspecified")
  CASE(E_OSABI::HPUX, "Hewlett-Packard HP-UX")
  CASE(E_OSABI::NETBSD, "NetBSD")
  CASE(E_OSABI::LINUX, "Linux")
  CASE(E_OSABI::SOLARIS, "Sun Solaris")
  CASE(E_OSABI::AIX, "AIX")
  CASE(E_OSABI::IRIX, "IRIX")
  CASE(E_OSABI::FREEBSD, "FreeBSD")  
  CASE(E_OSABI::TRU64, "Compaq TRU64 UNIX")
  CASE(E_OSABI::MODESTO, "Novell Modesto")
  CASE(E_OSABI::OPENBSD, "Open BSD")
  CASE(E_OSABI::OPENVMS, "Open VMS")
  CASE(E_OSABI::NSK, "Hewlett-Packard Non-Stop Kernel")
  default: return "Architecture-specific value range";
  }  
}

auto main(int argc, char *argv[]) -> int{
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
  out.append(checkType(elf_header.e_type)); LN
  out.flush();
  return 0;
}
