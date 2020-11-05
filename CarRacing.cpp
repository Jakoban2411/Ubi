#include<iostream>
#include<vector>
#include<Windows.h>
#include<ctime>
#include<conio.h>
#include "CarRacing.h"
#define RIGHTLIMIT 100
#define LEFTLIMIT 0
#define LEFTLANE 25
#define RIGHTLANE 75
#define PICKUPINTERVAL 10000
bool PlacePlayer(std::vector<char>& Textures, int& currentPosition, int moveBy,float& multiplier)
{
	if (Textures[currentPosition + moveBy] == '|' || Textures[currentPosition + moveBy] == '0' || Textures[currentPosition]=='|'|| Textures[currentPosition] == '0')
		return false;
	if (Textures[currentPosition + moveBy] == 'x' || Textures[currentPosition] == 'x')
		multiplier += 0.2f;
	Textures[currentPosition] = ' ';
	Textures[currentPosition + moveBy] = '*';
	currentPosition += moveBy;
	return true;
}
void GetInput(int& displacement)
{
	if (GetAsyncKeyState(65))
		displacement = -1;
	if (GetAsyncKeyState(68))
		displacement = 1;
}

void Render(const std::vector<char> &Textures)
{
	std::cout << "\n \t";
	for (size_t index = 0; index < Textures.size(); index++)
	{
		switch (Textures[index])
		{
		case '*':
			std::cout << "\033[32m" << Textures[index] ;
			break;
		case '|':
			std::cout << "\033[31m" << Textures[index] ;
			break;
		case '0':
			std::cout << "\033[31m" << Textures[index] ;
			break;
		default:
			std::cout << "\033[34m" << Textures[index];
			break;
		}
	}
}
void RandomPickup(std::vector<char>& Textures, clock_t& _lastPickup, int _CurrentLeftLane)
{
	clock_t PickupCheckat = clock();
	if (PickupCheckat - _lastPickup > PICKUPINTERVAL)
	{
		double prob = (rand() % 100) && 11;
		int UnrestricedLocation = rand()*prob;
		int Location = UnrestricedLocation % 50;
		Textures[_CurrentLeftLane + Location] = 'x';
		_lastPickup = PickupCheckat;
	}
}
void MoveRoad(std::vector<char>& Textures,int& _MoveBy,int &_CurrentLeftLane, int& _CurrentRightLane,int _leftObstacles,int _rightObstacles)
{
	if (_CurrentRightLane + _MoveBy == RIGHTLIMIT)
		_MoveBy = -1;
	if (_CurrentLeftLane + _MoveBy == LEFTLIMIT)
		_MoveBy = 1;
	Textures[_CurrentLeftLane] = ' ';
	Textures[_CurrentRightLane] = ' ';
	Textures[_CurrentLeftLane + _leftObstacles] = ' ';
	Textures[_CurrentRightLane + _rightObstacles] = ' ';
	_CurrentLeftLane += _MoveBy;
	_CurrentRightLane += _MoveBy;
	int Move1 = _leftObstacles & 1;
	Textures[_CurrentLeftLane +Move1] = '0';
	Textures[_CurrentLeftLane + _leftObstacles] = '0';
	Textures[_CurrentRightLane - Move1] = '0';
	Textures[_CurrentRightLane + _rightObstacles] = '0';
	Textures[_CurrentLeftLane] = '|';
	Textures[_CurrentRightLane] = '|';
}
void Update(bool& gameLoop, std::vector<char>& Textures,
	int& leftObstacles,int& rightObstacles, 
	int& currentposition, int displacement,
	int& _MoveBy, int& _CurrentLeftLane, int& _CurrentRightLane,
	int& multideltatime, float& scoremultiplier,
	clock_t& lastmultiplied, 
	clock_t &LastPickup)
{
	gameLoop = PlacePlayer(Textures, currentposition, displacement,scoremultiplier);
	if (clock() - lastmultiplied > multideltatime && scoremultiplier<11)
	{
		scoremultiplier++;
		multideltatime = multideltatime << 1;
		std::cout << "\n \n  Score multiplier active: " << scoremultiplier << "x. Press any key to continue. Game will continue after 5 seconds";
		leftObstacles++;
		rightObstacles--;
		Textures[_CurrentLeftLane + leftObstacles] = '0';
		Textures[_CurrentRightLane + rightObstacles] = '0';
		Sleep(5000);
		lastmultiplied = clock();
	}
	MoveRoad(Textures, _MoveBy,_CurrentLeftLane,_CurrentRightLane,leftObstacles,rightObstacles);
	RandomPickup(Textures,LastPickup,_CurrentLeftLane);
}
int main()
{
	std::vector<char> Textures(200,32);
	int currentposition = 45;
	Textures[currentposition] = '*';
	Textures[LEFTLANE] = '|';
	Textures[RIGHTLANE] = '|';
	bool gameLoop = true;
	int displacement = 0;
	uint32_t score = 0;
	int multideltatime = 10000;
	float scoremultiplier = 1;
	clock_t starttime = clock();
	clock_t lastmultiplied = starttime;
	int _MoveBy = -1;
	double FPS = 60;
	int _CurrentLeftLane = LEFTLANE;
	int _CurrentRightLane = RIGHTLANE;
	int _leftObstacles = 0;
	int _rightObstacles = 0;
	clock_t LastPickup = 0;
	std::cout << "\n Enter screen refresh rate(default used 60,max 240): ";
	std::cin >> FPS;
	if (FPS > 240)
	{
		std::cout << "\n Say sike right now(Reset FPS to 60,play fair next time)";
		FPS = 60;
	}
	std::cout << "\n Current FPS taken at " << FPS;
	std::cout << "\n A to go left, D to go right. You will automatically move towards the directrion of your last pressed direction.Control the direction to stop colliding with 0 and |";
	std::cout << "\n Once game starts, your score is calculated based on the time you survive. Please disable blue light filters like f.lux \n";
	std::cout << "\n As you progress your score will be multiplied based on the multiplier shown. The game will introduce new obstacles at this point to restrict your space \n";
	std::cout << "\n There is also a X Pickup which will boost your multiplier \n";
	std::cout << "\n These obstacles will only spawn at the edges near the boundary.  \n";
	std::cout << "\n Press any key to start \n";
	std::cout << "\n Here's to hopefully a GG \n";
	_getch();
	srand(starttime);
	clock_t newframetick;
	clock_t prevframetick = clock();
	long double elapsed = 0;
	long double FrameUpateInterval = (1.0 / FPS) * 1000;
	while (gameLoop)
	{
		newframetick = clock();
		elapsed = newframetick-prevframetick;
		if (elapsed>FrameUpateInterval)
		{
			GetInput(displacement);
			Update(gameLoop, Textures,
				_leftObstacles,_rightObstacles, 
				currentposition, displacement, 
				_MoveBy, _CurrentLeftLane, _CurrentRightLane,
				 multideltatime, scoremultiplier, 
				lastmultiplied, LastPickup);
			Render(Textures);
			prevframetick = newframetick;
		}
	}
	score = clock() - starttime;
	std::cout << "\n High Score: " << score*scoremultiplier;
	_flushall();
	Sleep(5000);
}

