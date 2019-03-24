CC = gcc
CFLAGS = -g -std=gnu99 -Wall
CUNIT = -L/home/ff/cs61c/cunit/install/lib -I/home/ff/cs61c/cunit/install/include -lcunit
ASSEMBLER_FILES = src/utils.c src/tables.c src/translate_utils.c src/translate.c

all: assembler

check: test-assembler

assembler: clean
	$(CC) $(CFLAGS) -o assembler assembler.c $(ASSEMBLER_FILES)

test-assembler: clean
	$(CC) $(CFLAGS) -DTESTING -o test-assembler test_assembler.c $(ASSEMBLER_FILES) $(CUNIT)
	./test-assembler

clean:
	rm -f *.o assembler test-assembler core
	rm -f out/*.int out/*.out
	rm -f log/*.txt

test:
	sh test.sh

vm:
	docker run -it --name valgrind -v $(CURDIR):/home/berkeley/cs61c \
		-w /home/berkeley/cs61c hexincloud/cs61c

stop_vm:
	docker rm valgrind