#include "node.h"
#include <iostream>

extern std::unordered_map<uint32_t, ASNode> network;

void ASNode::receive(Route& route)
{
  for (uint32_t as : route.path) {
    if (as == _asn) {
      return;
    }
  }

  route.path.push_back(_asn);

  if (!router.process_route(route)) {
    return; 
  }

  propogate(route);
}

void ASNode::propogate(Route& route)
{
  for (auto& [neighbor_asn, relation] : relatives) {

    if (neighbor_asn == route.next_hop)
      continue;

    if (!can_export(route.recv_from, relation))
      continue;

    Route out = route;
    out.next_hop = _asn;

    send_to(neighbor_asn, out);
  }
}

bool ASNode::can_export(Relation from, Relation to)
{
  if (from == Relation::CUSTOMER)
    return true;

  return to == Relation::CUSTOMER;
}

void ASNode::send_to(uint32_t asn, Route& route)
{
  network.at(asn).receive(route);
}