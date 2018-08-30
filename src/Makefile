#FST: main.c FST.c
#	gcc	-g -o FST FST.c main.c -lm -DDEBUG

#FST: main.c FST.c
#	gcc	-g -o FST FST.c main.c -fopenmp -lm -Wall -DDEBUG

#FST: main.c FST.c
#	gcc	-g -o FST FST.c main.c -fopenmp -lm -Wall 

FST: main.c FST.c
	/usr/local/opt/llvm/bin/clang -O3 -o FST FST.c main.c -fopenmp -L/usr/local/opt/llvm/lib -lm -Wall

#FST_PHI: main.c FST.c
#       icc -o FST_PHI FST.c main.c -mmic -fopenmp -O3
