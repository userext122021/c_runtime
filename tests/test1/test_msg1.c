#include <stdio.h>
#include <assert.h>
#include "vx_std.h"

typedef void (*vx_msg_f)(int);

void msg1(int val) { printf("msg1: %d\n", val); }
void msg2(int val) { printf("msg1: %d\n", val); }


int main() {

    return 0;
}
