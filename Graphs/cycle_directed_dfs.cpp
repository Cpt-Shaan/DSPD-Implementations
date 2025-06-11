// Program to detect a cycle in a directed graph using DFS

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool isCycle(vector<vector<int>>& adj, vector<bool>& vis, vector<bool>& pathvis, int node){
        vis[node] = true;
        pathvis[node] = true;

        for(const int adjNode : adj[node]){
                if(!vis[adjNode]){
                        if(isCycle(adj, vis, pathvis, adjNode)){
                                return true;
                        }
                }
                else if(pathvis[adjNode]){
                        return true;
                }
        }
        pathvis[node] = false;
        return false;
}

bool isGraphCycle(vector<vector<int>>& adj, int N){
        vector<bool> vis(N, false);
        vector<bool> pathvis(N, false);

        for(int i=0 ; i<N ; i++){
                if(!vis[i]){
                        if(isCycle(adj, vis, pathvis, i)){
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
        vector<vector<int>> adj(N);
        cout << "Enter the no of edges : ";
        cin >> E;
        cout << "Enter the edges :- " << endl;
        for(int i=0 ; i<E ; i++){
                int v1, v2;
                cout << "Edge " << i+1 << " : ";
                cin >> v1 >> v2;
                adj[v1].push_back(v2);
        }

        if(isGraphCycle(adj,N)){
                cout << "The Graph has a cycle" << endl;
        }
        else{
                cout << "The Graph doesnt have a cycle" << endl;
        }

        return 0;

}
