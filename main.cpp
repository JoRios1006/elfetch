
#include <cstdio>
#include <filesystem>
#include <iostream>
using namespace std;
namespace fs = filesystem;
int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const fs::path path = argv[1];
   if (!(fs::exists(path) && fs::is_regular_file(path))) return 1;
   cout << path << '\n';

   return 0;
}
