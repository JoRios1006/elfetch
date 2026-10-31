#include <cstdio>
#include <filesystem>
#include <iostream>
#include <array>

using namespace std;
namespace fs = filesystem;
typedef array<char, 0x40> Header;
bool is_file(fs::path p){return !(fs::exists(p) && fs::is_regular_file(p));}

Header read_header(const filesystem::path& ruta) {
    FILE* archivo = fopen(ruta.string().c_str(), "rb");
    if (!archivo) return {};
    array<char, 0x40> buffer{};
    fread(buffer.data(), 1, buffer.size(), archivo);
    fclose(archivo);
    return buffer;
}
int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const fs::path path = argv[1];
   if (is_file(path)) return 1;
   cout << path << '\n';
   Header header = read_header(path);   
   cout << header.size() << '\n';

   return 0;
}
