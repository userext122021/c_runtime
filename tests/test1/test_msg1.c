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

    vx_array foo;
    vx_array_init(&foo,sizeof(vx_msg_f));
    vx_array_resize(&foo,sz);

      // 1. Создаем переменные-указатели (ОБЯЗАТЕЛЬНО)
    vx_msg_f f1 = msg1;
    vx_msg_f f2 = msg2;
    
    vx_array_set(&foo,id1,&f1);
    vx_array_set(&foo,id2,&f2);
    
    
    
    printf("msg1_idx: %d | msg2_idx: %d | size: %zu\n", id1, id2, sz);


    vx_msg_f *call_msg1 = (vx_msg_f*)vx_array_at(&foo, id1);
    vx_msg_f *call_msg2 = (vx_msg_f*)vx_array_at(&foo, id2);

    (*call_msg1)(123);
    (*call_msg2)(246);
    

    
    // 4. Гарантируем вывод, если система тормозит (Force flush)
    fflush(stdout);

    // 5. Очистка
    vx_string_set_uninit(&str);
    vx_array_uninit(&foo);
    return 0;
}
