#include <stdio.h>
#include <assert.h>
#include "vx_std.h"

typedef void (*vx_msg_f)(int);

void msg1(int val) { printf("msg1: %d\n", val); }
void msg2(int val) { printf("msg1: %d\n", val); }



int main() {
vx_string_set str;
    vx_string_set_init(&str);
    vx_string_set_add(&str,"msg1");
    vx_string_set_add(&str,"msg2");

    printf(" msg1:%d msg2:%d size:%d\n",vx_string_set_get(&str,"msg1",vx_string_set_get(&str,"msg2",);
    
    vx_string_set_uninit(&str);
    return 0;
}
