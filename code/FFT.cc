auto FFT = [](vector<long double>a,vector<long double>b){
  auto DFT = [](vector<complex<long double>>&a, bool inv){
    int L=31-__builtin_clz(a.size()), n=1<<L;
    vector<complex<long double>> A(n);
    for(int k=0,r,i;k<n;A[r]=a[k++]) 
      for(i=r=0;i<L;(r<<=1)|=(k>>i++)&1);
    complex<long double> w,wm,t;
    for(int m=2,j,k;m<=n;m<<=1) 
      for(w={0,2*acos(-1)/m},wm=exp(inv?-w:w),k=0;k<n;k+=m)
        for(j=0,w=1;j<m/2;++j,w*=wm)
          t=w*A[k+j+m/2],A[k+j+m/2]=A[k+j]-t,A[k+j]+=t;
    return A;
  };  
  int n=4<<31-__builtin_clz(max(a.size(),b.size()));
  vector<complex<long double>> A(n), B(n), CC(n);
  for(int i=0;i<n;++i) 
    A[i]=i<a.size()?a[i]:0,B[i]=i<b.size()?b[i]:0;
  vector<complex<long double>> AA=DFT(A,0), BB=DFT(B,0);
  for(int i=0;i<n;++i) CC[i]=AA[i]*BB[i];
  vector<long double> c;
  for(auto i:DFT(CC,1)) if(c.size()<a.size()+b.size()-1) 
    c.push_back(i.real()/n+1e-5);
  return c;
};