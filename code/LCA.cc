class LCA{
	vector<vector<int>> up;
	vector<int> tin, tout;
	int CLK, n, lg;
	void tour(int u, int dad, const vector<vector<int>>& adj){
		tin[u] = CLK++;
		up[u][0] = dad;
		for(int i = 1; i < lg; ++i)
			up[u][i] = up[up[u][i-1]][i-1];
		for(auto i: adj[u]) tour(i, u, adj);
		tout[u] = CLK++;
	}
 
public:
	LCA(const vector<vector<int>>& adj, int root = 1):
	CLK(0), n(adj.size()), lg(1+__lg(n)){
		tin.resize(n), tout.resize(n);
		up.resize(n, vector<int>(lg));
		tour(root, root, adj);
	}
	bool is_ancestor(int x, int y){
		return tin[x] <= tin[y] && tout[y] <= tout[x];
	}
	int lca(int x, int y){
		if(is_ancestor(x, y)) return x;
		if(is_ancestor(y, x)) return y;
		for(int b = lg; b--;)
			if(!is_ancestor(up[x][b], y))
				x = up[x][b];
		return up[x][0];
	}	
};