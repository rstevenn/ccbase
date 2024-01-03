#ifndef __CCB_REGEX_H__
#define __CCB_REGEX_H__

#include <stdint.h>
#include <string.h>

// non-determinist finate state machine
typedef struct {
    uint32_t nb_transitions;
    uint32_t* state;
} ccb_rgx_ndstate;

typedef struct {
    uint32_t states;
    uint32_t transitions;
    ccb_rgx_ndstate *state_m;
} ccb_rgx_ndfsm; 


// determinist finate state machine
typedef struct {
    uint32_t states;
    uint32_t transitions;
    uint32_t *state_m;
} ccb_rgx_dfsm; 

typedef ccb_rgx_dfsm ccb_rgx_compiled_t;


// core opi
int ccb_rgx_match(const char* regex, const char* string);
int ccb_rgx_match_compiled(ccb_rgx_compiled_t* compiled, const char* string); 

// utils
void ccb_rgx_compile(ccb_rgx_compiled_t* compiled, const char* regex);

// impl
#define __CCB_REGEX_IMPL__
#ifdef __CCB_REGEX_IMPL__

#endif // __CCB_REGEX_IMPL__

void ccb_rgx_compile(ccb_rgx_compiled_t* compiled, const char* regex) {
    // convert to ndfst
    ccb_rgx_ndfsm ndfsm;
    memset(&ndfsm, 0, sizeof(ndfsm));

    for (char* current=(char*)regex; *current != '\0'; current++) {
        
    }

    // convert from ndfst to dfst

}



#endif // __CCB_REGEX_H__