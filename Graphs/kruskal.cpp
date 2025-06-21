// Program to implement the Kruskal's algorithm using the Disjoint Set data structure

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class DisjointSet{
private:
        vector<int> rank, parent;
public:
        DisjointSet(int n){
                rank.resize(n,0);
                parent.resize(n);
                for(int i=0 ; i<n ; i++){
                        parent[i] = i;
                }
        }

        int findUltimateParent(int u){
                if(parent[u] == u) return u;
                return parent[u] = findUltimateParent(parent[u]);
        }

        void unionRank(int u, int v){
                int parentU = findUltimateParent(u);
                int parentV = findUltimateParent(v);

                if(parentU != parentV){
                        if(rank[parentU] < rank[parentV]){
                                parent[parentU] = parentV;
                        }
                        else if(rank[parentV] < rank[parentU]){
                                parent[parentV] = parentU;
                        }
                        else{
                                parent[parentU] = parentV;
                                rank[parentV]++;
                        }
                 }
        }
};

pair<int, vector<vector<int>>> kruskalAlgo(vector<vector<vector<int>>> adj, int N){
        vector<pair<int, pair<int,int>>> edges; // Edges as {wt, {v1, v2}}
        for(int i=0 ; i<N; i++){
                for(auto it : adj[i]){
                        edges.push_back({it[1], {i, it[0]}});
                }
        }

        DisjointSet dsu(N);
        sort(edges.begin(), edges.end());

        vector<vector<int>> ans;
        int sum = 0;
        for(int i=0 ; i<edges.size() ; i++){
                int wt = edges[i].first;
                int u = edges[i].second.first;
                int v = edges[i].second.second;

                if(dsu.findUltimateParent(u) != dsu.findUltimateParent(v)){
                        sum += wt;
                        ans.push_back({u,v});
                        dsu.unionRank(u,v);
                }
        }

        return {sum, ans};
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

        auto ans = kruskalAlgo(adj, N);
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
