gcc: main.c FST.c
	gcc -g -o FST main.c FST.c -Wall -lm -O3

#icc: main.c FST.c
#	icc -g -o FST main.c FST.c -Wall -lm -O3

#gcc: main.c FST.c
#	gcc -g -o FST main.c FST.c -Wall -lm -DDEBUG
