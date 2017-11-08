#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

class Graph {
private:
    int V;
    vector<pair<int, pair<int, int> > > edges;
    bool hasNegativeCycle = false;
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void bellmanFord(int src);
};

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({w,{u, v}});
}

void Graph::bellmanFord(int src) {
    vector<int> dist(this->V, INF);
    dist[src] = 0;
    vector<pair<int, pair<int, int> > >::iterator it;
    for (int i = 1; i<this->V; i++) {
        for (it = edges.begin(); it != edges.end(); ++it) {
            int u = it->second.first;
            int v = it->second.second;
            int w = it->first;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (it = edges.begin(); it != edges.end(); ++it) {
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
        if (dist[u] + w < dist[v]) {
            this->hasNegativeCycle = true;
            //return false
        }
    }
}

int main() {
    int V = 5;
    //int E; cuantas aristas
    Graph g(V);
    g.addEdge(0, 1, 7);
    g.bellmanFord(2);
    return 0;
}