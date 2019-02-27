
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

#include "../Plateau/Plateau.cpp"

template <class Type>
class MyIterator : public std::iterator<std::input_iterator_tag, int>{
	private:
		Plateau* plateau;
	
	public:
		MyIterator(Plateau* plat) : plateau(plat) {}
		MyIterator(const MyIterator<Type>& mit) : plateau(mit.plateau) {}
		
		~MyIterator() noexcept = default; //Destructor
		
		MyIterator<Type>& operator++();
		MyIterator<Type> operator++(int);
		
		bool operator==(const MyIterator<Type>& oth) const {return plateau==oth.plateau;}
		bool operator!=(const MyIterator<Type>& oth) const {return not(*this==oth);}
		
		Plateau& operator*() {return *plateau;}
};

template <class Type>
MyIterator<Type>& MyIterator<Type>::operator++(){
	this->plateau = this->plateau->next();
	return *this;
	}

template <class Type>
MyIterator<Type> MyIterator<Type>::operator++(int i) {
	if (i != 0){
		MyIterator<Type> tmp(*this);
		int j=0;
		while (j < i){
			std::cout << j << std::endl;
			this->operator++();
			j+=1;
		}
		return tmp;
	}
	
	else{return this->operator++();}		
}
