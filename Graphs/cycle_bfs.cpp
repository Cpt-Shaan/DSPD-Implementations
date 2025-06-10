#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool cycleGraph(vector<vector<int>>& adj, int node, vector<bool>& visited){
        queue<pair<int,int>> q;
        q.push({node,-1});

        while(!q.empty()){
                int front_node = q.front().first;
                int parent = q.front().second;
                q.pop();
                visited[front_node] = true;

                for(int adjNode : adj[front_node]){
                        if(!visited[adjNode]){
                                q.push({adjNode, front_node});
                        }
                        else if(adjNode != parent){
                                return true;
                        }
                }
        }

        return false;
}

bool hasCycle(vector<vector<int>>& adj, int N){
        vector<bool> visited(N, false);
        for(int i=0 ; i<N ; i++){
                if(!visited[i]){
                        bool val = cycleGraph(adj, i, visited);
                        if(val){
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
