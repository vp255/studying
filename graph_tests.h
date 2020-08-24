#include "matrixgraph.h"
#include <vector>
#include <unordered_map>
#include "djikstras.h"
#include <iostream>

namespace GraphTests {

template <class V>
using HashMapIndexedOnInt = std::unordered_map<int, V>;

void run() {
  std::vector<Edge<int, int>> edgelist = {  {0,1,4}
                                         ,  {1,2,8}
                                         ,  {0,7,8}
                                         ,  {1,7,11}
                                         ,  {7,8,7}
                                         ,  {7,6,1}
                                         ,  {2,8,2}
                                         ,  {6,8,6}
                                         ,  {2,3,7}
                                         ,  {6,5,2}
                                         ,  {5,2,4}
                                         ,  {3,5,14}
                                         ,  {3,4,9}
                                         ,  {4,5,10}
                                         };
  auto graph2 = BiDirectionalMatrixGraph<HashMapIndexedOnInt, int, int>(edgelist);

  auto&& [weights, sequence] = Djikstras<std::vector>(graph2, 0);
  for (const auto& [idx, weight] : weights) {
    std::cout << "idx: " << idx << ", weight: " << weight << std::endl;
  }
  for (const auto& node : sequence) {
    std::cout << "node: " << node << std::endl;
  }

}

}
