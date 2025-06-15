// Dijkstra's algorithm implemented using priority-queue to find the shortest path from a src node to all nodes in a graph

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> shortestDist(int src, vector<vector<pair<int,int>>>& adj, int N){
        vector<int> dist(N, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

        dist[src] = 0;

        minHeap.push({0,src});

        while(!minHeap.empty()){
                int new_dist = minHeap.top().first;
                int node = minHeap.top().second;
                minHeap.pop();

                for(auto it : adj[node]){
                        if(new_dist + it.second < dist[it.first]){
                                dist[it.first] = new_dist + it.second;
                                minHeap.push({dist[it.first], it.first});
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
