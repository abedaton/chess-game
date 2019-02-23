/*
#include <iostream>
#include <vector>
*/

#include "../Chesspiece/Chesspiece.cpp"

class Tour: public Chesspiece{
	public:
        Tour(); //*< Constructor
        ~Tour() noexcept = default; //Destructor
        //Tour(const Tour&) noexcept = default;
        Tour& operator= (const Tour&) noexcept = default;
        
        std::string get_name() override;
        
};

class Fous: public Chesspiece{
	public:
        Fous(); //*< Constructor
        ~Fous() noexcept = default; //Destructor
        //Fous(const Fous&) noexcept = default;
        Fous& operator= (const Fous&) noexcept = default;
        
        std::string get_name() override;
};

class Pion: public Chesspiece{
	private:
		std::vector<AdvTuple>* alternative;
		std::string direction;
		
	public:
        Pion(std::string); //*< Constructor
        Pion(); //*< Constructor
        ~Pion() noexcept = default; //Destructor
        Pion(const Pion&);// noexcept = default;
        Pion& operator= (const Pion&) noexcept = default;
        
        void updt() override;
        
        std::string get_name() override;
        
        std::vector<AdvTuple>* get_alternative();
        
        void make_capt_list() override;
};

class Dame: public Chesspiece{
	public:
        Dame(); //*< Constructor
        ~Dame() noexcept = default; //Destructor
        //Dame(const Dame&) noexcept = default;
        Dame& operator= (const Dame&) noexcept = default;
        
        std::string get_name() override;
};

class Roi: public Chesspiece{
	public:
        Roi(); //*< Constructor
        ~Roi() noexcept = default; //Destructor
        //Roi(const Roi&) noexcept = default;
        Roi& operator= (const Roi&) noexcept = default;
        
        std::string get_name() override;
};

class Chevalier: public Chesspiece{
	public:
        Chevalier(); //*< Constructor
        ~Chevalier() noexcept = default; //Destructor
        //Chevalier(const Chevalier&) noexcept = default;
        Chevalier& operator= (const Chevalier&) noexcept = default;
        
        std::string get_name() override;
};

class Fonctionnaire: public Chesspiece{
	public:
        Fonctionnaire(); //*< Constructor
        ~Fonctionnaire() noexcept = default; //Destructor
        //Fonctionnaire(const Fonctionnaire&) noexcept = default;
        Fonctionnaire& operator= (const Fonctionnaire&) noexcept = default;
        
        std::string get_name() override;
};

class Garde: public Chesspiece{
	public:
        Garde(); //*< Constructor
        ~Garde() noexcept = default; //Destructor
        //Garde(const Garde&) noexcept = default;
        Garde& operator= (const Garde&) noexcept = default;
        
        std::string get_name() override;
};

class Faucon: public Chesspiece{
	public:
        Faucon(); //*< Constructor
        ~Faucon() noexcept = default; //Destructor
        //Faucon(const Faucon&) noexcept = default;
        Faucon& operator= (const Faucon&) noexcept = default;
        
        std::string get_name() override;
};

class Chancellier: public Chesspiece{
	public:
        Chancellier(); //*< Constructor
        ~Chancellier() noexcept = default; //Destructor
        //Chancellier(const Chancellier&) noexcept = default;
        Chancellier& operator= (const Chancellier&) noexcept = default;
        
        std::string get_name() override;
};
