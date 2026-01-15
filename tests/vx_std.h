#ifndef VX_STD_H
#define VX_STD_H

typedef uint8_t vx_byte;
typedef int vx_id;
typedef int vx_size;

typedef struct
{
vx_size size;
vx_size item_size;
vx_size alloc_size; //amount of items to alloc 
vx_byte *data;
}vx_array;

#endif
