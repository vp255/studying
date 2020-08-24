#include <queue>
#include <limits>
#include <iostream>

namespace {

template <class I, class W>
struct PQElement {

I index;
W distance;
I parent;

bool operator<(const PQElement& other) const {
  return distance < other.distance;
}

};

}


template <
           template <class> class Sequence
         , template <template <class> class Container, class I, class W> class HashGraph
         , template <class> class Container
         , class I
         , class W
         >
std::pair<Container<W>, Sequence<I>>
Djikstras(const HashGraph<Container, I, W>& graph, const I& start) {

  Container<W> weights;
  Container<I> parents;
  Container<bool> visited;

  auto infinite_weight = std::numeric_limits<W>::max();
  for (const auto& [index, row] : graph.matrix()) {
      weights[index] = infinite_weight;
      parents[index] = index;
      visited[index] = false;
  }
  weights[start] = W{};

  auto pq = std::priority_queue<PQElement<I,W>, std::vector<PQElement<I,W>>>();
  Sequence<I> path;

  pq.push(PQElement<I,W>{start, W{}, start});

  while (!pq.empty()) {
    const auto& [index, distance, parent] = pq.top();
    std::cout << "visiting index " << index << ", with a distance of " << distance << std::endl;
    if (!visited[index]) {
      visited[index] = true;
      weights[index] = distance;
      parents[index] = parent;
      for (const auto& [adj_idx, edge_weight] : graph.matrix().at(index)) {
        auto new_weight = weights[index] + edge_weight;
        if (weights[adj_idx] == infinite_weight || new_weight < weights[adj_idx]) {
          std::cout << "  line 60 index value: " << index << std::endl;
          pq.push({adj_idx, new_weight, index}); // this call modifies index..???
          std::cout << "  line 62 index value: " << index << std::endl;
        }
      }
    }

    pq.pop();
  }

  for (I i = start; parents[i] != i ; i = parents[i]) {
    std::cout << "pushing parent index " << i << std::endl;
    path.push_back(i);
  }



  return {weights, path};
}
