CC = gcc
CCFLAGS = -Wall

main: parenthesages
	
	
mymatrix.o:	mymatrix.c mymatrix.h
	${CC} ${CCFLAGS} -c mymatrix.c
	
parenthesages.o:	parenthesages.c
		${CC} ${CCFLAGS} -c parenthesages.c

parenthesages:	mymatrix.o parenthesages.o
	${CC} ${CCFLAGS} parenthesages.o mymatrix.o -o parenthesages
		
clean:
	rm *.o ; rm parenthesages
	
