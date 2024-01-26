#include "Utils.h"

std::vector<std::vector<int>> Utils::getSceneVector(const char* path) {
	std::ifstream sceneFile;
	std::stringstream contents;
	std::vector<std::vector<int>> data;

	try {
		sceneFile.open(path);
		contents << sceneFile.rdbuf();
		sceneFile.close();
	}
	catch (std::ifstream::failure e){
		throw std::exception(e.what());
	}

	std::string line;
	std::vector<int> elems;

	while (std::getline(contents, line)) {
		std::stringstream ss(line);
		std::string cur;
		while (std::getline(ss, cur, ' ')) {
			elems.push_back(std::stoi(cur));
		}
		data.push_back(elems);
		elems.clear();
	}

	return data;
}