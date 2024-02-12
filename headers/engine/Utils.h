#ifndef UTILS_H
#define UTILS_H

#include "EntityTags.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

namespace Utils {
	std::unordered_map<Entities::ID,std::vector<std::vector<int>>> getSceneVector(const char*);
}

#endif // !UTILS_H

