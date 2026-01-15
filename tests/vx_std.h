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
    size_t size;
    size_t item_size;
    size_t alloc_size;     /* Current capacity in elements */
    size_t capacity_bytes;
    size_t min_alloc;      /* Minimum number of elements to allocate */
    vx_byte *data;
} vx_array;

#endif /* VX_STD_H */
