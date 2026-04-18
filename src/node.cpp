#include "node.h"
#include <iostream>

extern std::unordered_map<uint32_t, ASNode> network;

void ASNode::receive(Route route)
{

  for (uint32_t as : route.path) {
    if (as == _asn)
      return;
  }

  if (route.next_hop != _asn) {
    auto it = relatives.find(route.next_hop);
    if (it != relatives.end()) {
      route.recv_from = it->second;
    }
  }

   route.path.insert(route.path.begin(), _asn);


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