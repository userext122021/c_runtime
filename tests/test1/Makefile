pull:
	git pull
clean:
	rm *.o *.out
%:
	gcc $@.c *.o -o $@.out
build:pull
	gcc vx_*.c -c

