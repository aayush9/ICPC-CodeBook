struct Hasher{
  vector<long long> prefix, pwr;
  const long long p;

  Hasher(const string& s, long long C = 1e5+7, long long _p = 1e9 + 7): p(_p) {
    pwr.push_back(1);
    long long run = 0;
    for(auto &c: s){
      run = (run * C + c) % p;
      prefix.push_back(run);
      pwr.push_back(pwr.back() * C % p);
    }
  }

  long long get(int l, int r){
    assert(l <= r);
    if(!l) return prefix[r];
    long long ans = prefix[r] - prefix[l-1]*pwr[r-l+1] % p;
    if(ans < 0) ans += p;
    return ans;
  }
};