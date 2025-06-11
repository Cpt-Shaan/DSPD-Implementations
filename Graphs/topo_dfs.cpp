// Topological Sort for a Graph using DFS and Stack

#include <iostream>
#include <vector>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& adj, vector<bool>& vis, int node, stack<int>& st){
        vis[node] = true;
        for(const int adjNode : adj[node]){
                if(!vis[adjNode]){
                        dfs(adj, vis, adjNode, st);
                }
        }
        st.push(node);
}

vector<int> topoSort(vector<vector<int>>& adj, int N){
        vector<bool> vis(N, false);
        vector<int> ans;
        stack<int> st;
        for(int i=0 ; i<N ; i++){
                if(!vis[i]){
                        dfs(adj, vis, i, st);
                }
        }

        while(!st.empty()){
                ans.push_back(st.top());
                st.pop();
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
        for(int i=0 ; i<ans.size() ; i++){
                cout << ans[i] << " ";
        }
        cout << "\n";
        return 0;
}
