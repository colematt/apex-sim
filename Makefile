export CXXFLAGS = -std=c++11 -g -Wall -I../include

all: apex-sim

apex-sim: libdir
	$(CXX) $(CXXFLAGS) -o $@ $(wildcard lib/*.o)

.PHONY: libdir
libdir:
	$(MAKE) -e -C lib

.PHONY: clean
clean:
	$(MAKE) -C lib clean
	$(RM) apex-sim