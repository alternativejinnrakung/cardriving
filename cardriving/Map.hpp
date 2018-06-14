#pragma once
#include "Engine.hpp"
#include "Spawner.hpp"

#include <iostream>
#include <vector>
#include <memory>

class Map
{
private:
	const enum MAP {
		CROSS = 'x',
		CIRCLE = 'o'
	};
	const enum MOVEMENT {
		NO_MOVEMENT = -1,
		MOVETYPE_RIGHT,
		MOVETYPE_UP,
		MOVETYPE_LEFT,
		MOVETYPE_DOWN
	};

	const int BORDER = 178;
	const int BLOCKAGE = 176;
	const int SPACE = 255;
	const int CAR = 229;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	std::vector<std::shared_ptr<Car>> car;
	std::vector<std::string> filedata;
	int mapwidth;
	int mapheight;
	bool gameover = false;
	int target[2] = { 0,0 };
	std::vector<int> currentmovement;
	std::vector<int> prevmovement;
	int randomizer[4] = {0,0,0,0};
	int carquant = 0;
	char input = static_cast<char>(0);
public:
	Map();
	~Map();
	void drawMap();
	void drawMapBorder();
	void applyMapData(int car_id);
	void setMapSize(const int& width, const int& height);
	void seekTarget(const int& car_id);
	int counter(const int& movement);
	bool randomMovement(const int& x, const int& y, const int& car_id);
	bool movementTypeA(const int (&x)[4], const int (&y)[4], const int(&movetype)[4], const int (&at)[4], const int& car_id);
	bool movementCorrector(const int& x, const int& y, const int& movetype, const int& car_id);
	bool movementCaseControl(const int& x, const int& y, const int& movetype, const int& car_id);
	bool carCrashControl(const int& x, const int& y, const int& car_id);
	void car_addcar();
	void initiateFirstCar();
};