// Program to implement the Prim's algorithm to find the Minimum spanning tree of a graph
// Using minHeap to store edge weights and parents

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Returns {sum_of_weights_of_MST, MST -> vector<edges>}
pair<int, vector<vector<int>>> primAlgo(vector<vector<vector<int>>>& adj, int N){
        vector<vector<int>> MST;
        int sum = 0;
        priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq;
        // To store {wt, {node, parent}}
        pq.push({0, {0,-1}});
        vector<bool> vis(N, false);
        int vis_count = 0;

        while(!pq.empty() && vis_count != N){
                int wt = pq.top().first;
                int node = pq.top().second.first;
                int parent = pq.top().second.second;
                pq.pop();

                if(vis[node]) continue;
                vis[node] = true;
                vis_count++;
                if(parent != -1){
                        MST.push_back({parent, node});
                        sum += wt;
                }
                for(auto it : adj[node]){
                        int weight = it[1];
                        int adjNode = it[0];
                        if(!vis[adjNode] && adjNode != parent){
                                pq.push({weight, {adjNode, node}});
                        }
                }
        }

        return {sum, MST};
}

int main(){
        int N,E;
        cout << "Enter the no of nodes : ";
        cin >> N;
        cout << "Enter the no of edges (undirected graph considered) : ";
        cin >> E;
        vector<vector<vector<int>>> adj(N);

        cout << "Enter the edges in the format (v1, v2, wt) " << endl;
        for(int i=0 ; i<E ; i++){
                int v1, v2, wt;
                cout << "Edge and Weight " << i+1 << " : ";
                cin >> v1 >> v2 >> wt;
                adj[v1].push_back({v2, wt});
                adj[v2].push_back({v1, wt});
        }

        auto ans = primAlgo(adj, N);
        int sum = ans.first;
        vector<vector<int>> MST = ans.second;

        cout << "The sum of weights of the MST is " << sum << endl;
        cout << "The MST is - { ";
        for(int i=0 ; i<MST.size() ; i++){
                cout << "{" << MST[i][0] << "," << MST[i][1] << "} ";
        }
        cout << "}" << endl;
        return 0;
}
