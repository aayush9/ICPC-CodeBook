#include <bits/stdc++.h>
using namespace std;
int A[1000005];
vector<int> segtree[400005];
void build(int u, int a, int b){
	if(a==b){
		segtree[u].push_back(A[a]);
		return;
	}
	build(u*2,a,(a+b)/2); build(u*2+1,(a+b)/2+1,b);
	segtree[u].resize(b-a+1);
	merge(segtree[u*2].begin(),segtree[u*2].end(),segtree[u*2+1].begin(),segtree[u*2+1].end(),segtree[u].begin());
}
int query(int u, int a, int b, int i, int j, int k){
	if(b<a || j<a || i>b) return 0;
	if(i<=a && b<=j) return lower_bound(segtree[u].begin(),segtree[u].end(),k) - segtree[u].begin();
	return query(u*2,a,(a+b)/2,i,j,k)+query(u*2+1,(a+b)/2+1,b,i,j,k);
}
int main(){
	ios_base::sync_with_stdio(0);
	int n,q,low,high,mid,x,y,k;
	for(cin>>n>>q,x=0;x<n;cin>>A[x++]);
	for(build(1,0,n-1);q--;cout<<low-1<<'\n')
		for(cin>>x>>y>>k,low=-1e9,high=1e9;low<high;)
			if(query(1,0,n-1,x-1,y-1,mid=low+high>>1)<k) low=mid+1;
			else high=mid;
}