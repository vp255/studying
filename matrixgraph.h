#include <utility>

template <class NodeId, class Weight>
struct Edge {
  NodeId source;
  NodeId destination;
  Weight weight;
};

template <template <class> class Container, class I, class W>
class BiDirectionalMatrixGraph {

public:
  typedef W                  weighttype;
  typedef I                   indextype;

  typedef Container<W> NodeEntry;
  typedef Container<NodeEntry> Matrix;

public:
  
  template <template <class> class Sequence, template <class, class> class Edge, class NodeId>
  BiDirectionalMatrixGraph(const Sequence<Edge<NodeId, W>>& edgelist) {
 
      for (auto&& edge : edgelist) {
          NodeId source   = edge.source;
          NodeId dest     = edge.destination;
          W weight   = edge.weight;
          nodeMatrix_[source][dest] = weight;
          nodeMatrix_[dest][source] = weight;
      }
  }

  const Matrix& matrix() const {
      return nodeMatrix_;
  }

  bool hasElement(const I& a, const I& b) {
    auto a_it = nodeMatrix_.find(a);
    return a_it != nodeMatrix_.end() && a_it->find(b) != a_it->end();
  }

private:

  Matrix nodeMatrix_;

};

// what is a matrix graph?
// each node has a mapping of weights to other nodes
