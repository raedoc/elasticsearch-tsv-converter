all:
	gcc convert.c -o convert
	gcc generate.c -o generate

test: all
	./test.sh

benchmark: test
	time ./benchmark.sh 10000

clean:
	rm convert
	rm generate
	rm -rf benchmark/
