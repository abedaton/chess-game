#pragma once
#ifndef CHESSPIECE_HPP
#define CHESSPIECE_HPP
//#include <iostream>
//#include <vector>
//#include <string>

#include "../Bot/Bot.cpp"

class Decoder;

class Chesspiece{
	private:
		int limite;
		Posi* position;
		std::vector<AdvTuple>* liste_depl;
		std::vector<AdvTuple>* liste_capt;
		Decoder* depl;
		Player* owner;
		Decoder* capt;
		bool updt_needed;
		bool has_moved;
	
	public:
        Chesspiece(); //*< Constructor
        virtual ~Chesspiece() noexcept = default; //Destructor
        Chesspiece(const Chesspiece&);// noexcept = default;
        Chesspiece& operator= (const Chesspiece&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Chesspiece &c);
        friend std::ostream& operator<< (std::ostream &s,Chesspiece* c);
        
        void set_limite(int);
        int get_limite();
        
        virtual void updt();
        void update();
        
        virtual std::string get_name();
        
        bool get_has_moved();
		void set_has_moved(bool);
        
        Posi* get_posi();
        void set_posi(Posi*);
        
        std::vector<AdvTuple>* get_liste_depl();
        void set_liste_depl(std::vector<AdvTuple>*);
        
        std::vector<AdvTuple>* get_liste_capt();
        void set_liste_capt(std::vector<AdvTuple>*);
        
        Decoder* get_depl();
        
        std::vector<std::pair<std::pair<int,int>,AdvTuple>> algo(std::string);
        
        Player* get_owner();
        void set_owner(Player*);
        
        void decoders_update();
        
        bool get_update_needed();
        void set_update_needed(bool);

	private:
		virtual void make_capt_list();
        
};

class Decoder{
    private:
		Chesspiece* pe;
		std::vector<AdvTuple>* liste;
		int limite;
		Posi* posi;
	
	public:
        Decoder(); //*< Constructor
        Decoder(Chesspiece*);
        ~Decoder() noexcept = default; //Destructor
        Decoder(const Decoder&) noexcept = default;
        Decoder& operator= (const Decoder&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Decoder &c);
        
        void set_liste(std::vector<AdvTuple>*);
        
        int get_limite();
        
        void maj(Chesspiece*,std::string);
        std::vector<std::pair<std::pair<int,int>,AdvTuple>> decode();
        
};
#endif
