vector<int> suffix_array(string &A){
  int n=A.size(),i=n, *M=new int[5*n];
  int *B=M,*C=M+n,*F=M+2*n,*G=M+3*n,*S=M+4*n;
  for(;i--;S[i]=n-i-1) B[i]=A[i];
  stable_sort(S,S+n,[&](int i,int j){return A[i]<A[j];});
  for(int L=1,p;L<n;L*=2){
    for(;++i<n;F[i]=B[S[i]],G[i]=B[S[i]+L/2]);
    for(;--i;F[i]=F[i]==F[i-1]&&G[i]==G[i-1]&&S[i-1]<n-L);
    for(p=B[*S]=0;++i<n;B[S[i]]=p=F[i]?p:i);
    for(fill_n(G,n,0);i--;F[i]=S[i]<L?-1:B[S[i]-L]);
    for(iota(C,C+n,0);++i<n;~F[i]?G[i]=C[F[i]]++:0);
    for(copy_n(S,n,F);i--;F[i]<L?0:S[G[i]]=F[i]-L);
  }
  vector<int>res(S,S+n);
  delete[] M;
  return res;
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