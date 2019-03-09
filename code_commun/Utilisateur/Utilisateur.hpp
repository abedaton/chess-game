
#include <iostream>
#include <string>
#include <vector>

class Utilisateur{
    private:
		std::string login;
		std::string nickname;
		std::vector<Utilisateur*>* amis;
		int victoires;
		int match;
		std::vector<bool>* historique; // bool temporaire plustard struct
		
	public:
        Utilisateur(); //*< Constructor
        ~Utilisateur() noexcept = default; //Destructor
        Utilisateur(const Utilisateur&) noexcept = default;
        Utilisateur& operator= (const Utilisateur&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Utilisateur &c);
        
        std::string get_login() const;
        std::string get_nickname() const;
        std::vector<Utilisateur*>* get_amis() const;
        int get_nb_victoires() const;
        int get_nb_match() const;
        double get_score() const;
        std::vector<bool>* get_historique() const;
        
        void add_match(bool);
        void add_amis(Utilisateur*);
        void remove_amis(Utilisateur*);
        void set_login(std::string);
        void set_nickname(std::string);
        
        bool operator==( const Utilisateur&) const;
        bool operator!=( const Utilisateur&) const;
	
	private:
		void inc_match();
		void inc_victory();
		void add_to_hist(bool); // bool temporaire plustard struct
        
};
