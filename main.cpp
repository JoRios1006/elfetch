#include <cstdio>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;
bool is_file(fs::path p){return !(fs::exists(p) && fs::is_regular_file(p));}
int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const fs::path path = argv[1];
   if (is_file(path)) return 1;
   cout << path << '\n';
   FILE *FD = fopen(path.c_str(), "rb");

   return 0;
}
