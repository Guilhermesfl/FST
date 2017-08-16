#gcc: main.c FST.c
#	gcc -g -o FST main.c FST.c -Wall -lm -O3 -pg

#gcc: main.c FST.c
#	gcc -g -o FST main.c FST.c -Wall -lm -O3 

gcc: main.c FST.c
	gcc -g -Wall -fopenmp -o FST main.c FST.c -lm -O3 

#gcc: main.c FST.c
#	gcc -g -Wall -fopenmp -o FST main.c FST.c -lm -DDEBUG -O3 

#icc: main.c FST.c
#	icc -g -o FST main.c FST.c -Wall -lm -O3

#icc: main.c FST.c
#	icc -g -o FST main.c FST.c -Wall -fopenmp -lm -O3 -DDEBUG

#gcc: main.c FST.c
#	gcc -g -o FST main.c FST.c -Wall -lm -DDEBUG -O3
