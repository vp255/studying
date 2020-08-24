
//find the distance from every point to every point in V^3 time

template <class Node>
int minDistance(Node i, Node j, Node k) {// where this denotes that we find the min distance from Node i to j, using intermediate nodes of 1 ... j-1
  //two cases

  std::min(  minDistance(i, j, k - 1), minDistance(i, k, k - 1) + minDistance(j, k, k - 1));
  return 0;
}
