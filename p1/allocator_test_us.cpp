#include "allocator.h"

#include <vector>
#include <set>
#include <iostream>

#include <cstdio>

using namespace std;
char buf[65536];

int main() {
    Allocator a(buf, sizeof(buf));

    int size = 500;

    Pointer p = a.alloc(size);
    char *v = reinterpret_cast<char*>(p.get());
    printf("%p\n", buf);
    printf("%p\n", v);

    a.free(p);
    return 0;
}