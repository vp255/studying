#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <memory>

template <class A, class B>
struct MyPair {
  A fst;
  B snd;
};

template <class T>
class Trie {

  struct TrieNode {
    std::unordered_map<T, std::unique_ptr<TrieNode>> children;
    bool isWord = false;
  };


public:
  template <template <class> class C>
  void insert(const C<T>& sequence) {
    TrieNode* t = &root;
    for (const T& e : sequence) {
      auto& children = t->children;

      if (children.find(e) == children.end()) {
        children.emplace(e, std::make_unique<TrieNode>());
      }
      t = children[e].get();
    }
    t->isWord = true;
  }

  template <template <class> class C>
  bool isWord(const C<T>& sequence) {
    TrieNode* t = &root;
    for (const T& e : sequence) {
      auto& children = t->children;
      if (children.find(e) == children.end()) {
        return false;
      }
      t = children[e].get();
    }
    return t->isWord;

  }

  void printAllWords() {
    printAllWords(*std::make_unique<std::vector<T>>().get(), root);
  }
private:

  TrieNode root;

  void printAllWords(std::vector<T>& accum, const TrieNode& trie_node) {
    if (trie_node.isWord) {
      for (const auto& t : accum) {
        std::cout << t << " ";
      }
      std::cout << std::endl;
    }
    for (const auto& [k, uptr] : trie_node.children) {
      accum.push_back(k);
      printAllWords(accum, *uptr.get());
      accum.pop_back();
    }
  }

};

namespace PriorityQueueTests {

void run() {

  std::vector<MyPair<int, std::string>> list = { {5, "koala"}, {5, "bear"}, {4, "bear"}, {4, "koala"} };

  auto comp = []<typename A, typename B>(const MyPair<A,B>& a, const MyPair<A,B>& b) {
    return a.fst == b.fst ? a.snd > b.snd : a.fst > b.fst;
  };

  std::priority_queue<MyPair<int, std::string>, std::vector<MyPair<int, std::string>>, decltype(comp)> pq(list.begin(), list.end(), comp);

  auto dummy = std::vector<int>{1,4,8,5,6};
  auto pq2 = std::priority_queue<int, std::vector<int>, std::less<int>>(dummy.begin(), dummy.end());

  while (!pq.empty()) {
    const auto& mypair = pq.top();
    std::cout << "Element: " << mypair.fst << ", " << mypair.snd << std::endl;
    pq.pop();
  }

  while (!pq2.empty()) {
    const auto& e = pq2.top();
    std::cout << "Element: " << e << std::endl;
    pq2.pop();
  }

  std::priority_queue<MyPair<int, std::string>, std::vector<MyPair<int, std::string>>, decltype(comp)> pq3;
  pq3.push({34, "cd"});
  pq3.push(MyPair<int, std::string>{34, "ef"});

  while (!pq3.empty()) {
    const auto& mypair = pq3.top();
    std::cout << "Element: " << mypair.fst << ", " << mypair.snd << std::endl;
    pq3.pop();
  }

  Trie<char> t;
  t.insert(std::string("apple"));
  t.insert(std::string("appliance"));
  t.insert(std::string("dudeman"));
  t.printAllWords();

}

}
