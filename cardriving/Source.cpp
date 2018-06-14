#include "Map.hpp"

#define _CRTDBG_MAP_ALOC

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(static_cast<unsigned int>(time(nullptr)));
	std::unique_ptr<Map> map = std::make_unique<Map>();
	getchar();
	return 0;
}