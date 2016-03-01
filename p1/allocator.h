#pragma once

#include <stdexcept>
#include <string>
#include <map>

enum class AllocErrorType {
    InvalidFree,
    NoMemory,
};

class AllocError: std::runtime_error {
private:
    AllocErrorType type;

public:
    AllocError(AllocErrorType _type, std::string message):
            runtime_error(message),
            type(_type)
    {}

    AllocErrorType getType() const { return type; }
};

class Allocator;

class Pointer {
    void *ptr;
public:
    Pointer(void *_ptr = nullptr):
            ptr(_ptr)
    {}
    void *get() const { return ptr; }
};

class Allocator {
    char *mem;
    size_t size;
    size_t free_space;
    std::map<size_t, size_t> ptrs;

public:
    Allocator(void *base, size_t size):
            mem(reinterpret_cast<char *>(base)),
            size(size),
            free_space(size)
    {
        ptrs[size] = 0;
    }
    
    Pointer alloc(size_t N);
    void realloc(Pointer &p, size_t N);
    void free(Pointer &p);

    void defrag();
    std::string dump() { return ""; }
};