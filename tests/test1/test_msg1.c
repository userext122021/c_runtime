#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "vx_std.h"

int main() {
    printf("Vertex Shell Sandbox: Custom Test...\n\n");

    /* 1. Initialization */
    vx_string_set set;
    vx_string_set_init(&set);

    vx_array array;
    vx_array_init(&array, sizeof(int)); // Change sizeof() to your type

    /* --- START YOUR LOGIC HERE --- */



    /* --- END YOUR LOGIC HERE --- */

    /* 2. Cleanup */
    vx_array_deinit(&array);
    vx_string_set_deinit(&set);

    printf("\nSandbox execution finished.\n");
    return 0;
}
