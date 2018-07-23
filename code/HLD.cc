#include <bits/stdc++.h>
using namespace std;

int a[100005],sz[100005],lvl[100005];
int seg_id[100005],pos_id[100005],parent[100005];
int up[100005][17],tin[100005],tout[100005],clk,CNT;
vector<int> v[100005], chain[100005];

class SegmentTree{
  vector<set<int>> segtree;
  public:
  SegmentTree(int size){
    segtree.resize(4*size);
  }
  void update(int u, int a, int b, int i, int j, int x){
    if(j<a || i>b || a>b) return;
    segtree[u].insert(x);
    if(j>=b && i<=a) return;
    update(u*2,a,(a+b)/2,i,j,x); 
    update(u*2+1,(a+b)/2+1,b,i,j,x);
  }
  void update(int i, int x){
    update(1, 0, segtree.size()/4-1, i, i, x);
  }
  int query(int u, int a, int b, int i, int j,int r){
    if(j<a || i>b || a>b) return 2e9;
    if(j>=b && i<=a) {
      auto it = segtree[u].lower_bound(r);
      int ans = abs(r-*it);
      if(it!=segtree[u].begin()) 
        ans = min(ans,abs(r-*(--it)));
      return ans;
    }
    return min(query(u*2,a,(a+b)/2,i,j,r),
               query(u*2+1,1+(a+b)/2,b,i,j,r));
  }
  int query(int i, int j,int r){
    return query(1,0,segtree.size()/4-1,i,j,r);
  }
};

int dfs(int u, int dad=1, int depth=1){
  tin[u]=clk++;
  up[u][0] = dad;
  lvl[u] = depth;
  for(int i=1;i<17;++i)
    up[u][i] = up[up[u][i-1]][i-1];
  lvl[u] = depth, sz[u] = 1;
  for(auto i:v[u]) if(i!=dad)
    sz[u] += dfs(i,u,depth+1);
  tout[u] = clk++;
  return sz[u];
}
void hld(int u, int dad = 1, int chain_no = 0, int chain_parent = 0){
  seg_id[u] = chain_no;
  pos_id[u] = chain[chain_no].size();
  parent[u] = chain_parent;
  chain[chain_no].push_back(u);
  int max_sz = 0, heavy_child = -1;
  for(auto i:v[u]) if(i!=dad && max_sz<sz[i])
    tie(max_sz,heavy_child)={sz[i],i};
  if(heavy_child!=-1)
    hld(heavy_child, u, chain_no, chain_parent);
  for(auto i:v[u]) if(i!=dad && i!=heavy_child)
    hld(i,u,++CNT, u);
}
int lca(int u, int v){
  if(lvl[u]>lvl[v]) swap(u,v);
  if(tin[u]<=tin[v] && tout[v]<=tout[u]) return u;
  for(int i=17;i--;)
    if(!(tin[up[u][i]]<=tin[v]&&tout[v]<=tout[up[u][i]]))
      u = up[u][i];
  return up[u][0];
}
vector<SegmentTree> ST;
int get(int x, int y, int r){
  if(seg_id[x] == seg_id[y]){
    if(pos_id[x]>pos_id[y]) swap(x,y);
    return ST[seg_id[x]].query(pos_id[x],pos_id[y],r);
  }
  if(seg_id[x]>seg_id[y]) swap(x,y);
  return min(get(x,parent[y],r),
              ST[seg_id[y]].query(0,pos_id[y],r));
}

int u[100005],T,q,n;
int main(){
  for(cin>>T;T--;){
    CNT = 0; clk = 0;
    for(int i=0;i<100005;chain[i].clear(),v[i].clear(), ++i);

    cin>>n>>q;  for(int i=1;i<=n;cin>>a[i++]);
    for(int i=n,x,y;--i;){
      cin>>x>>y;
      v[x].push_back(y); v[y].push_back(x)
    }
    
    dfs(1); hld(1);

    ST.clear();
    for(int i=0;i<=CNT;++i){
      ST.push_back(SegmentTree(chain[i].size()));
      for(auto u:chain[i])
        ST[i].update(pos_id[u],a[u]);
    }

    for(int ans=0,r,k,CA;q--;){
      cin>>r>>k; r^=ans;
      for(int i=0;i<k;u[i++]^=ans) cin>>u[i];
      CA = u[0], ans = 2000000000;
      for(int i=1;i<k;CA = lca(CA,u[i++]));
      for(int i=0;i<k;ans=min(ans,get(CA,u[i++],r)));
      cout<<ans<<'\n';
    }
  }
}