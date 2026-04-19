#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "node.h"
#include "route.h"

std::unordered_map<uint32_t, ASNode> network;

// ----------------------------
// Print graph
// ----------------------------
void print_graph() {
  std::cout << "\n=== GRAPH ===\n";

  for (auto& [asn, node] : network) {
    std::cout << "AS" << asn << " -> ";

    for (auto& [neighbor, rel] : node.relatives) {
      std::cout << neighbor << "(";

      if (rel == Relation::CUSTOMER) std::cout << "C";
      else if (rel == Relation::PROVIDER) std::cout << "P";
      else std::cout << "Peer";

      std::cout << ") ";
    }

    std::cout << "\n";
  }
}

// ----------------------------
// Print routing tables
// ----------------------------
void print_tables() {
  std::cout << "\n=== ROUTING TABLES ===\n";

  for (auto& [asn, node] : network) {
    std::cout << "AS" << asn << ":\n";

    for (auto& [prefix, route] : node.router.table) {
      std::cout << "  " << prefix << " -> [ ";

      for (uint32_t as : route.path)
        std::cout << as << " ";

      std::cout << "] nh=" << route.next_hop << "\n";
    }
  }
}

// ----------------------------
// MAIN
// ----------------------------
int main() {

  // ----------------------------
  // Build controlled graph
  // ----------------------------
  network.emplace(1, ASNode(1));
  network.emplace(2, ASNode(2));
  network.emplace(3, ASNode(3));
  network.emplace(4, ASNode(4));

  // AS1 connects to AS2 and AS3
  network[1].relatives[2] = Relation::PEER;
  network[2].relatives[1] = Relation::PEER;

  network[1].relatives[3] = Relation::PEER;
  network[3].relatives[1] = Relation::PEER;

  // AS2 -> AS4 is CUSTOMER path (better)
  network[2].relatives[4] = Relation::CUSTOMER;
  network[4].relatives[2] = Relation::PROVIDER;

  // AS3 -> AS4 is PEER path (worse)
  network[3].relatives[4] = Relation::PEER;
  network[4].relatives[3] = Relation::PEER;

  print_graph();

  // ----------------------------
  // Origin route at AS1
  // ----------------------------
  Route r;
  r.as_prefix = 100;
  r.path = {};
  r.next_hop = 1;
  r.recv_from = Relation::CUSTOMER;

  std::cout << "\nStarting propagation...\n";

  network[1].receive(r);

  print_tables();

  // ----------------------------
  // 🔥 DECISION CHECK
  // ----------------------------
  auto& path = network[4].router.table[100].path;

  std::cout << "\nAS4 final path: ";
  for (auto as : path) std::cout << as << " ";
  std::cout << "\n";

  // expected: via AS2 (customer path wins)
  if (path.size() >= 2 && path[1] == 2) {
    std::cout << "PASS (customer path preferred)\n";
  }
  else {
    std::cout << "FAIL (wrong decision)\n";
  }

  return 0;
}