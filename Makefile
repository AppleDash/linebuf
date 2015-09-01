all: linebuf

linebuf:
	gcc -c -o linebuf.o linebuf.c -Wall -Wextra
	ar rcs liblinebuf.a linebuf.o

clean:
	rm *.o
	rm *.a