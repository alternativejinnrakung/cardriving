#include "Map.hpp"

using namespace std;

Map::Map()
{
	initiateFirstCar();
	while (!gameover) {
		engine->setCurrentInput(engine->setInput());
		input = engine->getCurrentInput();
		gameover = engine->summon_world_clock(gameover);
		if (input != static_cast<char>(0)) {
			this->car_addcar();
			this->applyMapData(carquant - 1);
			engine->clearScreen();
			this->drawMap();
		}
		for (int i = 0; i < static_cast<int>(car.size()); i++) {
			this->seekTarget(i);
		}
	}
}

Map::~Map()
{
}


void Map::drawMap() {
	this->drawMapBorder();
	for (int i = 0; i < static_cast<int>(filedata.size()); i++) {
		cout << static_cast<char>(BORDER);
		for (int j = 0; j < static_cast<int>(filedata[i].size()); j++) {
			bool corrected = false;
			for (int k = 0; k < static_cast<int>(car.size()); k++)
			{
				if (j == car[k]->getLocX() && i == car[k]->getLocY()) {
					cout << static_cast<char>(CAR);
					corrected = true;
				}
			}
			if (filedata[i].at(j) == CROSS && !corrected) {
				cout << static_cast<char>(BLOCKAGE);
			}
			else if (filedata[i].at(j) == CIRCLE && !corrected) {
				cout << static_cast<char>(SPACE);
			}
		}
		cout << static_cast<char>(BORDER) << endl;
	}
	this->drawMapBorder();
}

void Map::drawMapBorder() {
	for (int i = -2; i < static_cast<int>(filedata[0].size()); i++) {
		cout << static_cast<char>(BORDER);
	}
	cout << endl;
}

void Map::applyMapData(int car_id) {
	for (int j = 0; j < mapheight; j++) {
		for (int i = 0; i < mapwidth; i++) {
			if (filedata[j].at(i) == CIRCLE && carCrashControl(i,j,car_id)) {
				car[car_id]->setLocX(i);
				car[car_id]->setLocY(j);
				return;
			}
		}
	}
}

void Map::setMapSize(const int& width, const int& height) {
	mapwidth = width;
	mapheight = height;
}

void Map::seekTarget(const int& car_id) {
	currentmovement[car_id] = NO_MOVEMENT;
	engine->gotoxy(static_cast<SHORT>(car[car_id]->getLocX() + 1), static_cast<SHORT>(car[car_id]->getLocY() + 1));
	bool move = this->randomMovement(car[car_id]->getLocX(), car[car_id]->getLocY(), car_id);

	if (move && currentmovement[car_id] != prevmovement[car_id]) {
		prevmovement[car_id] = counter(currentmovement[car_id]);
		car[car_id]->setLocX(target[0]);
		car[car_id]->setLocY(target[1]);
		cout << static_cast<char>(SPACE);
		engine->gotoxy(static_cast<SHORT>(target[0] + 1), static_cast<SHORT>(target[1] + 1));
		cout << static_cast<char>(CAR);
		engine->gotoxy(static_cast<SHORT>(target[0] + 1), static_cast<SHORT>(target[1] + 1));
	}
	else {
		prevmovement[car_id] = NO_MOVEMENT;
	}
}

int Map::counter(const int& movement) {
	if (movement == NO_MOVEMENT) {
		return movement;
	}
	else if (movement == MOVETYPE_RIGHT || movement == MOVETYPE_UP) {
		return (movement + 2);
	}
	else if (movement == MOVETYPE_LEFT || movement == MOVETYPE_DOWN) {
		return (movement - 2);
	}
	else { 
		return movement; 
	}
}

bool Map::randomMovement(const int& x, const int& y, const int& car_id) {
	int random = rand() % 4;
	int movelist[4] = { MOVETYPE_RIGHT, MOVETYPE_UP, MOVETYPE_LEFT, MOVETYPE_DOWN };
	int x_formation[4] = { x+1 ,  x  , x-1 ,  x  };
	int y_formation[4] = {  y  , y+1 ,  y  , y-1 };
	for (int i = 0; i < 4; i++) {
		randomizer[i] = random;
		random++;
		if (random == 4) {
			random = 0;
		}
	}
	return this->movementTypeA(x_formation, y_formation, movelist, randomizer, car_id);
}

bool Map::movementTypeA(const int(&x)[4], const int(&y)[4], const int(&movetype)[4], const int (&at)[4], const int& car_id) {
	if (movementCaseControl(x[at[0]], y[at[0]], movetype[at[0]], car_id) && carCrashControl(x[at[0]], y[at[0]], car_id)) {
		return movementCorrector(x[at[0]], y[at[0]], movetype[at[0]], car_id);
	}
	else if (movementCaseControl(x[at[1]], y[at[1]], movetype[at[1]], car_id) && carCrashControl(x[at[1]], y[at[1]], car_id)) {
		return movementCorrector(x[at[1]], y[at[1]], movetype[at[1]], car_id);
	}
	else if (movementCaseControl(x[at[2]], y[at[2]], movetype[at[2]], car_id) && carCrashControl(x[at[2]], y[at[2]], car_id)) {
		return movementCorrector(x[at[2]], y[at[2]], movetype[at[2]], car_id);
	}
	else if (movementCaseControl(x[at[3]], y[at[3]], movetype[at[3]], car_id) && carCrashControl(x[at[3]], y[at[3]], car_id)) {
		return movementCorrector(x[at[3]], y[at[3]], movetype[at[3]], car_id);
	}
	return false;
}

bool Map::movementCorrector(const int& x, const int& y, const int& movetype, const int& car_id) {
	target[0] = x;
	target[1] = y;
	currentmovement[car_id] = movetype;
	return true;
}

bool Map::movementCaseControl(const int& x, const int& y, const int& movetype, const int& car_id) {
	return (filedata[y].at(x) == CIRCLE && prevmovement[car_id] != movetype);
}

bool Map::carCrashControl(const int& x, const int& y, const int& car_id) {
	bool isFree = true;
	for (int i = 0; i < static_cast<int>(car.size()); i++) {
		if (x == car[i]->getLocX() && y == car[i]->getLocY()) {
			if (i != car_id) {
				isFree = false;
			}
		}
	}
	return isFree;
}

void Map::car_addcar() {
	SpawnPoint<vector<shared_ptr<Car>>> carlist(car);
	carquant++;
	carlist.addCar();
	car = carlist.getCar();
	prevmovement.push_back(NO_MOVEMENT);
	currentmovement.push_back(NO_MOVEMENT);
}

void Map::initiateFirstCar() {
	this->car_addcar();
	filedata = engine->file_reader();
	this->setMapSize(static_cast<int>(filedata[0].size()), static_cast<int>(filedata.size()));
	this->applyMapData(0);
	this->drawMap();
	engine->gotoxy(static_cast<SHORT>(car[0]->getLocX() + 1), static_cast<SHORT>(car[0]->getLocY() + 1));
}