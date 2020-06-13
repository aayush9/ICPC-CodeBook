struct UnionFind {
  int n,comp;
  vector<int> uf,si,c;
  UnionFind(int n=0):n(n),comp(n),uf(n),si(n,1){
    for(int i=0;i<n;++i) 
      uf[i]=i;
  }
  int find(int x){return x==uf[x]?x:find(uf[x]);}
  bool join(int x, int y){
    if((x=find(x))==(y=find(y))) return false;
    if(si[x]<si[y]) swap(x,y);
    si[x]+=si[y];uf[y]=x;comp--;
    c.push_back(y);
    return true;
  }
  int snap(){return c.size();}
  void rollback(int snap){
    while(c.size()>snap){
      int x=c.back(); c.pop_back();
      si[uf[x]]-=si[x];uf[x]=x;comp++;
    }
  }
};
enum {ADD,DEL,QUERY};
struct Query {int type,x,y;};
struct DynCon {
  vector<Query> q;
  UnionFind dsu;
  vector<int> mt;
  map<pair<int,int>,int> last;
  DynCon(int n):dsu(n){}
  void add(int x, int y){
    if(x>y) swap(x,y);
    q.push_back((Query){ADD,x,y}),mt.push_back(-1);
    last[make_pair(x,y)]=q.size()-1;
  }
  void remove(int x, int y){
    if(x>y)swap(x,y);
    q.push_back((Query){DEL,x,y});
    int pr=last[make_pair(x,y)];
    mt[pr]=q.size()-1;
    mt.push_back(pr);
  }
  void query(int x, int y){
    q.push_back((Query){QUERY,x,y});
    mt.push_back(-1);
  }
  void process(){ // answers all queries in order
    if(!q.size()) return;
    for(int i=0;i<q.size();++i) 
      if(q[i].type==ADD&&mt[i]<0)
        mt[i]=q.size();
    go(0,q.size());
  }
  void go(int l, int r){
    if(l+1==r){
      if(q[l].type==QUERY) // answer query using DSU
        puts(dsu.find(q[l].x)==dsu.find(q[l].y)? "YES":"NO");
      return;
    }
    int s=dsu.snap(),m=(l+r)/2;
    for(int i=r-1;i>=m;--i)
      if(mt[i]>=0&&mt[i]<l)
        dsu.join(q[i].x,q[i].y);
    go(l,m);
    dsu.rollback(s);
    for(int i=m-1;i>=l;--i)if(mt[i]>=r)dsu.join(q[i].x,q[i].y);
    go(m,r);
    dsu.rollback(s);
  }
};