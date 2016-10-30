BOOST_ROOT=/usr/local/boost_1_62_0
CC=g++
CFLAGS=-I $(BOOST_ROOT)
CLASS_FILES = 	cpu.cpp \
								mmu.cpp \
								register.cpp

all: apex-sim

apex-sim:
	$(CC) $(CFLAGS) main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -vf *~ *.o
	rm -vf apex-sim
