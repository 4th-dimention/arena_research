/* date = September 8th 2021 9:36 pm */

#ifndef ARENA_H
#define ARENA_H

////////////////////////////////
// NOTE(allen): Arena Types

typedef struct Arena{
    U64 pos;
    U64 cmt;
    U64 cap;
    U64 align;
    U64 cmt_size;
} Arena;

typedef struct ArenaTemp{
    Arena *arena;
    U64 pos;
} ArenaTemp;

////////////////////////////////
// NOTE(allen): Arena Core Functions

static Arena* arena_alloc(U64 cap, U64 cmt_size);
static void   arena_release(Arena *arena);
static void*  arena_push(Arena *arena, U64 size);
static void   arena_pop_to(Arena *arena, U64 pos);
static U64    arena_get_pos(Arena *arena);
static void   arena_set_align(Arena *arena, U64 align);
static U64    arena_get_align(Arena *arena);

////////////////////////////////
// NOTE(allen): Arena Helpers

#define push_array(a,T,c)      (T*)arena_push((a), sizeof(T)*(c))
#define push_array_zero(a,T,c) (T*)memset(arena_push((a), sizeof(T)*(c)), 0, sizeof(T)*(c))

static ArenaTemp arena_temp_begin(Arena *arena);
static void      arena_temp_end(ArenaTemp temp);
static void      arena_put_back(Arena *arena, U64 amt);


#endif //ARENA_H
