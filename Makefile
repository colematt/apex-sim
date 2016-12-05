CXX=clang++
CCFLAGS = -std=c++11 -g -Wall
CLASS_FILES = \
	cpu.cpp \
	code.cpp \
	data.cpp \
	register.cpp \
	simulate.cpp \
	stage.cpp 

all: apex-sim

apex-sim:
	$(CXX) $(CCFLAGS) main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -vf *~ *.o
	rm -vf apex-sim
