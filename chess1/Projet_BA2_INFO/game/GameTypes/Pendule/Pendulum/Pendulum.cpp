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


Pendulum::Pendulum(int timeAllowed, int player): _chrono0Thread(pthread_t()), _player(player){
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



void* Pendulum::checkIfTimeRanOut(void *thisptr){
	Pendulum *thisp = static_cast<Pendulum*>(thisptr);
	while(thisp->_gameState == PLAYING){  
			while(thisp->_chronos[thisp->_player].getTimeLeft() > 0 && thisp->_chronos[thisp->_player].isPlayerPlaying() && thisp->_gameState == PLAYING){
				int start = static_cast<int>(time(NULL));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				int timeElapsed = static_cast<int>(time(NULL))-start;
				thisp->_chronos[thisp->_player].setTimeLeft(thisp->_chronos[thisp->_player].getTimeLeft()-timeElapsed);
				std::cout << "salut :" << thisp->_chronos[thisp->_player].getTimeLeft() << std::endl;
			}

			if(thisp->_chronos[thisp->_player].getTimeLeft() <= 0){
				if  (thisp->_player==0){
					thisp->_gameState = PLAYER1OUTOFTIME;
				}
				else if(thisp->_player == 1){
					thisp->_gameState = PLAYER2OUTOFTIME;
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
