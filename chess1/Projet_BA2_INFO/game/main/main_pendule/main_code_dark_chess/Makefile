
FLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override

THREADS_FLAGS = -pthread

CXX= g++
MAIN= main_dark.cpp
OUT= CalTest.out

all: $(OUT)
	
$(OUT): $(MAIN)
	$(CXX) $(THREADS_FLAGS) $(FLAGS) $(MAIN) -o $(OUT)

.PHONY : clean
clean:
	rm *.o *.out;
