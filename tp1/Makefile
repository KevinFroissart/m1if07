all: mincut.out

mincut.out: main.o graph.o nodelist.o utility.o
	gcc -Wextra -Wall -O3 main.o graph.o nodelist.o utility.o -o mincut.out

main.o: main.c nodelist.h graph.h utility.h
	gcc -Wextra -Wall -O3 -c main.c -o main.o

utility.o: utility.h utility.c
	gcc -Wextra -Wall -O3 -c utility.c -o utility.o

graph.o: graph.h graph.c utility.h
	gcc -Wextra -Wall -O3 -c graph.c -o graph.o

nodelist.o: nodelist.h nodelist.c utility.h
	gcc -Wextra -Wall -O3 -c nodelist.c -o nodelist.o

clean:
	rm *.o

veryclean: clean
	rm *.out