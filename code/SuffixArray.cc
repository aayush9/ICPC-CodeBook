#include <bits/stdc++.h>
using namespace std;
vector<int> suffix_array(string &s){
  int n = s.size();
  vector<int> sa(n), buckets(n);
  for(int i=0;i<n;++i) sa[i] = n-i-1;
  stable_sort(sa.begin(),sa.end(),[&](int i, int j){return s[i]<s[j];});
  for(int i=0;i<n;++i) buckets[i]=s[i];
  for(int len=1;len<n;len*=2){
    vector<int> b(buckets), cnt(n), s(sa);
    for(int i=0;i<n;++i)
      buckets[sa[i]]=i&&b[sa[i-1]]==b[sa[i]]&&sa[i-1]+len<n&&b[sa[i-1]+len/2]==b[sa[i]+len/2]?buckets[sa[i-1]]:i;
    iota(cnt.begin(), cnt.end(),0);
    for(int i=0;i<n;++i) if(s[i]>=len)
      sa[cnt[buckets[s[i]-len]]++]=s[i]-len;
  }
  return sa;
}
vector<int> kasai(string &s, vector<int> &sa){
  int n = s.size();
  vector<int> lcp(n),inv(n);
  for(int i=0;i<n;++i) inv[sa[i]] = i;
  for(int i=0,k=0;i<n;++i){
    if(k<0) k = 0;
    if(inv[i]==n-1){ k=0; continue; }
    for(int j=sa[inv[i]+1];max(i,j)+k<n&&s[i+k]==s[j+k];++k);
    lcp[inv[i]] = k--;
  }
  return lcp;
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string a,s;
  int K = 0;
  for(;cin>>a;++K) s += a + char(4+K);
  vector<int> color(s.size()), col(s.size());
  for(int i=0,cnt=0;i<s.size();++i)
    col[i]=cnt, cnt+=s[i]<20;
  auto sa = suffix_array(s);
  auto lcp = kasai(s,sa);
  for(int i=0;i<lcp.size();++i) color[i]=col[sa[i]];
  int freq[11] = {};
  deque<int> v, mq;
  multiset<int> ms;
  int ans=0;
  for(int i=1,COL=0;i<lcp.size();++i){
    if(++freq[color[i]]==1) ++COL;
    while(v.size() && freq[color[v[0]]]>1){
      if(mq[0]==v[0])
        mq.pop_front();
      --freq[color[v[0]]];
      v.pop_front();
    }
    if(COL==K) ans = max(ans,lcp[mq[0]]);
    v.push_back(i);
    while(mq.size() && lcp[mq[0]]>lcp[i])
      mq.pop_front();
    mq.push_back(i);
  }
  cout<<ans<<'\n';
  return 0;
}