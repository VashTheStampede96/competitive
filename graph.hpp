#ifndef _GRAPH_HASHCODE_HPP_
#define _GRAPH_HASHCODE_HPP_

#include <bits/stdc++.h>
using namespace std;

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

    void discorec(int u, vector<int>& discovery, vector<bool>& vis) {
        vis[u] = true;

        for(auto v: adj[u]) {
            if(not vis[v.label])
                discorec(v.label, discovery, vis);
        }
        
        discovery.push_back(u);
    }

    void component(int u, int leader, vector<bool>& vis, vector<int>& leaders) {
        leaders[u] = leader;
        vis[u] = true;

        for(auto v: adj[u]) {
            if(not vis[v])
                component(v.label, leader, vis, leaders);
        }
    }

    vector<int> assign_leaders(vector<int>& sorted) {
        vector<bool> vis(nodes, false);
        vector<int> leaders(nodes, -1);

        for(auto u: sorted) {
            if(not vis[u])
                component(u, u, vis, leaders);
        }

        return leaders;
    }

public:
    static const int oo;

    Graph(int n, int e, bool dir=false) : nodes(n), edges(e), directed(dir) {
        adj.resize(n);
    }

    // *************************************** ADD EDGE **********************
    void add_edge(int u, T v) {
        adj[u].push_back(v);
        if(not directed)
            adj[v].push_back(u);
    }

    // *************************************** TRANSPOSE *********************
    Graph<T> transpose() {
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

    // *************************************** DIJKSTRA **********************
    vector<int> Dijkstra(int source, int end=-1) {
        vector<int> distance(nodes, oo);
        priority_queue<pair<int,int>> pq;

        pq.push({0, source});
        while(not pq.empty()) {
            int d = -pq.top().first;
            int u = pq.top().second;

            if(d < distance[u]) {
                distance[u] = d;
                
                for(auto v: adj[u]) {
                    if(d+v.weight < distance[v.label])
                        pq.push({-(d+v.weight), v.label});
                }
            }

            if(u == end)
                break;
        }

        return distance;
    }

    // *************************************** BFS ***************************
    vector<int> bfs(int source, int end=-1) {
        vector<bool> vis(nodes, false);
        vector<int> distance(nodes, oo);
        queue<pair<int,int>> q;

        q.push({0, source});
        while(not q.empty()) {
            int d = q.front().first;
            int u = q.front().second;

            if(d < distance[u]) {
                distance[u] = u;

                for(auto v: adj[u]) {
                    if(d+1 < distance[v.label])
                        q.push({d+1, v.label});
                }
            }

            if(u == end)
                break;
        }

        return distance;
    }

    // *************************************** DFS ***************************
    vector<int> dfs() {
        vector<bool> vis(nodes, false);
        vector<int> distance(nodes, oo);

        for(int n=0; n<nodes; ++n) {
            if(not vis[n])
                dfsrec(n, 0, vis, distance);
        }

        return distance;
    }

    // *************************************** DFS+SORTING *******************
    vector<int> dfs_discovery() {
        vector<bool> vis(nodes, false);
        vector<int> discovery;

        for(int u=0; u<nodes; ++u) {
            if(not vis[u])
                discorec(u, discovery, vis);
        }

        return discovery;
    }

    // *************************************** KOSARAJU **********************
    vector<int> Kosaraju() {
        Graph tr = transpose();

        vector<int> disc = dfs_discovery();
        reverse(disc.begin(), disc.end());

        return tr.assign_leaders(disc);
    }

};

template<class T>
const int Graph<T>::  oo = 1e9;

#endif
