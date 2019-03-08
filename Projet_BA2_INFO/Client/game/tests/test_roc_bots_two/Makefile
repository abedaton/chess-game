
FLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override

CXX= g++
MAIN= test_roc_bots_two.cpp
OUT= CalTest.out

all: $(OUT)
	
$(OUT): $(MAIN)
	$(CXX) $(FLAGS) $(MAIN) -o $(OUT)

.PHONY : clean
clean:
	rm *.o *.out;
