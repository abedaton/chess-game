
#include <iostream>
#include <string>
#include <vector>

#include "Player/Player.cpp"

class Human: public Player{
	public:
        Human(std::string); //*< Constructor
        Human() noexcept = default; //*< Constructor
        virtual ~Human() noexcept = default; //Destructor
        Human(const Human&);
        Human& operator= (const Human&) noexcept = default;
        
        virtual std::string next_input() override;
        
	private:
		virtual std::string get_type_prefix() const override;
};
