#ifndef __CCB_REGEX_H__
#define __CCB_REGEX_H__

#include <stdint.h>

// state machine
typedef struct {
    uint32_t states;
    uint32_t transitions;
    uint32_t *state_m;
} ccb_rgx_state_machine_t;

// core opi
int ccb_rgx_match(const char* regex, const char* string);
int ccb_rgx_match_compiled(ccb_rgx_state_machine_t* compiled, const char* string); 

// utils
void ccb_rgx_compile(ccb_rgx_state_machine_t* compiled, const char* regex);

// impl



#endif // __CCB_REGEX_H__