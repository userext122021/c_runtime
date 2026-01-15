#include <stdio.h>
#include <assert.h>
#include "vx_std.h"

typedef void (*vx_msg_f)(int);

void msg1(int val) { printf("msg1: %d\n", val); }
void msg2(int val) { printf("msg2: %d\n", val); }

int main() {
    vx_string_set str;
    
    // 1. Инициализация
    if (vx_string_set_init(&str) != 0) {
        fprintf(stderr, "Failed to init string set\n");
        return 1;
    }

    // 2. Добавление данных
    vx_string_set_add(&str, "msg1");
    vx_string_set_add(&str, "msg2");

    // 3. ПЕЧАТЬ (Важно: \n в конце принудительно "выталкивает" текст из буфера на экран)
    // Используем vx_string_set_find, чтобы получить индексы
    int id1 = vx_string_set_find(&str, "msg1");
    int id2 = vx_string_set_find(&str, "msg2");
    size_t sz = vx_string_set_get_size(&str);

    printf("msg1_idx: %d | msg2_idx: %d | size: %zu\n", id1, id2, sz);

    // 4. Гарантируем вывод, если система тормозит (Force flush)
    fflush(stdout);

    // 5. Очистка
    vx_string_set_uninit(&str);
    
    return 0;
}
