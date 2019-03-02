
#FLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
FLAGS = -std=c++11 -g
LDFLAGS = -pthread -lsqlite3 

CXX= g++
MAIN= main.cpp
OUT= ../cli

all: $(OUT)
	
$(OUT): $(MAIN)
	$(CXX) $(FLAGS) $(MAIN) $(LDFLAGS) -o $(OUT)

.PHONY : clean
clean:
	rm *.o *.out;

