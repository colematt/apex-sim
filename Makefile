CC=g++ -std=c++11
CLASS_FILES = 	cpu.cpp \
	code.cpp \
	register.cpp \
	data.cpp \
	instruction.cpp
	
all: apex-sim

apex-sim:
	$(CC) main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -vf *~ *.o
	rm -vf apex-sim
