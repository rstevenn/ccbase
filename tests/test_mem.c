#include <stdio.h>

#define CCB_ARENA_IMPL
#include "../utils/mem.h"
#include "../logs/log.h"

#define RAM_SIZE 64*mb
unsigned char ram[RAM_SIZE];

int main( int argc, char* argv[]) {
    printf("Test mem\n");

    ccb_arena_nos_setup_memory(ram, RAM_SIZE);
    ccb_arena* arena  = ccb_init_nos_arena(ram);
    ccb_arena* arena1 = ccb_init_nos_arena(ram);
    ccb_arena* arena2 = ccb_init_nos_arena(ram);
    ccb_arena* arena3 = ccb_init_nos_arena(ram);
    ccb_arena* arena4 = ccb_init_nos_arena(ram);

    ccb_nos_arena_malloc(ram, arena, 256);
    ccb_nos_arena_malloc(ram, arena, 4*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);

    ccb_nos_arena_reset(arena);

    ccb_nos_arena_malloc(ram, arena, 256);
    ccb_nos_arena_malloc(ram, arena, 4*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);
    ccb_nos_arena_malloc(ram, arena, 12*kb);

    ccb_nos_arena_free(ram, arena);
    
    printf("end nos test\n");


    return 0;
    /*
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
    */
}