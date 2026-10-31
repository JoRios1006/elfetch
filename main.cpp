#include <cstdint>
#include <cstdio>
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


int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const string path = argv[1];
   cout << path << '\n';
   Header header = read_elf_header(path.c_str());   
   cout << header.size() << '\n';
   uint32_t magic = header[0x00];

   return 0;
}
