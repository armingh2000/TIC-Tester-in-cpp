CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

test : test.o filehandler.o
	gcc -o test $(CFLAGS) test.o filehandler.o
	make clean

test.o : test.c 
	gcc -o test.o -c test.c $(CFLAGS)

filehandler.o : ../FileHandler/filehandler.c
	gcc -o filehandler.o -c ../FileHandler/filehandler.c $(CFLAGS)

clean:
	rm *.o	
