#include "../logs/trace_log.h"

ccb_maybe_t ko(){
    CCB_TRACE_RETURN_KO("ko");    
}

ccb_maybe_t ok() {
    int a = 1;
    CCB_TRACE_RETURN_OK(int, a);
}

ccb_maybe_t foo() {
    int a;
    ccb_maybe_t out = ko();

    CCB_TRACE_DECODE_MAYBE(out, int, a)
    CCB_TRACE_RETURN_OK(int, 1);
}

ccb_maybe_t bar() { 
    int a;
    ccb_maybe_t out = foo();

    CCB_TRACE_DECODE_MAYBE(out, int, a)
    CCB_TRACE_RETURN_OK(int, 1);
}


int main() {
    int a;
    ccb_maybe_t out = bar();
    
    if (!out.ok) printf("%s", out.msg);
    if (out.ok) printf("ok\n");

    return 0;
}
