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
    int l,r;
    string s;
    cin>>l>>r>>s;
    string s1 = s.substr(l,r-l+1);
    int ans = 0;
    for(int i=0;i<s1.length()/2;i++){
        ans+=(s1[i]!=s1[s1.length()-1-i]);
        // Implementation for solving the palindrome problem
    }
    cout<<ans<<"\n";
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
Implementations are simple. */