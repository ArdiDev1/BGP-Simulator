#pragma once

#include <vector>
#include "node_type.h"

struct Route
{
	uint32_t as_prefix;
	std::vector<uint32_t> path;
	uint32_t next_hop;
	Relation recv_from;
};