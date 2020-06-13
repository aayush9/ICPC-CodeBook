struct hasher{
  int hashes[MAXN+5];
  int *pow, *inv;
  int mod;
  int n;
  void init(string &str, int *p, int *i, int m){
    pow = p;
    inv = i;
    mod = m; 
    n = str.size();
    int last = 0;
    for (int i = 0; i < n; i++){
      int c = str[i] - 'a' + 1;
      last = (last + 1ll*c*pow[i]) % mod;
      hashes[i] = last;
    }
  }
  int getHash(int l, int r){
    if (r >= n || l < 0)
      return -1;
    int curr = hashes[r] - (l-1 >= 0 ? hashes[l-1] : 0);
    curr = ((curr % mod) + mod) % mod;
    curr = (1ll*curr*inv[l]) % mod;
    return curr;
  }
} A, B, C;