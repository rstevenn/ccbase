#ifndef __MEM_H__
#define __MEM_H__

#include <stdlib.h>

#define byte sizeof(char)
#define kb 1024*byte
#define mb 1024*kb
#define gb 1024*mb

typedef struct _ccb_arena_type {
    const char* data;

    size_t capacity;

    struct _ccb_arena_type* next;
} ccb_arena;


#ifndef CCB_ARENA_CAPACITY
    #define CCB_ARENA_CAPACITY 16*kb
#endif

#ifndef CCB_ARENA_MALLOC
    #define CCB_ARENA_MALLOC malloc
#endif


#ifndef CCB_ARENA_FREE
    #define CCB_ARENA_FREE free
#endif

#define CCB_ARENA_IMPL 
#ifdef CCB_ARENA_IMPL

#include "../logs/log.h"

ccb_arena* ccb_init_arena(void) {
    ccb_arena* arena = (ccb_arena*)CCB_ARENA_MALLOC(sizeof(ccb_arena));
    CCB_NOTNULL(arena, "can't allocate memory for a new memory block metadat")

    arena->data = (char*)CCB_ARENA_MALLOC(CCB_ARENA_CAPACITY);
    arena->capacity = CCB_ARENA_CAPACITY;
    CCB_NOTNULL(arena->data, "can't allocate a new memory block")
    arena->next = NULL;

    return arena;
}

void* ccb_arena_malloc(ccb_arena* arena, size_t size) {
    if (size > CCB_ARENA_CAPACITY)
        return NULL;

    ccb_arena* current_arena = arena;
    
    while (current_arena->capacity < size || current_arena->capacity < 1) {
        if (current_arena->next == NULL) {
            current_arena->next = ccb_init_arena();
        }
        current_arena = current_arena->next;
    }
    
    current_arena->capacity -= size>0 ? size : 1;
    return (void*) &(current_arena[CCB_ARENA_CAPACITY-1-current_arena->capacity]);
}

void ccb_arena_reset(ccb_arena* arena) {
    ccb_arena* current_arena = arena;

    do {
        arena->capacity = CCB_ARENA_CAPACITY;
        current_arena = current_arena->next;
    } while (current_arena != NULL);
}

void ccb_arena_free(ccb_arena* arena) {
    ccb_arena* current_arena = arena;
    ccb_arena* previous_arena = arena;

    do {
        CCB_ARENA_FREE(current_arena->data);
        previous_arena = current_arena;
        current_arena = current_arena->next;
        CCB_ARENA_FREE(previous_arena);
    } while (current_arena != NULL);
}


#endif



#endif