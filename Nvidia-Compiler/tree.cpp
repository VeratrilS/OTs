// Problem Statement
/*
*/
// Small Observations
/*
*/ 
// Claims on algo 
/*
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second
pair<int,int> dfs(int node,int par,auto &adj){
    int path = 0,
    for(auto [ch,w]:adj[node]){
        if(ch != par){
            auto [mx_path , mx] = dfs(ch,node,adj);
        }
    }
}
void solve(){
    int n;
    cin>>n;
    // no of edges
    vector<vector<pair<int,int>>>adj(n+1);
    vector<int>deg(n+1,0);
    for(int i=0;i<n;i++){
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back({y,w});
        deg[x]+=1;
        deg[y]+=1;
        adj[y].push_back({x,w});
    }
    n++; // no of nodes
    dfs(0,-1,adj);
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
// Golden Rules 
/*
Solutions are simple.
Proofs are simple.
Implementations are simple.
*/