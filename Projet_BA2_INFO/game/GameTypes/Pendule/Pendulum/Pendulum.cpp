#pragma once
#ifndef Pendulum_CPP
#define Pendulum_CPP

#include "Pendulum.hpp"
#include <iostream>


void Chrono::reset(int timeAllowed){
	_timeLeft = timeAllowed;
}

int Chrono::getTimeLeft(){
	//std::cout << _timeLeft << std::endl;
	return _timeLeft;
	
}

bool Chrono::isPlayerPlaying(){
	return _isPlayerPlaying;
}

void Chrono::pushChrono(){
	_isPlayerPlaying = true;
}

void Chrono::stopChrono(){
	_isPlayerPlaying = false;
}


void Chrono::setTimeLeft(int newValue){
	_timeLeft = newValue;
}


Pendulum::Pendulum(int timeAllowed): _chrono0Thread(pthread_t()){
	reset(timeAllowed);
}

/*
doit etre appelé quand une partie commence
*/
void Pendulum::run(){
	_gameState = PLAYING;
	std::cout<< this << std::endl;
	pthread_create(&_chrono0Thread, NULL, &Pendulum::checkIfTimeRanOut,  static_cast<void*>(this));
	std::cout << "running";
}



/*
//mais apres comment prevenir l'autre thread share variable ?

todo pour illias/celui qui va implémenter ca avec le jeu d'échec,
vous devez modifier gamestate avec setGameState en lui mettant
GAMEENDED à la fin de la partie si les joueurs ont perdues d'une 
autre manière que par temps la Pendulum. 
*/
void* Pendulum::checkIfTimeRanOut(void *thisptr){
	Pendulum *thisp = static_cast<Pendulum*>(thisptr);
	std::cout << thisp<< std::endl;
	while(thisp->_gameState == PLAYING){  
		for(int i = 0; i < 2; i++){
			while(thisp->_chronos[i].getTimeLeft() > 0 && thisp->_chronos[i].isPlayerPlaying() && thisp->_gameState == PLAYING){
				int start = static_cast<int>(time(NULL));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				int timeElapsed = static_cast<int>(time(NULL))-start;
				thisp->_chronos[i].setTimeLeft(thisp->_chronos[i].getTimeLeft()-timeElapsed);
				//std::cout << i << " " << thisp->_chronos[i].getTimeLeft() << std::endl;
			}

			if(thisp->_chronos[i].getTimeLeft() <= 0){
				if  (i==0){
					thisp->_gameState = PLAYER1OUTOFTIME;
				}
				else if(i == 1){
					thisp->_gameState = PLAYER2OUTOFTIME;
				}
			}
		}
	}
	
	std::cout << "Ran out of time or game was ended" << std::endl;
	
	return nullptr; // enleve le warning // même si pointeur vers 0, nullptr est equivalent à void* ici
	
}

Chrono Pendulum::getChrono(int player){
	return _chronos[player];
}

void Pendulum::reset(int timeAllowed){
	_chronos[0].reset(timeAllowed);
	_chronos[1].reset(timeAllowed);
}

void Pendulum::pushChrono(size_t idx){
	if(idx <= 1)
		_chronos[idx].pushChrono();

}

void Pendulum::setGameState(GameState newState){
	_gameState = newState;
}

GameState Pendulum::getGameState(){
	return _gameState;
}

void Pendulum::stopChrono(size_t idx){
	if(idx <= 1)
		_chronos[idx].stopChrono();
}

//todo  threadsafe code? pas sur si j_uste lire ca doit etre threadsafe aussi
#endif
