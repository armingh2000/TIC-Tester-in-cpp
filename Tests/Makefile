CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

test : test.o filehandler.o programhandler.o
	gcc -o test $(CFLAGS) test.o filehandler.o programhandler.o
	make clean

test.o : test.c 
	gcc -o test.o -c test.c $(CFLAGS)

filehandler.o : ../FileHandler/filehandler.c
	gcc -o filehandler.o -c ../FileHandler/filehandler.c $(CFLAGS)

programhandler.o : ../ProgramHandler/programhandler.c
	gcc -o programhandler.o -c ../ProgramHandler/programhandler.c $(CFLAGS)

clean:
	rm *.o	

test-result:
	./test > test-result.txt
