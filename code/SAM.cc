struct SuffixAutomaton {
  vector<map<char,int>> edges; // edges[i]: the labeled edges from node i
  vector<int> link;   // link[i]  : the parent of i
  vector<int> length; // length[i]: length of longest string in ith class
  vector<int> cnt;    // No. of times substring occurs
  int last;  // index of equivalence class of whole string
  SuffixAutomaton(string const& s) {
    // add the initial node
    edges.push_back(map<char,int>());
    link.push_back(-1);
    length.push_back(0);
    cnt.push_back(0);
    last = 0;

    for(int i=0;i<s.size();i++) {
      // construct r
      edges.push_back(map<char,int>());
      length.push_back(i+1);
      link.push_back(0);
      cnt.push_back(1);
      int r = edges.size() - 1;
      // add edges to r and find p with link to q
      int p = last;
      while(p >= 0 && !edges[p].count(s[i])){
        edges[p][s[i]] = r;
        p = link[p];
      }
      if(p != -1) {
        int q = edges[p][s[i]];
        if(length[p] + 1 == length[q]) {
          // we do not have to split q, just set the correct suffix link
          link[r] = q;
        } else {
          // we have to split, add q'
          edges.push_back(edges[q]); // copy edges of q
          length.push_back(length[p] + 1);
          link.push_back(link[q]); // copy parent of q
          cnt.push_back(0);
          int qq = edges.size()-1;
          // add qq as the new parent of q and r
          link[q] = link[r] = qq; cnt[r] = 1;
          // move short classes pointing to q to point to q'
          while(p >= 0 && edges[p][s[i]] == q) {
            edges[p][s[i]] = qq;
            p = link[p];
          }
        }
      }
      last = r;
    }
    
    vector<int> ind(length.size());
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(), ind.end(), [&](int i, int j){
      return length[i] > length[j];
    });
    for(auto i:ind) if(link[i] >= 0)
      cnt[link[i]] += cnt[i];
  }
};