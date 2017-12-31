int up[100005][20];
vector<int> v[100005];
void dfs(int u,int p=1){
    up[u][0]=p;
    for(int i=1;i<20;++i) up[u][i]=up[up[u][i-1]][i-1];
    for(auto i:v[u])
        if(i!=p) dfs(i,u);
}
int lca(int u,int v){
    if(hight[u]>hight[v]) swap(u,v);
    if(lt[u]<=lt[v]&&rt[v]<=rt[u]) return u;
    for(int i=19;i>=0;--i)
        if(!(lt[up[u][i]]<=lt[v]&&rt[v]<=rt[up[u][i]])) u=up[u][i];
    return up[u][0];
}