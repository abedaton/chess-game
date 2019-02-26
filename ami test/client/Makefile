CXX = g++
CXXFLAGS = -std=c++11 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LDFLAGS = -pthread -lsqlite3 


SRCSSERV = srcs/*

INCLUDES = includes

all:
	#$(CXX) $(CXXFLAGS) $(SRCSGAME) $(LDFLAGS) -c
	#$(CXX) $(CXXFLAGS) $(SRCSSERV) -I $(INCLUDES) $(LDFLAGS) -o client_ami_test
	$(CXX) $(CXXFLAGS) $(SRCSSERV) -I $(INCLUDES) $(LDFLAGS) -o client_ami_test
	
.PHONY: clean
clean:
	rm -f *.o client_ami_test
