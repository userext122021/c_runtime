#include <stdlib.h>
#include <stdint.h>
#include "vx_std.h"

int vx_array_init(vx_array *array,size_t item_size)
{
	array->item_size=item_size;
	array->size=0;
	array->alloc_size=0;
	return 0;
}


