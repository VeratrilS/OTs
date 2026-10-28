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

void solve(){
    int n;
    cin>>n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }
    vvi can(n, vi(n, 0));
    // can[i][j] = 1 if i,j is all zero
    // can[i][j] = 0 if it is there
    // dependent can[i][j] = can[i+1][k-1] && can[k+1][j-1] && 2*a[j] == a[i] + a[k]
    // independent can[i][j] = can[i][k] && can[k+1][j]
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            can[j][i] = 1;
        }
    }
    for(int i=n-1;i>=0;i--){ 
        for(int j=i;j<n;j++){
            // Logic for filling the can matrix
            if(j-i+1<=2)continue;
            for(int k=i+1;k<j;k++){
                can[i][j]|=(can[min(i+1,n-1)][max(0LL,k-1)] && can[min(k+1,n-1)][max(0LL,j-1)] && 2*a[k] == a[i] + a[j]);
                can[i][j]|=can[i][k] && can[min(k+1,n-1)][j];
            }
        }
    }
    vector<int>dp(n,0); // dp[i] : no of elements left until index i 
    for(int i=0;i<n;i++){
        dp[i] = (i>0 ? dp[i-1] : 0)+1;
        for(int j=i;j>=0;j--){
            dp[i] = min(dp[i] , can[j][i] ? (j>0 ? dp[j-1]:0) : dp[i]);
        }
    }
    cout<<dp[n-1]<<endl;
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