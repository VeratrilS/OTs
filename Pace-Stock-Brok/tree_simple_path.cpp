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
int ans  = 0;
int dfs(int node, int par , vector<vector<int>>& adj) {
    vector<int>comp;
    int sum =1;
    for(auto ch:adj[node]){
        if(ch != par){
            int val = dfs(ch, node, adj);
            sum+=val;
            comp.pb(val);
        }
    }
    for(auto ch:adj[node]){
        if(ch == par){
            comp.pb(adj.size()-sum);
        }
    }
    for(int i=0;i<comp.size();i++){
        for(int j=i+1;j<comp.size();j++){
            ans = ans + comp[i]*comp[j];
        }
    }
    return sum;
}
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<int>subtr(n,0);
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(0,-1,adj);
    cout<<ans<<endl;
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