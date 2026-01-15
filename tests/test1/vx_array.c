#include <stdlib.h>
#include <stdint.h>
#include <string.h> // Required for memcpy
#include "vx_std.h"

int vx_array_init(vx_array *array, size_t item_size)
{
    /* Safety check: ensure the pointer is valid */
    if (array == NULL) {
        return -1; // Or a specific error code like VX_ERR_INVALID_ARG
    }

    array->item_size = item_size;
    array->size = 0;
    array->alloc_size = 0;
    array->capacity_bytes = 0; /* Important: initialize our safety field */
    array->min_alloc = 10;     /* Default growth threshold */
    array->data = NULL;        /* Data is allocated on first push */

    return 0; // Success
}

/* 
 * Reserves memory for at least 'new_alloc' elements.
 * Returns 0 on success, -1 on memory failure.
 */
int vx_array_reserve(vx_array *array, size_t new_alloc)
{
    if (array == NULL) return -1;

    /* If we already have enough space, do nothing */
    if (new_alloc <= array->alloc_size) return 0;

    /* Enforce min_alloc for the first allocation */
    if (new_alloc < array->min_alloc && array->alloc_size == 0) {
        new_alloc = array->min_alloc;
    }

    size_t new_capacity = new_alloc * array->item_size;

    /* Check for integer overflow before allocation */
    if (array->item_size != 0 && new_capacity / array->item_size != new_alloc) {
        return -1; // Overflow detected
    }

    vx_byte *new_data = (vx_byte *)realloc(array->data, new_capacity);
    if (new_data == NULL) {
        return -1; // Out of memory
    }

    array->data = new_data;
    array->alloc_size = new_alloc;
    array->capacity_bytes = new_capacity;

    return 0;
}



/**
 * Adds an element to the end of the array.
 * If the array is full, it automatically grows using a growth factor of 2.
 * 
 * @param array Pointer to the vx_array
 * @param item Pointer to the data to be copied into the array
 * @return 0 on success, -1 on memory failure or invalid arguments
 */
int vx_array_push_back(vx_array *array, const void *item)
{
    if (array == NULL || item == NULL) {
        return -1;
    }

    /* 1. Check if we need more memory */
    if (array->size >= array->alloc_size) {
        /* Calculate new allocation size: if 0, use min_alloc, otherwise double it */
        size_t new_alloc = (array->alloc_size == 0) 
                           ? array->min_alloc 
                           : array->alloc_size * 2;

        /* Use our reserve function to handle memory allocation */
        if (vx_array_reserve(array, new_alloc) != 0) {
            return -1; // Memory allocation failed
        }
    }

    /* 2. Calculate the destination address in the raw data buffer */
    /* Formula: data_start + (current_index * size_of_one_item) */
    vx_byte *destination = array->data + (array->size * array->item_size);

    /* 3. Copy the item data into the array */
    memcpy(destination, item, array->item_size);

    /* 4. Increment the size */
    array->size++;

    return 0;
}


/**
 * Frees the internal memory of the array and resets its fields.
 * This function does not free the vx_array structure itself if it was 
 * allocated on the heap; it only cleans up the internal buffer.
 * 
 * @param array Pointer to the vx_array to be cleared.
 */
void vx_array_free(vx_array *array)
{
    if (array == NULL) {
        return;
    }

    /* 1. Free the raw data buffer */
    if (array->data != NULL) {
        free(array->data);
        array->data = NULL; /* Prevent double-free */
    }

    /* 2. Reset all fields to zero for safety */
    array->size = 0;
    array->alloc_size = 0;
    array->capacity_bytes = 0;
    
    /* We keep item_size and min_alloc as they were, 
       in case the user wants to re-use the structure. */
}

/**
 * Returns a pointer to the element at the specified index.
 * 
 * @param array Pointer to the vx_array
 * @param index Position of the element
 * @return Pointer to the element, or NULL if index is out of bounds
 */
void* vx_array_at(const vx_array *array, size_t index)
{
    if (array == NULL || index >= array->size) {
        return NULL; /* Out of bounds or invalid array */
    }

    /* Calculate address: start + (index * item_size) */
    return (void*)(array->data + (index * array->item_size));
}

/**
 * Copies the data from 'item' into the array at the specified index.
 * The index must be within the current size of the array.
 * 
 * @param array Pointer to the vx_array
 * @param index Position where to set the data
 * @param item Pointer to the new data
 * @return 0 on success, -1 on failure
 */
int vx_array_set(vx_array *array, size_t index, const void *item)
{
    if (array == NULL || item == NULL || index >= array->size) {
        return -1;
    }

    /* Calculate destination address */
    vx_byte *dest = array->data + (index * array->item_size);
    
    /* Copy new data over existing data */
    memcpy(dest, item, array->item_size);
    
    return 0;
}

int vx_array_remove(vx_array *array, size_t index) {
    if (array == NULL || index >= array->size) return -1;

    if (index < array->size - 1) {
        vx_byte *dest = array->data + (index * array->item_size);
        vx_byte *src = dest + array->item_size;
        size_t bytes_to_move = (array->size - index - 1) * array->item_size;
        memmove(dest, src, bytes_to_move);
    }
    array->size--;
    return 0;
}

void vx_array_clear(vx_array *array) {
    if (array) array->size = 0;
}

