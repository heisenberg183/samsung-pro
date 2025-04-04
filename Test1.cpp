/*Daksh Dixit*/
#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<iostream>
#include<istream>
#include<fstream>
 
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
const int mod = 1000000007;
// const int mod = 998244353;
#define inf 1000000000000000005
#define endl "\n"
#define pb push_back
#define X first
#define Y second
#define yes cout << "YES" <<endl
#define no cout << "NO" <<endl
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define fr(i,a,b) for(int i = a; i < b; i++)
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define ai(a, n) for (int ele = 0; ele < n; ele++) cin >> a[ele];
#define ain(a, lb, rb) for (int ele = lb; ele <= rb; ele++) cin >> a[ele];
#define ao(a, n) {for (int ele = 0; ele < (n); ele++) { if (ele) cout << " "; cout << a[ele]; } cout << '\n';}
#define aout(a, lb, rb) {for (int ele = (lb); ele <= (rb); ele++) { if (ele > (lb)) cout << " "; cout << a[ele]; } cout << '\n';}
#define getunique(v) {sort(all(v)); v.erase(unique(all(v)), v.end());}
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int,int> pi;
typedef vector<int> vi;
typedef vector<pi> vpi;
template<class T>
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //greater<int> for descending set, also less_equal<int> which is ascending multiset 
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;
/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/
//DEBUG SECTION
void __print(long x) { cerr << x; }void __print(long long x) { cerr << x; }void __print(unsigned x) { cerr << x; }void __print(unsigned long x) { cerr << x; }void __print(unsigned long long x) { cerr << x; }void __print(float x) { cerr << x; }void __print(double x) { cerr << x; }void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }void __print(const char *x) { cerr << '\"' << x << '\"'; }void __print(const string &x) { cerr << '\"' << x << '\"'; }void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename T, typename V>void __print(const pair<T, V> &x){cerr << '{';__print(x.first);cerr << ',';__print(x.second);cerr << '}';}
template <typename T>void __print(const T &x){int f = 0;cerr << '{';for (auto &i : x){cerr << (f++ ? "," : ""), __print(i);}cerr << "}";}
void _print() { cerr << "]\n"; }
template <typename T, typename... V> void _print(T t, V... v){__print(t);if (sizeof...(v)){cerr << ", ";}_print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...)cerr << #x << " = ["; \
    _print(x)
#else
#define debug(x...)
#endif
//DEBUG SECTION

/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRandomNumber(int l, int r) {return uniform_int_distribution<int>(l, r)(rng);} 
int MSB(int n){return 63-__builtin_clzll(n);}
int getIthbit(int n, int i){return ( n & ( 1 << i) ) == 0 ? 0 : 1;}
void setIthBit(int &n, int i){ n = n | (1 << i);}
void clearIthBit(int &n, int i){ n = n & ( ~(1 << i));}
int gcd(int a, int b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
int pwr(int a, int b) {a %= mod; int res = 1; while (b > 0) {if (b & 1) res = (res * a) % mod; a = (a * a) % mod; b >>= 1;} return res;}
void extendgcd(int a, int b, int*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); int x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
int mminv(int a){int arr[3];extendgcd(a, mod, arr); if(arr[2]!=1){return -1;}arr[0] =(arr[0]%mod + mod)%mod ;return arr[0];} //Modulo Inverse Exist only if gcd(a,m)=1;
int inv(int i) {if (i == 1) return 1; return (mod - ((mod / i) * inv(mod % i)) % mod) % mod;}
int mminvprime(int a){int ans = pwr(a, mod - 2); ans = (ans%mod+mod)%mod; return ans;} //If a,m are Coprime
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
void google(int t) {cout << "Case #" << t << ": ";}
int mod_add(int a, int b) {a = a % mod; b = b % mod; return (((a + b) % mod) + mod) % mod;}
int mod_mul(int a, int b) {a = a % mod; b = b % mod; return (((a * b) % mod) + mod) % mod;}
int mod_sub(int a, int b) {a = a % mod; b = b % mod; return (((a - b) % mod) + mod) % mod;}
int mod_div(int a, int b) {a = a % mod; b = b % mod; return (mod_mul(a, mminvprime(b)) + mod) % mod;}  //only for prime m
int phin(int n) {int number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (int i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
int ceil_div(int a, int b) {return a % b == 0 ? a / b : a / b + 1;}
int ceil_rem(int a, int b) {return a%b==0 ? b : a%b;}

class CMP{
public:
    bool operator()(pi &a , pi &b) //For min priority_queue .
    {    return ! ( a.X < b.X || ( a.X==b.X && a.Y <= b.Y ));   }
    // priority_queue<pi, vector<pi>, CMP> minPQ;
};
void add(map<int,int> &m, int x,int cnt=1){
    auto jt=m.find(x);
    if(jt==m.end()){m.insert({x,cnt});} 
    else{jt->Y+=cnt;}
}
void del(map<int,int> &m, int x,int cnt=1){
    auto jt=m.find(x);
    if(jt->Y<=cnt){m.erase(jt);}
    else{jt->Y-=cnt;}
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Test - 1
// You are given a path on an infinite 2d lattice. The path consists of line segments parallel to either the x or y axis.Example : (1, 1) to (1, 3) to (6, 3) to (6, 6). Also there is a set of points given . You have to find how many of the given points lie on the path.
// Input 
// n,m
// There were n numbers that denoted x coordinates of n points
// There were n numbers again which denoted y coordinates of those n points
// Now there are two more arrays of size m , one consisting of x coordinates and other y coordinates correspondingly
// These points are the turning points in a path.
// Examples.
// Say i went from 1, 1 to 1, 5 to 2, 5 so the given arrays will be
// 1, 1, 2
// 1, 5, 5
// In the given path , we have to find how many of the given n points lie.

set<pi> mergeIntervals(vector<pi> &intervals){
    vector<pi> merged;
    merged.pb({INT_MIN,INT_MIN});
    sort(all(intervals));
    for(auto [a,b] : intervals){
        auto [x,y] = merged.back();
        if(a>y){
            merged.pb({a,b});
        }
        else{
            merged.back().second = max(y,b);
        }
    }
    set<pi> result;
    debug(merged);
    for(auto [x,y] : merged){
        result.insert({x,y});
    }
    return result;
}

bool PointPresent(int x, set<pi> &intervals){
    auto it = intervals.upper_bound({x, INT_MAX});
    if (it == intervals.begin()) return false;
    --it; // move to the previous interval
    return it->first <= x && x <= it->second;
}


int solve(int n, int m, vector<pi> &points, vector<pi> &pointsOnPath){
    map<int,vector<pi>> horizontals;
    map<int,vector<pi>> verticals;
    for(int i = 0; i+1 < m; i++){
        int x1 = pointsOnPath[i].first;
        int y1 = pointsOnPath[i].second;
        int x2 = pointsOnPath[i+1].first;
        int y2 = pointsOnPath[i+1].second;
        if(y1 == y2){
            int y = y1;
            int low = min(x1,x2);
            int high = max(x1,x2);
            horizontals[y].pb({low,high});
        }
        else if(x1 == x2){
            int x = x1;
            int low = min(y1,y2);
            int high = max(y1,y2);
            verticals[x].pb({low,high});
        }
    }
    map<int,set<pi>> mergedHorizontals;
    map<int,set<pi>> mergedVerticals;
    
    for(auto &[a,b] : horizontals){
        // debug(b);
        mergedHorizontals[a] = mergeIntervals(b);
    }
    for(auto &[a,b] : verticals){
        // debug(b);
        mergedVerticals[a] = mergeIntervals(b);
    }

    int ans = 0;
    for(auto &[x,y] : points){
        if(horizontals.count(y) && PointPresent(x,mergedHorizontals[y])){
            ans++;
            continue;
        }
        if(verticals.count(x) && PointPresent(y,mergedVerticals[x])){
            ans++;
        }
    }
    return ans;
}

//Code
signed main(){
    fast;
    // Try This Test Case Exp ans = 2
    // 3 6
    // 1 2 1
    // 3 5 11
    // 1 1 2 2 1 1 
    // 1 5 5 0 0 10
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> points(n);
    vector<pair<int,int>> pointsOnPath(m);
    for(int i = 0; i < n; i++){
        cin>>points[i].first;
    }
    for(int i=0;i<n;i++){
        cin>>points[i].second;
    }
    for(int i = 0; i < m; i++){
        cin>>pointsOnPath[i].first;
    }
    for(int i=0;i<m;i++){
        cin>>pointsOnPath[i].second;
    }
    cout<<solve(n,m,points,pointsOnPath)<<endl;
    return 0;
}