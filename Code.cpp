#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ll long long int
#define pi 3.1415926535897932385
#define mod 1000000007 
#define MOD 998244353
#define db double
#define pp(x) pair<x,x>
#define ff first
#define ss second
#define FIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define vv(x) vector<x >
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof  pop_front
#define endl "\n"
#define umap unordered_map
#define pq priority_queue
#define dbg(x) { cout<< #x << ": " << (x) << endl; }
#define dbg2(x,y) { cout<< #x << ": " << (x) << " , " << #y << ": " << (y) << endl; }
#define bp ll kkk; cin >>kkk;
#define dbgArr(a,n) cout<<"Array "<<#a<<endl; for(ll i=0 ; i<n ; i++) cout<<a[i]<<" "; cout<<endl;
#define forn(i,n) for(ll i=0 ; i<n ; i++)
#define forn1(i,n) for(ll i=1 ; i<=n ; i++)
#define arr(a,n) for(ll i=0;i<n;i++){ cin>>a[i]; }
#define arr1(a,n) for(ll i=1;i<=n;i++){ cin>>a[i]; }
#define file freopen("inp.in","r",stdin); freopen("outp.out","w",stdout)
#define print cout<<"Case #"<<number<<": "
#define all(x) x.begin(), x.end()
#define trav(x, a) for(auto &x: a)
#define inf 1e18
#define ordered_set tree<ll, null_type,less,rb_tree_tag,tree_order_statistics_node_update>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll power(ll x, ll b) {ll p = 1;while (b > 0) {if(b&1) {p = p * x; p %= mod;} b >>= 1; x *= x; x %= mod;} return p % mod;}

void yn(bool x) {
    cout<<(x==1 ? "YES\n" : "NO\n");
}

ll modinv(ll n) { 
    return power(n,mod-2); 
}

int n,d,minimum_available ;
vector<int> available_resources , resources , maximum_needed_allocation ;
vector<int> safe_sequence ;

struct Process {
    vector<int> maximum_need ;
    vector<int> current_allocation ;
    vector<int> needed_allocation ;
    bool complete ;
    int id ;
};

vector<Process> v ;

bool cmp(Process &a , Process &b) {
	if(maximum_needed_allocation[a.id]==maximum_needed_allocation[b.id]) return a.id < b.id ;
	return maximum_needed_allocation[a.id] < maximum_needed_allocation[b.id];
}

void bonkers() {
    forn(i,n) {
        forn(j,d) {
            if(v[i].maximum_need[j]>resources[j] or available_resources[j] < 0) {
                cout<<"UNSAFE STATE" ;
                return ;
            }
        }
    }
    sort(all(v),cmp); // sort processes by maximum needed resources ascending
    forn(i,n) {
    	if(maximum_needed_allocation[v[i].id] <= minimum_available and !v[i].complete) {
    		v[i].complete=true ;
    		safe_sequence.pb(v[i].id);
    		forn(j,d) available_resources[j]+=v[i].current_allocation[j];
    		minimum_available = *min_element(all(available_resources));
    	}
    	else if(!v[i].complete) {
    		forn(j,d) {
    			if(v[i].needed_allocation[j]<=available_resources[j]) continue ;
    			cout<<"UNSAFE STATE" ;
    			return ;
    		}
    		v[i].complete=true ;
    		forn(j,d) available_resources[j]+=v[i].current_allocation[j];
    		minimum_available = *min_element(all(available_resources));
    	}
    }
    if(safe_sequence.size()!=n) {
        cout<<"UNSAFE STATE\n" ;
        return ;
    }
    cout<<"SAFE SEQUENCE IS :\n" ;
    trav(x,safe_sequence) cout<<x<<" " ;
}

void solve() {
    cin>>n>>d ;
    maximum_needed_allocation.resize(n,0);
    resources.resize(d,0);
    available_resources.resize(d,0);
    forn(j,d) { cin>>resources[j]; available_resources[j]=resources[j]; }
    forn(i,n) {
        Process x ;
        x.maximum_need.resize(d,0);
        x.current_allocation.resize(d,0);
        x.needed_allocation.resize(d,0);
        x.complete=false ;
        x.id = i ;
        forn(j,d) { cin>>x.current_allocation[j]; available_resources[j]-=x.current_allocation[j] ; }
        forn(j,d) { cin>>x.maximum_need[j]; x.needed_allocation[j]=x.maximum_need[j]-x.current_allocation[j]; }
        maximum_needed_allocation[i] = *max_element(all(x.needed_allocation));
        v.pb(x);
    }
    minimum_available = *min_element(all(available_resources));
    bonkers();
}

int main() 
{
    FIO
    ll TC=1 ;
    forn1(number,TC) solve();
    return 0;
}
