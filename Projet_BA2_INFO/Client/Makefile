CXX = g++
#CXXFLAGS = -std=c++11 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
CXXFLAGS = -std=c++11 
LDFLAGS = -pthread -lsqlite3 

IDIRC = includes/
SRCSDIRC = srcs/*

all:
	$(CXX) $(CXXFLAGS) $(SRCSDIRC) -I $(IDIRC) $(LDFLAGS) -o ../cli

.PHONY: clean

clean:
	rm -f *.o
	rm -f cli
