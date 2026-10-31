
#include <cstdio>
#include <iostream>
#include <string_view>
using namespace std;
typedef string_view stringv;
int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   const stringv path = argv[1];
   cout << path << '\n';   
      
   return 0;
}
