#include <bits/stdc++.h>
using namespace std;
int a[100005],sz[100005],lvl[100005];
int seg_id[100005],pos_id[100005],parent[100005];
int CNT;
int e_to_v[100005];
vector<pair<int,int>> edges(100005);
vector<pair<int,int>> v[100005];
vector<int> chain[100005];
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
      segtree[u]=x;
      if(a!=b) lazy[u*2]+=x,lazy[2*u+1]+=x;
      return;
    }
    update(u*2,a,(a+b)/2,i,j,x); update(u*2+1,(a+b)/2+1,b,i,j,x);
    segtree[u]=max(segtree[u*2],segtree[u*2+1]);
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
    return max(query(u*2,a,(a+b)/2,i,j),query(u*2+1,1+(a+b)/2,b,i,j));
  }
  T query(int i, int j){
    return query(1,0,segtree.size()/4-1,i,j);
  }
};
int dfs(int u, int dad=1, int depth=1){
  lvl[u] = depth;
  sz[u] = 1;
  for(auto i:v[u]) if(i.first!=dad)
    sz[u] += dfs(i.first,u,depth+1);
  return sz[u];
}
void hld(int u, int dad = 1, int chain_no = 0, int chain_parent = 0){
  seg_id[u] = chain_no;
  pos_id[u] = chain[chain_no].size();
  parent[u] = chain_parent;
  chain[chain_no].push_back(u);
  int max_sz = 0, heavy_child = -1;
  for(auto i:v[u]) if(i.first!=dad){
    a[i.first] = i.second;
    if(max_sz < sz[i.first])
      max_sz = sz[i.first], heavy_child = i.first;
  }
  if(heavy_child!=-1)
    hld(heavy_child, u, chain_no, chain_parent);
  for(auto i:v[u]) if(i.first!=dad && i.first!=heavy_child)
    hld(i.first,u,++CNT, u);
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int T, n, x, y;
  for(cin>>T;T-- && cin>>n;){
    
    CNT = 0;
    for(int i=0;i<100005;chain[i].clear(), v[i].clear(), i++);

    for(int i=1,c;i<n;++i){
      cin>>x>>y>>c;
      edges[i] = {x,y};
      v[x].push_back({y,c});
      v[y].push_back({x,c});
    }

    dfs(1);

    for(int i=1;i<n;++i){
      int u = edges[i].first, v = edges[i].second;
      e_to_v[i] = (lvl[u]<lvl[v]?v:u);
    }

    hld(1);

    vector<SegmentTree<int>> ST;
    for(int i=0;i<=CNT;++i){
      ST.push_back(SegmentTree<int>(chain[i].size()));
      for(auto u:chain[i])
        ST[i].update(pos_id[u],a[u]);
    }

    for(string type;cin>>type && type!="DONE";){
      cin>>x>>y;
      if(type=="QUERY"){
        int res = 0;
        while(x!=y){
          if(seg_id[x]>seg_id[y]) swap(x,y);
          else if(seg_id[x] == seg_id[y]){
            if(pos_id[x]>pos_id[y]) swap(x,y);
            res = max(res,ST[seg_id[y]].query(pos_id[x]+1,pos_id[y]));
            break;
          }
          res = max(res, ST[seg_id[y]].query(0,pos_id[y]));
          y = parent[y];
        }
        cout<<res<<'\n';
      }
      else if(type == "CHANGE"){
        int u = e_to_v[x];
        ST[seg_id[u]].update(pos_id[u],y);
      }
    }
  }
}