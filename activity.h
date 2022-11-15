#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: Damariz Licea
// Date:  15/11/2022
// =========================================================

#include "ugraph.h"

template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph,
    std::set<Vertex> &reached, std::stack<Vertex> &TS) {

reached.insert(v);
for (auto u : graph->getConnectionFrom(v)) {
  if (reached.find(u) == reached.end()) {
    dfs2(u, graph, reached, TS);
  }
}
TS.push(v);
}

template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
      std::set<Vertex> reached;
    std::stack<Vertex> TS;
    for (auto v : graph->getVertexes()) {
      if (reached.find(v) == reached.end()) {
        dfs2(v, graph, reached, TS);
      }
    }
    std::stringstream aux;
    while (!TS.empty()) {
      aux << TS.top() << " ";
      TS.pop();
    }
    return aux.str();
}

template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {

  std::set<Vertex> reached;
  std::map<Vertex, int> color;
  std::queue<Vertex> Q;
  
  for (auto v : graph->getVertexes()) {
    if (reached.find(v) == reached.end()) {
      Q.push(v);
      color[v] = 0;
      reached.insert(v);
      while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (auto w : graph->getConnectionFrom(u)) {
          if (reached.find(w) == reached.end()) {
            Q.push(w);
            reached.insert(w);
            color[w] = 1 - color[u];
          } else {
            if (color[w] == color[u]) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph,
  std::set<Vertex> &reached, Vertex parent) {

  reached.insert(v);
  for (auto u : graph->getConnectionFrom(v)) {
    if (reached.find(u) == reached.end()) {
      if (isCyclic(u, graph, reached, v)) {
        return true;
      }
    } else {
      if (u != parent) {
        return true;
      }
    }
  }
  return false;

}

template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {


  std::set<Vertex> reached;
  Vertex vertex = graph->getVertexes()[0];
  if (isCyclic(vertex, graph, reached, NULL)) {
    return false;
  }
  for (auto v : graph->getVertexes()) {
    if (reached.find(v) == reached.end()) {
      return false;
    }
  }
  return true;

}

#endif /* ACTIVITY_H */
