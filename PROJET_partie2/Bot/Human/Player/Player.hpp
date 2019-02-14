
#include <iostream>
#include <string>

#include "../../../AdvTuple/AdvTuple.cpp"

class Player{
    private:
		std::string name;
	
	public:
        Player(std::string); //*< Constructor
        Player() noexcept = default; //*< Constructor
        virtual ~Player() noexcept = default; //Destructor
        Player(const Player&);
        Player& operator= (const Player&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Player &c);
        friend std::ostream& operator<< (std::ostream &s,Player* c);
        
        std::string get_name() const;
        
        virtual std::string next_input() = 0;
        
        bool operator==( const Player&) const;
        bool operator!=( const Player&) const;
        
        bool operator==(const Player*) const;
        bool operator!=(const Player*) const;
        
    private:
		virtual std::string get_type_prefix() const;
};
