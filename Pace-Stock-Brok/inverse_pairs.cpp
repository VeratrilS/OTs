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
int ans;
void merge(int st, int mid, int e, string &s){
    // Implementation for merging two sorted subarrays
    // st -> mid
    // mid+1 -> e
    int p1 = st , p2 = mid+1;
    vector<int>tmp;
    while(p1 <= mid && p2 <= e){
        if(s[p1] <= s[p2]){
            tmp.pb(s[p1]);
            p1++;
        }
        else{
            tmp.pb(s[p2]);
            p2++;
            // this is i < j and s[i] > s[j] can be found
            // ans += (mid - p1 + 1);
        }
    }
    for(int i=mid+1;i<=e;i++){
        int ind = upper_bound(s.begin()+st,s.begin()+mid+1,s[i]) - s.begin();
        ans += (mid - ind + 1);
    }
    while(p1 <= mid){
        tmp.pb(s[p1]);
        p1++;
    }
    while(p2 <= e){
        tmp.pb(s[p2]);
        p2++;
    }
    for(int i = st; i <= e; i++){
        s[i] = tmp[i - st];
    }
}
void mergesrt(int st , int e , string &s){
    int mid = (st+e)/2;
    mergesrt(st,mid,s);
    mergesrt(mid+1,e,s);
    merge(st,mid,e,s);
}
int inv(string &s){
    auto tmp = s;
    ans = 0;
    mergesrt(0 , s.size()-1, s);
    s = tmp;
    return ans;
}
void solve(){
    string s,t;
    cin>>s>>t;
    int ans = inv(s) + inv(t);
    
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
Implementations are simple.
*/