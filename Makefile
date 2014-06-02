all:
	gcc convert.c -o convert

test: all
	./test.sh

benchmark: all
	./benchmark.sh 10000
