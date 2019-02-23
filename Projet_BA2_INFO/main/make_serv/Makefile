CXX = g++
CXXFLAGS = -std=c++11 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LDFLAGS = -pthread -lsqlite3 

SRCSDIRS = ../../Serveur/srcs/*

all:
	$(CXX) $(CXXFLAGS) $(SRCSDIRS) $(LDFLAGS) -o serv

.PHONY: clean
clean:
	rm -f *.o serv
