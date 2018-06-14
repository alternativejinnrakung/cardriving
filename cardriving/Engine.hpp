#pragma once
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include <conio.h>
#include <assert.h>
#include <windows.h>

#include "json.hpp"

#define REQUIRE(condition) assert(condition)
#define PROMISE(condition) assert(condition)

typedef std::chrono::high_resolution_clock Clock;
using elapsed_resolution = std::chrono::milliseconds;
using mytimepoint = std::chrono::steady_clock::time_point;

class Engine
{
private:
	const double INTERVAL_TIME = 0.05;
	const std::string TEXTNAME = "drawnmap.txt";
	const std::string JSONNAME = "car.json";
	mytimepoint t1, t2;
	char currentinput = static_cast<char>(0);
	nlohmann::json jsonfile;
public:
	Engine();
	~Engine();
	bool summon_world_clock(bool gameover);
	char setInput();
	int roundup(const double number);
	std::vector<std::string> file_reader();
	void gotoxy(const SHORT& x, const SHORT& y);
	void initTime();
	void setDeltaTime();
	int getDeltaTimeInMilliseconds();
	float deltaTime();
	void resetDeltaTime();
	void setCurrentInput(char input);
	char getCurrentInput();
	void clearScreen();
	void readJson();
	std::vector<std::string> extractJson();
};

