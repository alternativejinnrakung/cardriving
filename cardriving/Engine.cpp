#include "Engine.hpp"



Engine::Engine()
{
	t1 = Clock::now();
	this->readJson();
	this->extractJson();
}


Engine::~Engine()
{
}

bool Engine::summon_world_clock(bool gameover) {
	float diff;
	this->initTime();
	while (true) {
		this->setDeltaTime();
		diff = this->deltaTime();
		if (diff > static_cast<float>(INTERVAL_TIME)) {
			this->resetDeltaTime();
			return false;
		}
		if (gameover) {
			return true;
		}
	}
	return true;
}

char Engine::setInput() {
	if (_kbhit()) {
		int kbinput = _getch();
		return static_cast<char>(kbinput);
	}
	return 0;
}

int Engine::roundup(const double number) {
	if (number > 0) {
		return static_cast<int>(number + 1.0);
	}
	else if (number < 0) {
		return static_cast<int>(number - 1.0);
	}
	else {
		return 0;
	}
}

std::vector<std::string> Engine::file_reader() {
	std::vector<std::string> package;
	std::ifstream textfile(TEXTNAME);
	std::string line;
	std::string token;

	while (getline(textfile, line)) {
		std::stringstream stream(line);
		while (getline(stream, token, ' ')) {
			package.push_back(token);
		}
	}
	PROMISE(!package.empty());
	return package;
}

void Engine::gotoxy(const SHORT& x, const SHORT& y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Engine::initTime() {
	t1 = Clock::now();
}

void Engine::setDeltaTime() {
	t2 = Clock::now();
}

int Engine::getDeltaTimeInMilliseconds() {
	return static_cast<int>(std::chrono::duration_cast<elapsed_resolution>(t2 - t1).count());
}

float Engine::deltaTime() {
	return static_cast<float>(this->getDeltaTimeInMilliseconds() / 1000.0);
}

void Engine::resetDeltaTime() {
	t1 = t2;
}

void Engine::setCurrentInput(char input) {
	currentinput = input;
}

char Engine::getCurrentInput() {
	return currentinput;
}

void Engine::clearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
    )) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
    )) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

void Engine::readJson() {
	std::ifstream ifstream(JSONNAME);
	jsonfile = nlohmann::json::parse(ifstream);
	jsonfile.dump();
}

std::vector<std::string> Engine::extractJson() {
	std::vector<std::string> jsonlist;
	for (nlohmann::json::iterator it = jsonfile.begin(); it != jsonfile.end(); ++it) {
		std::string temp = it.key();
		for (nlohmann::json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {

		}
	}
	return jsonlist;
}