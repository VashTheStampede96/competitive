#include <bits/stdc++.h>

template<class T>
class Graph {
private:
    int nodes, edges;
    bool directed;
    vector<vector<T>> adj;

    void dfsrec(int u, int d, vector<bool>& vis, vector<int> dist) {
        vis[u] = true;
        dist[u] = d;

        for(auto v: adj[u]) {
            if(not vis[v.label])
                dfsrec(v.label, d+1, vis, dist);
        }
    }

public:
    static const int oo;

    Graph(int n, int e, bool dir=false) : nodes(n), edges(e), directed(dir) {
        adj.resize(n);
    }

    void add_edge(int u, T v) {
        adj[u].push_back(v);
        if(not directed)
            adj[v].push_back(u);
    }

    Graph transpose() {
        Graph tr(nodes, edges, directed);

        for(int u=0; u<nodes; ++u) {
            for(auto v: adj[u]) {
                auto edge = v;
                edge.label = u;
                tr.add_edge(v.label, edge, directed);
            }
        }

        return tr;
    }

    vector<int> Dijkstra(bool w, int source, int end=-1) {
        vector<int> distance(nodes, oo);
        if(w)
            priority_queue<pair<int,int>> q;
        else
            queue<pair<int, int>> q;

        pq.push({0, source});
        while(!pq.empty()) {
            int d;
            if(w)
                d = -pq.top().first;
            else
                d = -pq.front().first;
            int u = pq.top().second;

            if(d < distance[u]) {
                distance[u] = d;
                
                for(auto v: adj[u]) {
                    if(d+v.weight < distance[v.label])
                        pq.push({-(d+weight), v.label});
                }
            }

            if(u == end)
                break;
        }

        return distance;
    }

    vector<int> dfs() {
        vector<bool> vis(nodes, false);
        vector<int> distance(nodes, oo);

        for(int n=0; n<nodes; ++n) {
            if(not vis[n])
                dfsrec(n, 0, vis, distance);
        }

        return distance;
    }

    vector<int> Kusaraju() {
        Graph tr = transpose();

        vector<int> dfs1 = dfs();
        vectorGraph tr = transpose();
        
        vector<int> dfs1 = dfs();
    }

};

Graph:: const int oo = 1e9;
