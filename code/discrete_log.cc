// Calculates x such that g^x % md == h
int baby_giant(int g, int h, int md){
  unordered_map<int,int> mp;
  int sq = ceil(sqrtl(md));
  for(int i=0,now=1;i<sq;++i)
    mp[now] = i, now = (long long) now*g % md;
  for(int i=0,jmp=power(g,md-1-sq);i<sq;++i){
    if(mp.find(h)!=mp.end()) return i*sq+mp[h];
    h = (long long) h*jmp % md;
  }
  return -1;
}