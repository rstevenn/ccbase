#include <stdio.h>

#define CCB_ARENA_IMPL
#include "../utils/mem.h"



int main(unsigned int argc, char* argv[]) {
    printf("Test mem\n");
    
    ccb_arena* arena = ccb_init_arena();
    ccb_arena_malloc(arena, 256);
    ccb_arena_malloc(arena, 4*kb);
    ccb_arena_malloc(arena, 12*kb);
    ccb_arena_malloc(arena, 12*kb);
    ccb_arena_malloc(arena, 12*kb);

    ccb_arena_reset(arena);
    ccb_arena_malloc(arena, 256);
    ccb_arena_malloc(arena, 4*kb);
    ccb_arena_malloc(arena, 12*kb);
    ccb_arena_malloc(arena, 12*kb);
    ccb_arena_malloc(arena, 12*kb);

    ccb_arena_free(arena);

    printf("end malloc test\n");

    return 0;
}