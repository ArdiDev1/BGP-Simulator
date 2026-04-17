#pragma once

#include <vector>
#include "relative.h"
/*
  AS NODE REPRESENTATION
*/



struct ASNode {
	uint32_t as_number;

	std::vector<Relative> relatives;
};