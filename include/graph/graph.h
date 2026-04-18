#pragma once

#include <unordered_map>
#include "node.h"
	
constexpr size_t init_cap{ 16 };

class ASGraph {
private:
	std::unordered_map<uint32_t, ASNode> network;

};