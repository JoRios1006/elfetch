#include <cstdio>
#include <filesystem>
#include <iostream>
#include <array>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <iostream>
using namespace std;
namespace fs = filesystem;
typedef array<char, 0x40> Header;

#include <cstdio>
#include <array>

Header read_elf_header(const char* ruta_archivo) {
    FILE* archivo = fopen(ruta_archivo, "rb");
    if (!archivo) return {};

    // Forzar al flujo C a no almacenar páginas de 4096 bytes en memoria
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

   return 0;
}
