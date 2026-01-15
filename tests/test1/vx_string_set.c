#include <stdlib.h>
#include <string.h>
#include "vx_std.h"

/**
 * Initialize string set using pointers to vx_string objects.
 */
int vx_string_set_init(vx_string_set *set) {
    if (set == NULL) return -1;
    /* We store pointers (vx_string*), so item size is the size of a pointer */
    return vx_array_init(&set->strings, sizeof(vx_string*));
}

/**
 * Look for an existing string in the set by comparing its content.
 */
int vx_string_set_find(const vx_string_set *set, const char *c_str) {
    if (set == NULL || c_str == NULL) return -1;

    for (size_t i = 0; i < set->strings.size; i++) {
        /* Retrieve the pointer to vx_string from the raw array data */
        vx_string *s = *(vx_string**)vx_array_at(&set->strings, i);
        
        /* Compare content using our string utility */
        if (s != NULL && strcmp(vx_string_get_c(s), c_str) == 0) {
            return (int)i;
        }
    }
    return -1;
}

/**
 * Add unique string and return its index.
 */
int vx_string_set_add(vx_string_set *set, const char *c_str) {
    if (set == NULL || c_str == NULL) return -1;

    /* 1. Return index if string is already in the set */
    int existing_idx = vx_string_set_find(set, c_str);
    if (existing_idx != -1) {
        return existing_idx;
    }

    /* 2. Allocate and create a new vx_string object */
    vx_string *new_s = vx_string_new(c_str);
    if (new_s == NULL) return -1;

    /* 3. Add the pointer to the array */
    if (vx_array_push_back(&set->strings, &new_s) != 0) {
        vx_string_destroy(new_s);
        return -1;
    }

    /* 4. Return the index of the newly added string */
    return (int)(set->strings.size - 1);
}

/**
 * Get string object by index with bounds checking.
 */
vx_string* vx_string_set_get(const vx_string_set *set, size_t index) {
    if (set == NULL || index >= set->strings.size) {
        return NULL;
    }
    /* Cast the raw pointer from the array back to vx_string* */
    return *(vx_string**)vx_array_at(&set->strings, index);
}

/**
 * Deep clean: free every vx_string object, then the pointer array.
 */
void vx_string_set_free(vx_string_set *set) {
    if (set == NULL) return;

    /* First pass: destroy each string object on the heap */
    for (size_t i = 0; i < set->strings.size; i++) {
        vx_string *s = *(vx_string**)vx_array_at(&set->strings, i);
        if (s != NULL) {
            vx_string_free(s);
        }
    }

    /* Second pass: free the internal array that held the pointers */
    vx_array_free(&set->strings);
}
