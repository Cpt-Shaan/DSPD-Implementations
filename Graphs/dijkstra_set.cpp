// Dijkstra's algorithm implemented using set to find the shortest path from a src node to all nodes in a graph

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> shortestDist(int src, vector<vector<pair<int,int>>>& adj, int N){
        vector<int> dist(N, INT_MAX);
        set<pair<int,int>> st;
        dist[src] = 0;

        st.insert({0,src});

        while(!st.empty()){
                auto it = *(st.begin());
                int new_dist = it.first;
                int node = it.second;
                st.erase(it);

                for(auto it : adj[node]){
                        if(new_dist + it.second < dist[it.first]){
                                if(dist[it.first] != INT_MAX){
                                        st.erase({dist[it.first], it.first});
                                }
                                dist[it.first] = new_dist + it.second;
                                st.insert({dist[it.first], it.first});
                        }
                }
        }
        return dist;
}

int main(){
        int N,E;
        cout << "Enter the no of nodes : ";
        cin >> N;
        vector<vector<pair<int,int>>> adj(N);
        cout << "Enter the no of edges (format - v1, v2, weight): ";
        cin >> E;
        cout << "Enter the edges :- " << endl;
        for(int i=0 ; i<E ; i++){
                int v1, v2, w;
                cout << "Edge and Weight " << i+1 << " : ";
                cin >> v1 >> v2 >> w;
                adj[v1].push_back({v2,w});
        }
        int src;
        cout << "Enter the source node : ";
        cin >> src;
        vector<int> dist = shortestDist(src, adj, N);
        cout << "Shortest Distance per node : " << endl;
        for(int i=0 ; i<N ; i++){
                cout << "Node " << i << " Distance - " << dist[i] << endl;
        }
        return 0;
}
