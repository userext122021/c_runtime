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
typedef struct vx_array_s
{
    size_t size;           /* Current number of elements in the array */
    size_t item_size;      /* Size of a single element in bytes */
    size_t alloc_size;     /* Maximum number of elements before reallocation */
    size_t capacity_bytes; /* Total allocated memory in bytes (alloc_size * item_size) */
    vx_byte *data;         /* Pointer to the raw data buffer */
} vx_array;

#endif /* VX_STD_H */
