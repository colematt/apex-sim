CXX=clang++
CCFLAGS = -std=c++11 -g -Wall
CLASS_FILES = 	cpu.cpp \
	code.cpp \
	register.cpp \
	data.cpp \
	stage.cpp \
	simulate.cpp

all: apex-sim

apex-sim:
	$(CC) $(CCFLAGS) main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -vf *~ *.o
	rm -vf apex-sim
