#include "Utils.h"

std::unordered_map<Entities::ID, std::vector<std::vector<int>>> 
	Utils::getSceneVector(const char* path) {

	std::ifstream sceneFile;
	std::stringstream contents;

	std::unordered_map<Entities::ID, 
		std::vector<std::vector<int>>> data;

	try {
		sceneFile.open(path);
		contents << sceneFile.rdbuf();
		sceneFile.close();
	}
	catch (std::ifstream::failure e){
		throw std::exception(e.what());
	}

	std::string line;
	std::vector<std::string> elems;

	while (std::getline(contents, line)) {
		std::stringstream ss(line);
		std::string cur;
		while (std::getline(ss, cur, ' ')) {
			elems.push_back(cur);
		}
		std::vector<int> temp = {
				std::stoi(elems[1]),
				std::stoi(elems[2]),
				std::stoi(elems[3])
		};
		if (elems[0] == "Box") {
			data[Entities::Box].push_back(temp);
		}
		else if (elems[0] == "Light") {
			data[Entities::LightSoruce].push_back(temp);
		}
		elems.clear();
	}

	return data;
}