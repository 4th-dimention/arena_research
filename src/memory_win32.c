////////////////////////////////
// NOTE(allen): Win32 Memory Implementation

#include <Windows.h>

static void*
mem_reserve(U64 size){
    void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
    return(result);
}

static B32
mem_commit(void *ptr, U64 size){
    B32 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != 0);
    return(result);
}

static void
mem_decommit(void *ptr, U64 size){
    VirtualFree(ptr, size, MEM_DECOMMIT);
}

static void
mem_release(void *ptr, U64 size){
    VirtualFree(ptr, size, MEM_RELEASE);
}
