long long segtree[400005],lazy[400005],n;
void update(int u, int a, int b, int i, int j, long long val){
	if(lazy[u]){
		segtree[u]+=(b-a+1)*lazy[u];
		if(a!=b){
			lazy[u*2]+=lazy[u];
			lazy[u*2+1]+=lazy[u];
		}
		lazy[u]=0;
	}
	if(a>b or j<a or i>b) return;
	if(a>=i and b<=j){
		segtree[u]+=(b-a+1)*val;
		if(a!=b){
			lazy[u*2]+=val;
			lazy[u*2+1]+=val;
		}
	}
	else{
		update(u*2,a,a+b>>1,i,j,val);
		update(u*2+1,1+(a+b)/2,b,i,j,val);
		segtree[u]=segtree[u*2]+segtree[u*2+1];
	}
}
long long query(int u, int a, int b, int i, int j){
	if(a>b or a>j or b<i) return 0;
	if(lazy[u]){
		segtree[u]+=(b-a+1)*lazy[u];
		if(a!=b){
			lazy[u*2]+=lazy[u];
			lazy[u*2+1]+=lazy[u];
		}
		lazy[u]=0;
	}
	if(a>=i and b<=j) return segtree[u];
	return query(u*2,a,(a+b)/2,i,j)+query(u*2+1,1+(a+b)/2,b,i,j);
}