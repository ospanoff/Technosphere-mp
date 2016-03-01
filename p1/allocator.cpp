#include "allocator.h"
#include <iostream>
#include <cstring>
#include <set>

Pointer Allocator::alloc(size_t N)
{
    size_t last_free_ptr = 0;
    bool existSpace = false;

    if (free_space < N) {
        throw AllocError(AllocErrorType::NoMemory, "Недостаточно памяти");
    }

    for (auto const ptr : ptrs) {
        if (ptr.first - last_free_ptr >= N) {
            existSpace = true;
            break;
        }
        existSpace = false;
        last_free_ptr = ptr.first + ptr.second;
    }

    if (!existSpace) {
        std::cout << "IMH\n";
        defrag();
        auto last = ptrs.rbegin()++;
        last_free_ptr = last->first + last->second;
    }

    ptrs[last_free_ptr] = N;
    free_space -= N;
    return Pointer(&mem[last_free_ptr]);
}

void Allocator::realloc(Pointer &p, size_t N)
{

}

void Allocator::free(Pointer &p)
{
    size_t offset = reinterpret_cast<char *>(p.get()) - mem;
    free_space += ptrs[offset];
    ptrs.erase(offset);
    p = Pointer();
}

void Allocator::defrag()
{
    char tmp_buf[size];
    std::set<size_t> ends;
    size_t end = 0;

    for (auto ptr : ptrs) {
        memcpy(&tmp_buf[end], &mem[ptr.first], ptr.second);
        end += ptr.second;
        ends.insert(end);
    }

    ptrs.clear();
    end = 0;

    for (auto e : ends) {
        ptrs[end] = e;
        end = e;
    }
    ptrs[size] = 0;

    memcpy(mem, tmp_buf, end);
}