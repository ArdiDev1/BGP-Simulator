#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include "node_type.h"
#include "bgp_routing.h"
#include "route.h"

/*
  AS NODE REPRESENTATION
*/

class ASNode
{
public:
	std::unordered_map<uint32_t, Relation> relatives;
	BGPRouter router;
	

	uint32_t _asn;

	ASNode() : _asn(0) {}

	ASNode(uint32_t asn) {
		_asn = asn;
	}

	void receive(Route route);
	void propogate(Route& route);
	bool can_export(Relation from, Relation to);
	void send_to(uint32_t asn, Route& route);

};