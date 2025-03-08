#include<bits/stdc++.h>
#include <type_traits>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 

using namespace __gnu_pbds;
using namespace std;

#ifndef ONLINE_JUDGE
#include "template.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif


#define ordered_set tree<int, null_type,less<int >, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
// find_by_order, order_of_key

template<typename T>
int log2_floor(T i)
{
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    if (i <= 0)
        return -1;
    unsigned long val = i;
    return std::bit_width(val) - 1;
}

int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int inv(int a, int m) {
    return a <= 1 ? a : m - (long long)(m/a) * inv(m % a, m) % m;
}

struct dsu{
    int n;
    vector<int> parent,sz;
    dsu(int n):n(n)
    {
        parent.resize(n);
        sz.resize(n);
        iota(parent.begin(),parent.end(),0);
        fill(sz.begin(),sz.end(),1);
    }
    int find(int a)
    {
        return a == parent[a] ? a : parent[a] = find(parent[a]);
    }
    bool merge(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] > sz[b])
        {
            parent[b] = a;
            sz[a] = sz[a] + sz[b];
        }
        else
        {
            parent[a] = b;
            sz[b] = sz[a] + sz[b];
        }
        return 1;
    }
    int components()
    {
        int ans = 0;
        for (int i = 0 ; i < n ; i++)
            ans += (parent[i] == i);
        return ans;
    }
};

template<class T>
struct sparse_table{
    int n;
    vector<vector<T> > st;

    T combine(T a , T b)
    {
        // fill here
    }

    sparse_table(int n1, const vector<T> &array) : n(n1)
    {
        st.resize(25,vector<T>(n+1));
        std::copy(array.begin(), array.end(), st[0].begin());
        for (int i = 1; i <= 24; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = combine(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }

    T query(int L, int R)
    {
        int i = log2_floor(R-L+1);
        return combine(st[i][L], st[i][R - (1 << i) + 1]);
    }
};

template<class T>
struct segment_tree{
    int n;
    vector<T> t,a;
    segment_tree(int n1, const vector<T> &x) : n(n1),a(x)
    {
        t.resize(4*n);
    }
    segment_tree(int n1) : n(n1)
    {
        t.resize(4*n);
    }
    T combine(T a , T b)
    {
        // fill here
    }
    void build(int l, int r , int index)
    {
        if (l == r)
        {
            // fill here
            return;
        }
        int m = (l+r) >> 1;
        build(l,m,2*index+1);
        build(m+1,r,2*index+2);
        t[index] = combine(t[2*index+1],t[2*index+2]);
    }
    void update(int l, int r, int index, int pos, T val)
    {
        if (l == r)
        {
            // fill here
            return;
        }
        int m = (l+r) >> 1;
        if (pos <= m)
            update(l,m,2*index+1,pos,val);
        else   
            update(m+1,r,2*index+2,pos,val);
        
        t[index] = combine(t[2*index+1],t[2*index+2]);
    }
    T query(int l, int r , int index, int ql, int qr)
    {
        if (l == ql && r == qr)
            return t[index];
        int m = (l+r) >> 1;
        if (qr <= m)
            return query(l,m,2*index+1,ql,qr);
        if (ql > m)
            return query(m+1,r,2*index+2,ql,qr);
        return combine(query(l,m,2*index+1,ql,m),query(m+1,r,2*index+2,m+1,qr));
    }

    void update(int pos, T val) {update(0, n - 1, 0, pos, val);}
    
    T query(int l, int r) {return query(0, n - 1, 0, l, r);}

};



template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

#define MOD 1000000007
#define INF 1e18

void yn(bool possible)
{
     cout << ((possible) ? "YES" : "NO") << "\n";
}

#define print(n) cout << n << "\n"
#define print_space(a, n) for (int i = 0; i < n; ++i) cout << a[i] << (i == n - 1 ? '\n' : ' ');
#define all(x) (x).begin(), (x).end()
#define sortall(x) sort(all(x))

template<typename T>

void read(T a[], int n, int offset = 0) {
    for (int i = 0; i < n; i++) {
        cin >> a[i + offset];
    }
}


#define read_2d(a,n,m) \
    for (int i = 0 ; i < n ; i++) \
        for (int j = 0 ; j < m ; j++) \
            cin >> a[i][j];


#define read_pair(a,n) \
    for (int i = 0 ; i < n ; i++) \
        cin >> a[i].first >> a[i].second;

typedef unsigned long long ull;
typedef long long ll;

void solve()
{
    
}
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
}
