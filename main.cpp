#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <array>
#include <fcntl.h>
#include <unistd.h>
#include <array>
using namespace std;
typedef array<char, 0x40> Header;

#include <cstdio>
#include <array>

Header read_elf_header(const char* ruta_archivo) {
    FILE* archivo = fopen(ruta_archivo, "rb");
    if (!archivo) return {};
    setvbuf(archivo, nullptr, _IONBF, 0);
    Header buffer{};
    fread(buffer.data(), 1, buffer.size(), archivo);
    fclose(archivo);
    return buffer;
}

#pragma pack(push, 1)
struct ElfHeader {
    array<unsigned char, 4>  magic;      // Offset 0x00, Tamaño 4 (0x7F, 'E', 'L', 'F')
    uint8_t  ei_class;   // Offset 0x04, Tamaño 1 (1 = 32-bit, 2 = 64-bit)
    uint8_t  ei_data;    // Offset 0x05, Tamaño 1 (1 = Little Endian, 2 = Big Endian)
};
#pragma pack(pop)

int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const string path = argv[1];
   cout << path << '\n';
   Header header = read_elf_header(path.c_str());   
   cout << header.size() << '\n';
   ElfHeader elf_header;
   memcpy(&elf_header, header.data(), sizeof(ElfHeader));
   cout << ((elf_header.magic[0] == 0x7F) ? "ELF" : "NOT ELF") << '\n';
   return 0;
}
