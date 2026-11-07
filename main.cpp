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
enum ARCH : Elf64_Half { // NOLINT(performance-enum-size)
NONE 	      = 0,	// No machine
M32 	      = 1,	// T&T WE 32100
SPARC 	      = 2,	// SPARC
I386 	      = 3,	// Intel 80386
M68K 	      = 4,	// Motorola 68000
M88K 	      = 5,	// Motorola 88000
RES6          = 6,  // Reserved for future use (was EM_486)
I860 	      = 7,	// Intel 80860
MIPS 	      = 8,	// MIPS I Architecture
S370          = 9,	// BM System/370 Processor
MIPS_RS3_LE   = 10, // MIPS RS3000 Little-endian
RES11         = 11,  // Reserved for future use
RES12         = 12,  // Reserved for future use
RES13         = 13,  // Reserved for future use
RES14         = 14,  // Reserved for future use
PARISC 	      = 15,	// Hewlett-Packard PA-RISC
RES16         = 16,  // Reserved for future use
VPP500 	      = 17,	// Fujitsu VPP500
SPARC32PLUS   = 18,	// Enhanced instruction set SPARC
I960 	      = 19,	// Intel 80960
PPC 	      = 20,	// PowerPC
PPC64 	      = 21,	// 64-bit PowerPC
S390 	      = 22,	// BM System/390 Processor
RES23         = 23,  // Reserved for future use
RES24         = 24,  // Reserved for future use
RES25         = 25,  // Reserved for future use
RES26         = 26,  // Reserved for future use
RES27         = 27,  // Reserved for future use
RES28         = 28,  // Reserved for future use
RES29         = 29,  // Reserved for future use
RES30         = 30,  // Reserved for future use
RES31         = 31,  // Reserved for future use
RES32         = 32,  // Reserved for future use
RES33         = 33,  // Reserved for future use
RES34         = 34,  // Reserved for future use
RES35         = 35,  // Reserved for future use
V800          = 36,	// NEC V800
FR20 	      = 37,	// Fujitsu FR20
RH32          = 38,	// TRW RH-32
RCE           = 39,	// Motorola RCE
ARM 	      = 40,	// Advanced RISC Machines ARM
ALPHA         = 41,	// Digital Alpha
SH 	          = 42,	// Hitachi SH
SPARCV9 	  = 43,	// PARC Version 9
TRICORE 	  = 44,	// Siemens TriCore embedded processor
ARC 	      = 45,	// Argonaut RISC Core, Argonaut Technologies Inc.
H8_300 	      = 46,	// Hitachi H8/300
H8_300H 	  = 47,	// Hitachi H8/300H
H8S 	      = 48,	// Hitachi H8S
H8_500 	      = 49,	// Hitachi H8/500
IA_64 	      = 50,	// Intel IA-64 processor architecture
MIPS_X 	      = 51,	// Stanford MIPS-X
COLDFIRE 	  = 52,	// Motorola ColdFire
M68HC12 	  = 53,	// Motorola M68HC12
MMA 	      = 54,	// Fujitsu MMA Multimedia Accelerator
PCP 	      = 55,	// Siemens PCP
NCPU 	      = 56,	// Sony nCPU embedded RISC processor
NDR1 	      = 57,	// Denso NDR1 microprocessor
STARCORE 	  = 58,	// Motorola Star*Core processor
ME16 	      = 59,	// Toyota ME16 processor
ST100 	      = 60,	// STMicroelectronics ST100 processor
TINYJ 	      = 61,	// Advanced Logic Corp. TinyJ embedded processor family
X86_64 	      = 62,	// AMD x86-64 architecture
PDSP 	      = 63,	// Sony DSP Processor
PDP10 	      = 64,	// Digital Equipment Corp. PDP-10
PDP11 	      = 65,	// Digital Equipment Corp. PDP-11
FX66 	      = 66,	// Siemens FX66 microcontroller
ST9PLUS 	  = 67,	// STMicroelectronics ST9+ 8/16 bit microcontroller
ST7 	      = 68,	// STMicroelectronics ST7 8-bit microcontroller
M8HC16        = 69,	// Motorola MC68HC16 Microcontroller
M68HC11 	  = 70,	// Motorola MC68HC11 Microcontroller
M68HC08 	  = 71,	// Motorola MC68HC08 Microcontroller
M68HC05 	  = 72,	// Motorola MC68HC05 Microcontroller
SVX 	      = 73,	// Silicon Graphics SVx
ST19 	      = 74,	// STMicroelectronics ST19 8-bit microcontroller
VAX 	      = 75,	// Digital VAX
CRIS 	      = 76,	// Axis Communications 32-bit embedded processor
JAVELIN 	  = 77,	// Infineon Technologies 32-bit embedded processor
FIREPATH 	  = 78,	// Element 14 64-bit DSP Processor
ZSP 	      = 79,	// LSI Logic 16-bit DSP Processor
MMIX 	      = 80,	// Donald Knuth's educational 64-bit processor
HUANY 	      = 81,	// Harvard University machine-independent object files
PRISM 	      = 82,	// SiTera Prism
AVR 	      = 83,	// Atmel AVR 8-bit microcontroller
FR30 	      = 84,	// Fujitsu FR30
D10V 	      = 85,	// Mitsubishi D10V
D30V 	      = 86,	// Mitsubishi D30V
V850 	      = 87,	// NEC v850
M32R 	      = 88,	// Mitsubishi M32R
MN10300 	  = 89,	// Matsushita MN10300
MN10200 	  = 90,	// Matsushita MN10200
PJ 	          = 91,	// picoJava
OPENRISC 	  = 92,	// OpenRISC 32-bit embedded processor
ARC_A5 	      = 93,	// ARC Cores Tangent-A5
XTENSA 	      = 94,	// Tensilica Xtensa Architecture
VIDEOCORE 	  = 95,	// Alphamosaic VideoCore processor
TMM_GPP 	  = 96,	// Thompson Multimedia General Purpose Processor
NS32K 	      = 97,	// National Semiconductor 32000 series
TPC 	      = 98,	// Tenor Network TPC processor
SNP1K 	      = 99,	// Trebia SNP 1000 processor
ST200 	      = 100,// STM ST200 microcontroller
  
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

enum class E_DATA : Elf64_Byte {
 NONE   = 0,
 TWOLSB = 1,
 TWOMSB = 2,  
};

#pragma pack(push, 1)
struct ElfHeader {
  Elf64_Byte      magic[4];       // Offsets 0x00-0x03 (4 bytes) // NOLINT(modernize-avoid-c-arrays)
  Elf64_Byte      ei_class;       // Offset  0x04      (1 byte)
  E_DATA          ei_data;        // Offset  0x05      (1 byte)
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

const string reserved = "Reserved for future use";
#define CASE(x, y) case x: return y;
inline auto checkArch(ARCH EMACHINE) -> string {
  switch (EMACHINE) {
  CASE(ARCH::NONE, "No machine")
  CASE(ARCH::M32, "T&T WE 32100")  
  CASE(ARCH::SPARC, "SPARC")
  CASE(ARCH::I386, "Intel 80386")
  CASE(ARCH::M68K, "Motorola 68000")
  CASE(ARCH::M88K, "Motorola 88000")
  CASE(ARCH::RES6, "Reserved for future use (was EM_486)") // RES
  CASE(ARCH::I860, "Intel 80860")
  CASE(ARCH::MIPS, "MIPS I Architecture")
  CASE(ARCH::S370, "BM System/370 Processor")
  CASE(ARCH::MIPS_RS3_LE, "MIPS RS3000 Little-endian")
  case ARCH::RES11:
  case ARCH::RES12:
  case ARCH::RES13:
  case ARCH::RES14:
    return "Reserved for future use";
  CASE(ARCH::PARISC, "Hewlett-Packard PA-RISC")
  CASE(ARCH::RES16, "Reserved for future use")
  CASE(ARCH::VPP500, "Fujitsu VPP500")
  CASE(ARCH::SPARC32PLUS, "Enhanced instruction set SPARC")
  CASE(ARCH::I960, "Intel 80960")
  CASE(ARCH::PPC, "PowerPC")
  CASE(ARCH::PPC64, "64-bit PowerPC")
  CASE(ARCH::S390, "BM System/390 Processor")
  case ARCH::RES23:
  case ARCH::RES24:
  case ARCH::RES25:
  case ARCH::RES26:
  case ARCH::RES27:
  case ARCH::RES28:
  case ARCH::RES29:
  case ARCH::RES30:
  case ARCH::RES31:
  case ARCH::RES32:
  case ARCH::RES33:
  case ARCH::RES34:
  case ARCH::RES35:
    return "Reserved for future use";
  CASE(ARCH::V800, "")
  CASE(ARCH::FR20, "")
  CASE(ARCH::RH32, "")
  CASE(ARCH::RCE, "")
  CASE(ARCH::ARM, "")
  CASE(ARCH::ALPHA, "")
  CASE(ARCH::SH, "")
  CASE(ARCH::SPARCV9, "")
  CASE(ARCH::TRICORE, "")
  CASE(ARCH::ARC, "")
  CASE(ARCH::H8_300, "")
  CASE(ARCH::H8_300H, "")
  CASE(ARCH::H8S, "")
  CASE(ARCH::H8_500, "")
  CASE(ARCH::IA_64, "")
  CASE(ARCH::MIPS_X, "")
  CASE(ARCH::COLDFIRE, "")
  CASE(ARCH::M68HC12, "")
  CASE(ARCH::MMA, "")
  CASE(ARCH::PCP, "")
  CASE(ARCH::NCPU, "")
  CASE(ARCH::NDR1, "")
  CASE(ARCH::STARCORE, "")
  CASE(ARCH::ME16, "")
  CASE(ARCH::ST100, "")
  CASE(ARCH::TINYJ, "")
  CASE(ARCH::X86_64, "")
  CASE(ARCH::PDSP, "")
  CASE(ARCH::PDP10, "")
  CASE(ARCH::PDP11, "")
  CASE(ARCH::FX66, "")
  CASE(ARCH::ST9PLUS, "")
  CASE(ARCH::ST7, "")
  CASE(ARCH::M8HC16, "")
  CASE(ARCH::M68HC11, "")
  CASE(ARCH::M68HC08, "")
  CASE(ARCH::M68HC05, "")
  CASE(ARCH::SVX, "")
  CASE(ARCH::ST19, "")
  CASE(ARCH::VAX, "")
  CASE(ARCH::CRIS, "")
  CASE(ARCH::JAVELIN, "")
  CASE(ARCH::FIREPATH, "")
  CASE(ARCH::ZSP, "")
  CASE(ARCH::MMIX, "")
  CASE(ARCH::HUANY, "")
  CASE(ARCH::PRISM, "")
  CASE(ARCH::AVR, "")
  CASE(ARCH::FR30, "")
  CASE(ARCH::D10V, "")
  CASE(ARCH::D30V, "")
  CASE(ARCH::V850, "")
  CASE(ARCH::M32R, "")
  CASE(ARCH::MN10300, "")
  CASE(ARCH::MN10200, "")
  CASE(ARCH::PJ, "")
  CASE(ARCH::OPENRISC, "")
  CASE(ARCH::ARC_A5, "")
  CASE(ARCH::XTENSA, "")
  CASE(ARCH::VIDEOCORE, "")
  CASE(ARCH::TMM_GPP, "")
  CASE(ARCH::NS32K, "")
  CASE(ARCH::TPC, "")
  CASE(ARCH::SNP1K, "")
  CASE(ARCH::ST200, "")
  // default: return "Reserved for future use";    
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

inline auto checkTwosComplement(E_DATA DATA) -> string {
  switch (DATA) {
  CASE(E_DATA::NONE, "Invalid data encoding")  
  CASE(E_DATA::TWOLSB, "little endian")
  CASE(E_DATA::TWOMSB, "big endian")
  default: return "Invalid format";  
  }
}
const string ascii_art[] = {// NOLINT(modernize-avoid-c-arrays)
  "\\     /\\     /",
  " \\. .'--`. .' ",
  "  \\\\|X X |//  ",
  "   \\|┌──┐|/   ",
  "    |└──┘|    ",
  "     ----     ",};


auto main(int argc, char *argv[]) -> int{
  IOBuffer<4096> out;
  if (argc < 2) return 1;
  const string path = argv[1];
  Header header = read_elf_header(path.c_str());   
  ElfHeader elf_header;
  memcpy(&elf_header, header.data(), sizeof(ElfHeader));
  bool is_elf = (elf_header.magic[0] == 0x7F && 
                 elf_header.magic[1] == 'E' && 
                 elf_header.magic[2] == 'L' && 
                 elf_header.magic[3] == 'F');

  if (!is_elf) {
    out.append("Error: El archivo no es un binario ELF válido.\n");
    out.flush();
    return 1;
  }
  string info_lines[] = { // NOLINT(modernize-avoid-c-arrays)
    "Target:  " + path,
    "Endian:  " + checkTwosComplement(elf_header.ei_data),
    "Arch:    " + checkArch(elf_header.e_machine),
    "Type:    " + checkType(elf_header.e_type),
    "OS/ABI:  " + checkOSABI(elf_header.ei_osabi),
    "Format:  ELF64 Header OK"
  };

  constexpr int total_lines = 6;
  for (int i = 0; i < total_lines; ++i) {
    out.append(ascii_art[i]);
    out.append("   "); // Espacio de separación entre columnas
    out.append(info_lines[i]);
    out.append("\n");
  }
  out.flush();
  return 0;
}
