#include <string.h>
#include "vx_std.h"

int vx_string_init(vx_string *str) {
    if (!str) return -1;
    /* Initialize buffer for bytes (characters) */
    if (vx_array_init(&str->buffer, sizeof(char)) != 0) return -1;
    
    /* Always start with a null-terminator for an empty string */
    char null_char = '\0';
    return vx_array_push_back(&str->buffer, &null_char);
}

const char* vx_string_get_c(const vx_string *str) {
    if (!str || !str->buffer.data) return "";
    return (const char*)str->buffer.data;
}

int vx_string_set_c(vx_string *str, const char *c_str) {
    if (!str || !c_str) return -1;
    
    size_t len = strlen(c_str);
    vx_array_clear(&str->buffer);
    
    /* Reserve space for characters + null terminator */
    if (vx_array_reserve(&str->buffer, len + 1) != 0) return -1;
    
    /* Copy data and set size */
    memcpy(str->buffer.data, c_str, len + 1);
    str->buffer.size = len + 1;
    
    return 0;
}

int vx_string_append_c(vx_string *str, const char *c_str) {
    if (!str || !c_str) return -1;
    
    size_t append_len = strlen(c_str);
    if (append_len == 0) return 0;

    /* Remove the current null-terminator before appending */
    if (str->buffer.size > 0) str->buffer.size--;

    /* Push each character including the new null-terminator */
    for (size_t i = 0; i <= append_len; i++) {
        if (vx_array_push_back(&str->buffer, &c_str[i]) != 0) return -1;
    }

    return 0;
}

void vx_string_free(vx_string *str) {
    if (str) vx_array_free(&str->buffer);
}
