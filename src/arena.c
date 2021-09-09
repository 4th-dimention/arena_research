////////////////////////////////
// NOTE(allen): Arena Core Functions

#define ARENA_HEADER_SIZE 64

static Arena*
arena_alloc(U64 cap, U64 cmt_size){
    Arena *result = 0;
    void *memory = mem_reserve(cap);
    if (mem_commit(memory, cmt_size)){
        result = (Arena*)memory;
        result->pos = ARENA_HEADER_SIZE;
        result->cmt = cmt_size;
        result->cap = cap;
        result->align = 8;
        result->cmt_size = cmt_size;
    }
    return(result);
}

static void
arena_release(Arena *arena){
    mem_release(arena, arena->cap);
}

static void*
arena_push(Arena *arena, U64 size){
    void *result = 0;
    
    U64 pos = arena->pos;
    U64 align_mask = arena->align - 1;
    U64 pos_aligned = (pos + align_mask) & ~align_mask;
    U64 new_pos = pos_aligned + size;
    
    if (new_pos <= arena->cap){
        if (new_pos > arena->cmt){
            U64 cmt_mask = arena->cmt_size - 1;
            U64 new_cmt = (new_pos + cmt_mask) & ~cmt_mask;
            U64 new_cmt_clamped = ClampTop(new_cmt, arena->cap);
            U64 cmt_size = new_cmt_clamped - arena->cmt;
            if (mem_commit((U8*)arena + arena->cmt, cmt_size)){
                arena->cmt += cmt_size;
            }
        }
        if (new_pos < arena->cmt){
            result = (U8*)arena + pos_aligned;
            arena->pos = new_pos;
        }
    }
    
    return(result);
}

static void
arena_pop_to(Arena *arena, U64 pos){
    U64 pos_clamped = ClampBot(ARENA_HEADER_SIZE, pos);
    if (arena->pos > pos_clamped){
        arena->pos = pos_clamped;
    }
}

static U64
arena_get_pos(Arena *arena){
    return(arena->pos);
}

static void
arena_set_align(Arena *arena, U64 align){
    arena->align = align;
}

static U64
arena_get_align(Arena *arena){
    return(arena->align);
}


////////////////////////////////
// NOTE(allen): Arena Helpers

static ArenaTemp
arena_temp_begin(Arena *arena){
    U64 pos = arena_get_pos(arena);
    ArenaTemp result = {arena, pos};
    return(result);
}

static void
arena_temp_end(ArenaTemp temp){
    arena_pop_to(temp.arena, temp.pos);
}

static void
arena_put_back(Arena *arena, U64 amt){
    U64 pos = arena_get_pos(arena);
    U64 new_pos = 0;
    if (pos > amt){
        new_pos = pos - amt;
    }
    arena_pop_to(arena, new_pos);
}

