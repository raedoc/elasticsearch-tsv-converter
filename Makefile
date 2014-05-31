all:
	gcc convert.c -o convert

test: all
	./test.sh
