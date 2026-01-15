#ifndef VX_STD_H
#define VX_STD_H

typedef uint8_t vx_byte;
typedef unsigned int vx_id;

typedef struct
{
size_t size;
size_t item_size;
size_t alloc_size; //amount of items to alloc 
vx_byte *data;
}vx_array;

#endif
