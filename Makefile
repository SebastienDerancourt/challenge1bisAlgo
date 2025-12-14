all: parenthesages

parenthesages: parenthesages.o mymatrix.o
	gcc -o parenthesages parenthesages.o mymatrix.o

parenthesages.o: parenthesages.c mymatrix.h
	gcc -c parenthesages.c -Wall

mymatrix.o: mymatrix.c mymatrix.h
	gcc -c mymatrix.c -Wall

clean:
	rm -f *.o parenthesages