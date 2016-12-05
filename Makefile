CXX=clang++
CXXFLAGS = -std=c++11 -g -Wall
CXX_INCLUDE = -I./srcs
APEX_SRC = srcs
CLASS_FILES = \
	$(APEX_SRC)/cpu.cpp \
	$(APEX_SRC)/code.cpp \
	$(APEX_SRC)/data.cpp \
	$(APEX_SRC)/register.cpp \
	$(APEX_SRC)/simulate.cpp \
	$(APEX_SRC)/stage.cpp

all: apex-sim

apex-sim:
	$(CXX) $(CXX_INCLUDE) $(CXXFLAGS) srcs/main.cpp $(CLASS_FILES) -o apex-sim

.PHONY: clean
clean:
	rm -rvf *~ *.o
	rm -vf apex-sim
