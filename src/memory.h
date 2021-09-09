/* date = September 8th 2021 9:41 pm */

#ifndef MEMORY_H
#define MEMORY_H

////////////////////////////////
// NOTE(allen): Memory Wrapper Interface

static void* mem_reserve(U64 size);
static B32   mem_commit(void *ptr, U64 size);
static void  mem_decommit(void *ptr, U64 size);
static void  mem_release(void *ptr, U64 size);

#endif //MEMORY_H
