
#pragma once
#ifndef TOURPARTOUR_HPP
#define TOURPARTOUR_HPP

#include "../BaseGameType/BaseGameType.cpp"

class TourParTour: public BaseGameType {	
	public:
        TourParTour(BaseChess*); //*< Constructor
        TourParTour() noexcept = default; //*< Constructor
        ~TourParTour() noexcept = default; //Destructor
        TourParTour(const TourParTour&) noexcept = default;
        TourParTour& operator= (const TourParTour&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(std::string,std::string,bool) override;
        
        using BaseGameType::execute_step;

};
#endif
