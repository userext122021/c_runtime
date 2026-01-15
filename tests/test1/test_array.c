#include <stdio.h>
#include <assert.h>
#include "vx_std.h"

int main() {
    printf("Running Vertex Shell: vx_array unit tests...\n");

    vx_array ids;
    
    // 1. Test Initialization
    assert(vx_array_init(&ids, sizeof(int)) == 0);
    assert(ids.size == 0);
    assert(ids.data == NULL);
    printf("[PASS] Initialization\n");

    // 2. Test Push Back
    for (int i = 0; i < 15; i++) {
        vx_array_push_back(&ids, &i);
    }
    assert(ids.size == 15);
    assert(ids.alloc_size >= 15); // Should have grown beyond min_alloc (10)
    printf("[PASS] Push Back (15 elements, triggered growth)\n");

    // 3. Test Access (Get)
    int *val_ptr = (int*)vx_array_at(&ids, 5);
    assert(val_ptr != NULL);
    assert(*val_ptr == 5);
    
    void *out_of_bounds = vx_array_at(&ids, 100);
    assert(out_of_bounds == NULL);
    printf("[PASS] Element Access (Get & Bounds check)\n");

    // 4. Test Set
    int new_val = 99;
    assert(vx_array_set(&ids, 5, &new_val) == 0);
    assert(*(int*)vx_array_at(&ids, 5) == 99);
    printf("[PASS] Element Set\n");

    // 5. Test Remove
    // Array was: [0, 1, 2, 3, 4, 99, 6, 7, ...]
    // Removing index 5 (value 99)
    assert(vx_array_remove(&ids, 5) == 0);
    assert(ids.size == 14);
    assert(*(int*)vx_array_at(&ids, 5) == 6); // Next element shifted left
    printf("[PASS] Element Remove & Shift\n");

    // 6. Test Clear
    vx_array_clear(&ids);
    assert(ids.size == 0);
    assert(ids.data != NULL); // Memory should still be there
    printf("[PASS] Array Clear\n");

    // 7. Test Free
    vx_array_free(&ids);
    assert(ids.data == NULL);
    assert(ids.size == 0);
    printf("[PASS] Array Free\n");

    printf("\nAll tests passed successfully for Vertex Shell stdlib!\n");
    return 0;
}
