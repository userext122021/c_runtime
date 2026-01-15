all:build
	echo Building all... 
pull:
	git pull
clean:
	rm *.o *.out
%:build
	gcc $@.c *.o -o $@.out
build:pull
	gcc vx_*.c -c

