#pragma once
#include <unordered_map>
#include "route.h"

class BGPRouter {
public:
	std::unordered_map<uint32_t, Route> table;
	bool compare(Route& a, Route& b);
	int rank(Relation r);

	bool process_route(Route& route);

};