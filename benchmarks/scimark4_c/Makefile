.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: scimark4 


CC = icc
CFLAGS = -O3 -fno-alias -parallel -par-num-threads=4


CC = gcc
CC = cc
LDFLAGS = 
CFLAGS = -O3 -funroll-all-loops -mtune=prescott
CFLAGS = -O3 -funroll-all-loops   -Wall -pedantic -flto
CFLAGS = -O3 -funroll-all-loops   -Wall -pedantic -flto 
CFLAGS = -O3 -funroll-loops   -Wall -pedantic -flto 
CFLAGS = -O3 -funroll-all-loops   -Wall -pedantic  -ansi
CFLAGS = -O3 -funroll-loops   -Wall -pedantic  -ansi

OBJS = FFT.o kernel.o Stopwatch.o Random.o SOR.o SparseCompRow.o \
	array.o MonteCarlo.o LU.o scimark4.o

scimark4 :  $(OBJS)
	$(CC) $(CFLAGS) -o scimark4  $(OBJS) $(LDFLAGS) -lm 

clean:
	rm $(OBJS) 

wipe:
	rm $(OBJS) scimark4
