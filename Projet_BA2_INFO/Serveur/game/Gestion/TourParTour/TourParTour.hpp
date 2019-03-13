
#pragma once
#ifndef TOURPARTOUR_HPP
#define TOURPARTOUR_HPP

#include "../TempsReel/TempsReel.cpp"

class TourParTour: public TempsReel {	
	public:
        TourParTour(BaseChess*); //*< Constructor
        TourParTour() noexcept = default; //*< Constructor
        ~TourParTour() noexcept = default; //Destructor
        TourParTour(const TourParTour&) noexcept = default;
        TourParTour& operator= (const TourParTour&) noexcept = default;
        
        bool execute_step() override;

};
#endif
