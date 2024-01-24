#include "GameEngine.h"
#include <stdexcept>

int main() {
	try {
		GameEngine game;
		game.run();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}