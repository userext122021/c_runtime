#ifndef VX_STD_H
#define VX_STD_H

#include <stdint.h> // Required for uint8_t
#include <stddef.h> // Required for size_t

/* Basic types for the VX ecosystem */
typedef uint8_t      vx_byte;
typedef unsigned int vx_id;

/**
 * @struct vx_array_s
 * @brief A dynamic array implementation for the Vertex Shell environment.
 */
#define VX_ARRAY_GET(type, arr_ptr, idx) (*(type*)vx_array_at(arr_ptr, idx))
typedef struct vx_array_s
{
    size_t size;
    size_t item_size;
    size_t alloc_size;     /* Current capacity in elements */
    size_t capacity_bytes;
    size_t min_alloc;      /* Minimum number of elements to allocate */
    vx_byte *data;
} vx_array;

/* Initializes the array structure with item size and default values */
int vx_array_init(vx_array *array, size_t item_size);

/* Frees internal buffer and resets metadata */
void vx_array_free(vx_array *array);

/* Ensures the array has enough memory for at least new_alloc elements */
int vx_array_reserve(vx_array *array, size_t new_alloc);

/* Adds an element to the end, growing the array if necessary */
int vx_array_push_back(vx_array *array, const void *item);

/* Removes element at index and shifts subsequent elements */
int vx_array_remove(vx_array *array, size_t index);

/* Returns a pointer to the element at index, or NULL if out of bounds */
void* vx_array_at(const vx_array *array, size_t index);

/* Copies data from item into the element at specified index */
int vx_array_set(vx_array *array, size_t index, const void *item);

/* Resets size to 0 without freeing memory */
void vx_array_clear(vx_array *array);

//VX STRINGS
typedef struct vx_string_s
{
    vx_array buffer; /* Internal buffer to store characters */
} vx_string;

/* Allocates a new vx_string on the heap and initializes it */
vx_string* vx_string_new(const char *initial_text);

/* Initializes an empty string */
int vx_string_init(vx_string *str);

/* Initializes a string from a C-style string (char*) */
int vx_string_set_c(vx_string *str, const char *c_str);

/* Appends a C-style string to the end */
int vx_string_append_c(vx_string *str, const char *c_str);

/* Returns a pointer to a null-terminated C-string */
const char* vx_string_get_c(const vx_string *str);

/* Frees string memory */
void vx_string_free(vx_string *str);

#endif /* VX_STD_H */
