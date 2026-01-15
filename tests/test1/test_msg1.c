#include <stdio.h>
#include <assert.h>
#include "vx_std.h"

// 1. Define a type for your function pointer for readability
typedef void (*vx_msg_f)(int);

// 2. Some dummy functions to test
void msg1(int val) { printf("msg1: %d\n", val); }
void msg2(int val) { printf("msg1: %d\n", val); }
vx_array msg_functions;
vx_string_set u_strings;    
int main() {
    vx_array_init(&handlers, sizeof(vx_msg_f));
    vx_string_set_init(&u_strings);
 
 
   

    vx_string_set_uninit(&u_strings);
    vx_array_uninit(&handlers);

    return 0;
}
