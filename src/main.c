////////////////////////////////
// NOTE(allen): Includes

// TODO(allen): Arena ideas I would like to work on.
//  1. tight reserve uncapped arena with minimal overhead and/or complexity
//  2. multi-threaded arena design
//  3. arena has pointer tests
//  4. arena attached allocations
//  5. explicit "perform cleanup" (decommit, release any free list)

#include "types.h"
#include "helpers.h"
#include "memory.h"
#include "arena.h"

#include "memory_win32.c"
#include "arena.c"

#include <stdio.h>

static void
test_reserve_caps(char *header, U64 size){
    printf("%s\n", header);
    fflush(stdout);
    
    B32 gave_up = 0;
    U32 count = 0;
    for (;;){
        void *memory = mem_reserve(size);
        if (memory == 0){
            break;
        }
        count += 1;
        if (count % 1000 == 0){
            printf("%u ...\n", count);
            fflush(stdout);
            if (count == 20*1000){
                gave_up = 1;
                break;
            }
        }
    }
    
    if (!gave_up){
        printf("%u\n", count);
    }
    else{
        printf("gave up!\n");
    }
}

static void
test_arena_basics(void){
    Arena *arena = arena_alloc(1 << 30, 64 << 10);
    {
        U64 *vals = push_array(arena, U64, 100);
        vals[0] = 0;
        vals[99] = 100;
        arena_put_back(arena, 8*10);
        U64 *new_vals = push_array(arena, U64, 20);
        if (new_vals + 9 == vals + 99){
            printf("worked as expected\n");
        }
    }
}

static void
test_arena_caps(char *header, U64 cap, U64 cmt_size){
    printf("%s\n", header);
    fflush(stdout);
    
    B32 gave_up = 0;
    U32 count = 0;
    for (;;){
        Arena *arena = arena_alloc(cap, cmt_size);
        if (arena == 0){
            break;
        }
        U64 *vals = push_array(arena, U64, 100);
        vals[99] = 100;
        count += 1;
        if (count % 1000 == 0){
            printf("%u ...\n", count);
            fflush(stdout);
            if (count == 20*1000){
                gave_up = 1;
                break;
            }
        }
    }
    
    if (!gave_up){
        printf("%u\n", count);
    }
    else{
        printf("gave up!\n");
    }
}

int
main(int argc, char **argv){
    //test_reserve_caps("How many times can I reserve 1TB?", 1llu << 40);
    //test_reserve_caps("How many times can I reserve 1GB?", 1llu << 30);
    //test_arena_basics();
    //test_arena_caps("How many 1GB/64KB arenas can I allocate?", 1 << 30, 64 << 10);
    //test_arena_caps("How many 1GB/64MB arenas can I allocate?", 1 << 30, 64 << 20);
    //test_arena_caps("How many 64MB/64KB arenas can I allocate?", 64 << 20, 64 << 10);
    
    return(0);
}

