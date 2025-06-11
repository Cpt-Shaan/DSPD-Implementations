// Topological Sort of a Graph using BFS (Kahn's Algorithm)

#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

vector<int> topoSort(vector<vector<int>>& adj, int N){
        vector<int> inDegree(N,0);
        vector<int> ans;
        for(int i=0 ; i<N ; i++){
                for(const int adjNode : adj[i]){
                        inDegree[adjNode]++;
                }
        }
        queue<int> q;
        for(int i=0 ; i<N ; i++){
                if(inDegree[i] == 0){
                        q.push(i);
                }
        }

        while(!q.empty()){
                int node = q.front(); q.pop();
                ans.push_back(node);
                for(const int adjNode : adj[node]){
                        inDegree[adjNode]--;
                        if(inDegree[adjNode] == 0){
                                q.push(adjNode);
                        }
                }
        }

        return ans;

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
        vector<int> ans = topoSort(adj, N);
        if(ans.size() != N){
                cout << "There is a cycle in the graph " << endl;
        }
        else{
                for(int i=0 ; i<ans.size() ; i++){
                        cout << ans[i] << " ";
                }
        }
        cout << "\n";
}
