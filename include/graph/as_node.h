#pragma once

#include <vector>

/*
  AS NODE REPRESENTATION
*/

struct ASNode {
	uint32_t as_number;
	std::vector<uint32_t> providers;
	std::vector<uint32_t> customers;
	std::vector<uint32_t> peers;

};