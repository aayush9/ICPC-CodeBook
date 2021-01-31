template <typename T>
class SegmentTree{
	vector<T> segtree,lazy;
	public:
	SegmentTree(int size){
		segtree.resize(4*size,0);
		lazy.resize(4*size,0);
	}
	void update(int u, int a, int b, int i, int j, T x){
		if(lazy[u]){
			segtree[u]+=(b-a+1)*lazy[u];
			if(a!=b)
				lazy[u*2]+=lazy[u],lazy[2*u+1]+=lazy[u];
			lazy[u]=0;
		}
		if(j<a || i>b || a>b) return;
		if(j>=b && i<=a){
			segtree[u]+=(b-a+1)*x;
			if(a!=b) lazy[u*2]+=x,lazy[2*u+1]+=x;
			return;
		}
		update(u*2,a,(a+b)/2,i,j,x); update(u*2+1,(a+b)/2+1,b,i,j,x);
		segtree[u]=segtree[u*2]+segtree[u*2+1];
	}
	void update(int i, T x){
		update(1, 0, segtree.size()/4-1, i, i, x);
	}
	void update(int i, int j, T x){
		update(1, 0, segtree.size()/4-1, i, j, x);
	}
	T query(int u, int a, int b, int i, int j){
		if(j<a || i>b || a>b) return 0;
		if(lazy[u]){
			segtree[u]+=(b-a+1)*lazy[u];
			if(a!=b)
				lazy[u*2]+=lazy[u],lazy[2*u+1]+=lazy[u];
			lazy[u]=0;
		}
		if(j>=b && i<=a) return segtree[u];
		return query(u*2,a,(a+b)/2,i,j)+query(u*2+1,1+(a+b)/2,b,i,j);
	}
	T query(int i, int j){
		return query(1,0,segtree.size()/4-1,i,j);
	}
};