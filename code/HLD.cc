#include <bits/stdc++.h>
using namespace std;
int a[500005],sz[500005],lvl[500005];
int seg_id[500005],pos_id[500005],parent[500005];
int up[500005][19],tin[500005],tout[500005],clk,CNT;
vector<int> chain[500005];
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
map<int,int> v[500005];
int dfs(int u, int dad=1, int depth=1, int last_edge = 0){
  tin[u]=clk++;
  up[u][0] = dad;
  lvl[u] = depth;
  a[u] = last_edge;
  for(int i=1;i<19;++i)
    up[u][i] = up[up[u][i-1]][i-1];
  lvl[u] = depth, sz[u] = 1;
  for(auto i:v[u]) if(i.first!=dad)
    sz[u] += dfs(i.first,u,depth+1, i.second);
  tout[u] = clk++;
  return sz[u];
}
void hld(int u, int dad = 1, int chain_no = 0, int chain_parent = 0){
  seg_id[u] = chain_no;
  pos_id[u] = chain[chain_no].size();
  parent[u] = chain_parent;
  chain[chain_no].push_back(u);
  int max_sz = 0, heavy_child = -1;
  for(auto i:v[u]) if(i.first!=dad && max_sz<sz[i.first])
    tie(max_sz,heavy_child)=make_pair(sz[i.first],i.first);
  if(heavy_child!=-1)
    hld(heavy_child, u, chain_no, chain_parent);
  for(auto i:v[u]) if(i.first!=dad && i.first!=heavy_child)
    hld(i.first,u,++CNT, u);
}
int lca(int u, int v){
  if(lvl[u]>lvl[v]) swap(u,v);
  if(tin[u]<=tin[v] && tout[v]<=tout[u]) return u;
  for(int i=19;i--;)
    if(!(tin[up[u][i]]<=tin[v]&&tout[v]<=tout[up[u][i]]))
      u = up[u][i];
  return up[u][0];
}
vector<SegmentTree> ST;
bool get(int x, int y){
  if(seg_id[x] == seg_id[y]){
    if(pos_id[x]>pos_id[y]) swap(x,y);
    return ST[seg_id[x]].query(pos_id[x],pos_id[y]);
  }
  if(seg_id[x]>seg_id[y]) swap(x,y);
  return get(x,parent[y]) ^ ST[seg_id[y]].query(0,pos_id[y]);
}
int u[100005],T,q,n;
vector<pair<pair<int,int>,int>> edges(1);
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin>>n;
  for(int i=1,x,y,p;i<n;++i){
    cin>>x>>y>>p;
    p%=2;
    v[x][y] = p;
    v[y][x] = p;
    edges.push_back({{x,y},p});
  }
  dfs(1); hld(1);
  ST.clear();
  for(int i=0;i<=CNT;++i){
    ST.push_back(SegmentTree(chain[i].size()));
    for(auto u:chain[i])
      ST[i].update(pos_id[u],a[u]);
  }
  for(cin>>q;q--;){
    int type,x,y;
    cin>>type>>x>>y;
    if(type==1){
      int l = lca(x,y);
      bool sum = get(x,l) ^ get(y,l);
      cout<<(sum?"WE NEED BLACK PANDA\n":"JAKANDA FOREVER\n");
    } else {
      if(lvl[edges[x].first.first]>lvl[edges[x].first.second])
        x = edges[x].first.first;
      else
        x = edges[x].first.second;
      y %= 2;
      ST[seg_id[x]].update(pos_id[x],y);
    }
  }
}