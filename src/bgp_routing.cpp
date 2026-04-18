#include "bgp_routing.h"

bool BGPRouter::process_route(Route& route)
{
  auto it = table.find(route.as_prefix);

  if (it == table.end()) {
    table[route.as_prefix] = route;
    return true;
  }

  Route& current = it->second;

  if (compare(route, current)) {
    current = route;
    return true;
  }

  return false;
}

bool BGPRouter::compare(Route& a, Route& b)
{
  if (a.recv_from != b.recv_from)
    return rank(a.recv_from) > rank(b.recv_from);

  if (a.path.size() != b.path.size())
    return a.path.size() < b.path.size();

  return false;
}

int BGPRouter::rank(Relation r)
{
  if (r == Relation::CUSTOMER) return 3;
  if (r == Relation::PEER) return 2;
  return 1;
}