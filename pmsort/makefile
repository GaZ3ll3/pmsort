CC=g++

all:
	${CC} -c -Wall pmsort.cpp pmsort.h -fopenmp
	${CC} -c -Wall main.cpp -fopenmp
	${CC} -o main main.o pmsort.o -fopenmp

	./main

clean:
	rm -rf *.o main *.gch
