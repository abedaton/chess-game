
//#include <iostream>
//#include <string>
//#include <vector>

#include "Human/Human.cpp"

class Bot: public Player{
	private:
		int counter;
		std::vector<std::string> move_list;
	
	public:
        Bot(std::string); //*< Constructor
        Bot() noexcept = default; //*< Constructor
        virtual ~Bot() noexcept = default; //Destructor
        Bot(const Bot&);
        Bot& operator= (const Bot&) noexcept = default;
        
        std::string next_input() override;  
        void set_moves(std::vector<std::string>);
        
	private:
		virtual std::string get_type_prefix() const override;
};

Bot* make_bot(std::string, std::string, std::string);
