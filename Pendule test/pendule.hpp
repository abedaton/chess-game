#ifndef PENDULE_HPP
#define PENDULE_HPP

#include <vector>
#include <chrono>
#include <ctime> 
#include <thread>
#include <iostream>


enum GameState : int {
    INACTIVE, PLAYING, PLAYER1OUTOFTIME, PLAYER2OUTOFTIME, GAMEENDED
};


class Chrono
{
public:
	//Chrono(int time_allowed); //temps en secondes

	void reset(int timeAllowed);
	void pushChrono();   //au début d'un tour 
	void stopChrono();   //quand le joueur a fini de jouer

	void setTimeLeft(int newValue);
	bool isPlayerPlaying();
	int  getTimeLeft();
private:
	bool _isPlayerPlaying = false;
	int  _timeLeft = 0;   //temps en seconde
};





class Pendule
{
public:
	Pendule(int timeAllowed);
	static void* checkIfTimeRanOut(void *thisptr); //ca doit etre void* ?
	void run();
	void setGameState(GameState newState);
	GameState getGameState();

	void pushChrono(size_t idx);
	void stopChrono(size_t idx);
	

	void reset(int timeAllowed);

private:
//public:
    Chrono _chronos[2];
private:
    pthread_t _chrono0Thread;
    GameState _gameState = INACTIVE; //doit aussi etre modifié si le joueur gagne par echec et mat ou si la partie se termine d'une autre maniere
};






#endif