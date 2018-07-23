set<int> v[100005];
map<int,int> mp[100005];
int n,up[100005][17],lvl[100005],par[100005],CNT,siz[100005],tin[100005],tout[100005];
void dfspre(int u, int dad=1, int depth = 0){
  static int clk = 0;
  tin[u]=clk++;
  up[u][0] = dad;
  lvl[u] = depth;
  for(int i=1;i<17;++i)
    up[u][i] = up[up[u][i-1]][i-1];
  for(int i:v[u]) if(i!=dad)
    dfspre(i,u,depth+1);
  tout[u]=clk++;
}
int dfs(int u, int dad){
  siz[u] = 1;
  for(int i:v[u]) if(i!=dad)
    siz[u] += dfs(i,u);
  return siz[u];
}
int centroid(int u, int dad){
  for(int i:v[u]) if(i!=dad && siz[i]>CNT)
    return centroid(i,u);
  return u;
}
void decompose(int u, int dad){
  CNT = dfs(u,dad)/2;
  int centre = centroid(u,dad);
  par[centre] = dad;
  for(int i:v[centre]) if(i!=dad){
    v[i].erase(centre);
    decompose(i,centre);
  }
  v[centre].clear();
}
int lca(int u, int v){
  if(lvl[u]>lvl[v]) swap(u,v);
  if(tin[u]<=tin[v] && tout[v]<=tout[u]) return u;
  for(int i=17;i--;)
    if(!(tin[up[u][i]]<=tin[v] && tout[v]<=tout[up[u][i]]))
      u = up[u][i];
  return up[u][0];
}
void update(int u){
  for(int node = u;u;u = par[u])
    ++mp[u][lvl[node]+lvl[u] - 2*lvl[lca(u,node)]];
}
int get(int u){
  int ans = INT_MAX;
  for(int node = u; u; u = par[u])
    ans = min(ans,lvl[u]+lvl[node]-2*lvl[lca(u,node)]+(*mp[u].begin()).first);
  return ans;
}