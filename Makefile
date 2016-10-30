CC=g++
CLASS_FILES = 	cpu.cpp \
								mmu.cpp \
								register.cpp

all: apex-sim

apex-sim:
	$(CC) main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -vf *~ *.o
	rm -vf apex-sim
