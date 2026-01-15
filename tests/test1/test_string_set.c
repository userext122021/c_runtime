#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "vx_std.h"

int main() {
    printf("Running Vertex Shell: vx_string_set unit tests...\n");

    vx_string_set set;
    
    // 1. Test Initialization
    assert(vx_string_set_init(&set) == 0);
    assert(set.strings.size == 0);
    printf("[PASS] Initialization\n");

    // 2. Test Adding Unique Strings
    int idx1 = vx_string_set_add(&set, "Vertex");
    int idx2 = vx_string_set_add(&set, "Shell");
    int idx3 = vx_string_set_add(&set, "OpenStep");

    assert(idx1 == 0);
    assert(idx2 == 1);
    assert(idx3 == 2);
    assert(set.strings.size == 3);
    printf("[PASS] Adding 3 unique strings\n");

    // 3. Test Adding Duplicates (The "Unique" part)
    int idx_dup = vx_string_set_add(&set, "Vertex");
    assert(idx_dup == 0);          // Must return existing index
    assert(set.strings.size == 3); // Size must not increase
    printf("[PASS] Duplicate rejection (Index: %d)\n", idx_dup);

    // 4. Test Finding Strings
    int found_idx = vx_string_set_find(&set, "Shell");
    int not_found = vx_string_set_find(&set, "Linux");
    
    assert(found_idx == 1);
    assert(not_found == -1);
    printf("[PASS] Find existing and non-existing strings\n");

    // 5. Test Access (Get)
    vx_string *s = vx_string_set_get(&set, 2);
    assert(s != NULL);
    assert(strcmp(vx_string_get_c(s), "OpenStep") == 0);
    printf("[PASS] Get string by index: '%s'\n", vx_string_get_c(s));

    // 6. Test Deep Cleanup
    // We use valgrind later to ensure all vx_string objects are freed
    vx_string_set_deinit(&set);
    assert(set.strings.data == NULL);
    printf("[PASS] Deep deinitialization\n");

    printf("\nAll String Set tests passed for Vertex Shell!\n");
    return 0;
}
