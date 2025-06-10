// Program to check the presence of a cycle in an undirected graph using DFS

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool cycleDfs(vector<vector<int>>& adj, int node, int parent, vector<bool>& visited){
        visited[node] = true;

        for(const int adjNode : adj[node]){
                if(!visited[adjNode]){
                        if(cycleDfs(adj, adjNode, node, visited)){
                                return true;
                        }
                }
                else if(adjNode != parent){
                        return true;
                }
        }

        return false;
}

bool hasCycle(vector<vector<int>>& adj, int N){
        vector<bool> visited(N, false);

        for(int i=0 ; i<N ; i++){
                if(!visited[i]){
                        if(cycleDfs(adj, i, -1, visited)){
                                return true;
                        }
                }
        }
        return false;
}

int main(){
        int N,E;
        cout << "Enter the no of nodes : ";
        cin >> N;
        cout << "Enter the no of edges (undirected graph considered) : ";
        cin >> E;
        vector<vector<int>> adj(N);

        cout << "Enter the edges - " << endl;
        for(int i=0 ; i<E ; i++){
                int v1, v2;
                cout << "Edge " << i+1 << " : ";
                cin >> v1 >> v2;
                adj[v1].push_back(v2);
                adj[v2].push_back(v1);
        }

        if(hasCycle(adj, N)){
                cout << "The Graph has a cycle" << endl;
        }
        else{
                cout << "The Graph doesnt have a cycle" << endl;
        }

        return 0;
}
