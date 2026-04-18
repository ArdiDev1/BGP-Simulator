#include <iostream>
#include <unordered_map>
#include "node.h"
#include "route.h"

std::unordered_map<uint32_t, ASNode> network;

int main() {

  network.emplace(1, ASNode(1));
  network.emplace(2, ASNode(2));
  network.emplace(3, ASNode(3));

  network[2].relatives[1] = Relation::PROVIDER;
  network[1].relatives[2] = Relation::CUSTOMER;

  network[3].relatives[2] = Relation::PROVIDER;
  network[2].relatives[3] = Relation::CUSTOMER;

  Route r;
  r.as_prefix = 100;
  r.path = {};
  r.next_hop = 3;
  r.recv_from = Relation::CUSTOMER;

  std::cout << "Starting propagation from AS3...\n";

  network[3].receive(r);

  return 0;
}