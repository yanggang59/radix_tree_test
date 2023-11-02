SRC ?= main.c radix-tree.c

all:
	gcc ${SRC} -o main -O0

clean:
	rm main