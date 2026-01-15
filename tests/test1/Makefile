# 1. Первая цель - всегда 'all'. Она не даст запускать '%' для мусора.
all: build
	@echo "Library built. Usage: make <test_name>"

pull:
	git pull

clean:
	rm -f *.o *.out

# 2. Компиляция только библиотечных файлов
build: pull
	gcc -Wall -Wextra vx_*.c -c

# 3. Уточняем правило: %: %.c
# Это значит: "Запускать только если существует файл с расширением .c"
%: %.c build
	gcc $< *.o -o $@.out
