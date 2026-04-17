#include <iostream>
#include "as_graph.h"

ASGraph::ASGraph()
{
	as_graph.reserve(init_cap);
	num_nodes = 0;
}

void ASGraph::AddEdge(ASNode& node, size_t src)
{
	as_graph[src].push_back(node);
}

void ASGraph::PrintASGraph()
{
	for (auto i : as_graph) {
		std::cout << i << "\n";
	}
}