struct aho {
  struct node {
    map<char, int> next, go;
    int link, el, er;
    vector<int> inv;
    node() : link(-1) {}
  };
  vector<node> b;
  vector<int> pos, q;
  aho() {}
  aho(const vector<string>& vs) {
    int m = vs.size();
    pos.resize(m);
    b.emplace_back();
    for (int i=0; i<m; i++) pos[i] = add(vs[i]);
    find_links();
    int t = 0;
    dfs(0, t);
  }
  int newnode() {
    b.emplace_back();
    return b.size() - 1;
  }
  int add(const string& s) {
    int x = 0;
    for (char c : s) {
      if (b[x].next.count(c)) x = b[x].next[c];
      else x = b[x].next[c] = newnode();
    }
    return x;
 
  void find_links() {
    q = {0};
    size_t qs = 0;
    while (qs != q.size()) {
      int x = q[qs++];
      for (auto [c, y] : b[x].next) {
        int z = b[x].link;
        for (; z != -1 && !b[z].next.count(c); z = b[z].link);
        if (z == -1) b[y].link = 0;
        else b[y].link = b[z].next[c];
        q.push_back(y);
      }
    }
    for (int x : q) {
      b[x].go = b[x].next;
      if(x) b[b[x].link].inv.push_back(x);
    }
  }
  int go(int x, char c) {
    if (x == -1)  return 0;
    if (!b[x].go.count(c)) b[x].go[c] = go(b[x].link, c);
    return b[x].go[c];
  }
  void dfs(int x, int& t) {
    b[x].el = t++;
    for (int y : b[x].inv) dfs(y, t);
    b[x].er = t;
  }
};