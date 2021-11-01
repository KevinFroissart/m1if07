all: maxstab.out

maxstab.out: main.o graph.o nodelist.o utility.o fonctions-algo.o
	gcc -Wextra -Wall -O3 main.o graph.o nodelist.o utility.o fonctions-algo.o -o maxstab.out

main.o: main.c nodelist.h graph.h utility.h
	gcc -Wextra -Wall -O3 -c main.c -o main.o

utility.o: utility.h utility.c
	gcc -Wextra -Wall -O3 -c utility.c -o utility.o

graph.o: graph.h graph.c utility.h
	gcc -Wextra -Wall -O3 -c graph.c -o graph.o

nodelist.o: nodelist.h nodelist.c utility.h
	gcc -Wextra -Wall -O3 -c nodelist.c -o nodelist.o

fonctions-algo.o: fonctions-algo.h fonctions-algo.c nodelist.h
	gcc -Wextra -Wall -O3 -c fonctions-algo.c -o fonctions-algo.o

clean:
	rm *.o

veryclean: clean
	rm *.out

