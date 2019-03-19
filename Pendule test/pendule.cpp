#include "pendule.hpp"



void Chrono::reset(int timeAllowed)
{
	_timeLeft = timeAllowed;
}

int Chrono::getTimeLeft()
{
	return _timeLeft;
}

bool Chrono::isPlayerPlaying()
{
	return _isPlayerPlaying;
}

void Chrono::pushChrono()
{
	_isPlayerPlaying = true;
}

void Chrono::stopChrono()
{
	_isPlayerPlaying = false;
}


void Chrono::setTimeLeft(int newValue)
{
	_timeLeft = newValue;
}









Pendule::Pendule(int timeAllowed)
{
	reset(timeAllowed);
}

/*
doit etre appelé quand une partie commence
*/
void Pendule::run()
{
	_gameState = PLAYING;
	pthread_create(&_chrono0Thread, NULL, &Pendule::checkIfTimeRanOut,  static_cast<void*>(this));
	std::cout << "running";
}



/*
//mais apres comment prevenir l'autre thread share variable ?

todo pour illias/celui qui va implémenter ca avec le jeu d'échec,
vous devez modifier gamestate avec setGameState en lui mettant
GAMEENDED à la fin de la partie si les joueurs ont perdues d'une 
autre manière que par temps la pendule. 
*/
void* Pendule::checkIfTimeRanOut(void *thisptr)
{
	Pendule *thisp = (Pendule*)thisptr;
	while(thisp->_gameState == PLAYING)
	{  
		for(int i = 0; i < 2; i++)
		{
			while(thisp->_chronos[i].getTimeLeft() > 0 && thisp->_chronos[i].isPlayerPlaying() && thisp->_gameState == PLAYING)
			{
				int start = static_cast<int>(time(NULL));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				int timeElapsed = static_cast<int>(time(NULL))-start;
				thisp->_chronos[i].setTimeLeft(thisp->_chronos[i].getTimeLeft()-timeElapsed);
				//std::cout << i << " " << thisp->_chronos[i].getTimeLeft() << std::endl;
			}

			if(thisp->_chronos[i].getTimeLeft() <= 0)
			{
				if  (i==0)
					thisp->_gameState = PLAYER1OUTOFTIME;
				else if(i == 1)
					thisp->_gameState = PLAYER2OUTOFTIME;
			}
			
		}
	}

	
	std::cout << "Ran out of time or game was ended" << std::endl;
}

void Pendule::reset(int timeAllowed)
{
	_chronos[0].reset(timeAllowed);
	_chronos[1].reset(timeAllowed);
}

void Pendule::pushChrono(size_t idx)
{
	if(idx <= 1)
		_chronos[idx].pushChrono();

}

void Pendule::setGameState(GameState newState)
{
	_gameState = newState;
}

GameState Pendule::getGameState()
{
	return _gameState;
}

void Pendule::stopChrono(size_t idx)
{
	if(idx <= 1)
		_chronos[idx].stopChrono();
}

//todo  threadsafe code? pas sur si j_uste lire ca doit etre threadsafe aussi