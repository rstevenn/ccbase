#include <stdio.h>
#include <stdlib.h>

#define CCB_ARENA_IMPL
//#define CCB_ARENA_CAPACITY kb
#include "../utils/mem.h"
#include "../logs/log.h"

#define RAM_SIZE mb
unsigned char ram[RAM_SIZE];

void dump_ram(char name[]) {
    ccb_area_ram_data meta_data = ((ccb_area_ram_data*)ram)[0];
    
    FILE* fp = fopen(name, "w");
    
    fprintf(fp, "metadata:\n");
    
    fprintf(fp, "ram size = %llu\n", meta_data.ram_size);
    fprintf(fp, "max nb blocks = %llu\n", meta_data.max_block_numbers);

    fprintf(fp, "ram adresses:\n");
    fprintf(fp, "ram base= %p\n", ram-ram);
    fprintf(fp, "blocks status base= %p\n", (size_t)meta_data.blocks_status - (size_t)ram);
    fprintf(fp, "blocks base= %p\n\n", (size_t)meta_data.blocks - (size_t)ram);


    fprintf(fp, "raw_data:\n");
    for (size_t i=0; i<RAM_SIZE; i++) {
        fprintf(fp, "%02X ", ram[i]);

        if (i > 0) {
            if ((i+1)%16==0) fprintf(fp, "\n");
            if ((i+1)%1024==0) {fprintf(fp, "\n"); fprintf(fp, "%p:\n" , (size_t)&ram[i] - (size_t)ram );}
        }
    }

    fclose(fp);
}


int main( int argc, char* argv[]) {
    printf("Test mem\n");
    printf("setup ram..\n");
    ccb_arena_nos_setup_memory(ram, RAM_SIZE);
    dump_ram("ram0.txt");

    printf("setup arena..\n");
    ccb_arena* arena  = ccb_init_nos_arena(ram);
    dump_ram("ram1.txt");
    
    printf("arena0\n");
    ccb_arena* arena1 = ccb_init_nos_arena(ram);
    dump_ram("ram2.txt");
    
    printf("arena1\n");
    ccb_arena* arena2 = ccb_init_nos_arena(ram);
    dump_ram("ram3.txt");

    printf("arena2\n");
    ccb_arena* arena3 = ccb_init_nos_arena(ram);
    printf("arena3\n");
    ccb_arena* arena4 = ccb_init_nos_arena(ram);
    printf("arena4\n");

    printf("malloc..\n");
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


