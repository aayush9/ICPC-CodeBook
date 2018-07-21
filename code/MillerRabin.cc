//   Error rate: 2^(-TRIAL)
//   Almost constant time. srand is needed

int64_t ModMul(int64_t a, int64_t b, int64_t m){
	int64_t ret=0, c=a;
	for(;b;b>>=1, c=(c+c)%m)
		if(b&1) ret=(ret+c)%m;
	return ret;
}
int64_t ModExp(int64_t a, int64_t n, int64_t m){
	return n?ModMul(ModExp(ModMul(a,a,m),n/2,m),(n%2?a:1),m):1;
}
bool Witness(int64_t a, int64_t n){
	int64_t u=n-1;
  	int t=0;
	while(!(u&1)){u>>=1; t++;}
	int64_t x0=ModExp(a, u, n), x1;
	for(int i=1;i<=t;i++) {
		x1=ModMul(x0, x0, n);
		if(x1==1&&x0!=1&&x0!=n-1) return true;
		x0=x1;
	}
	if(x0!=1) return true;
	return false;
}

bool IsPrimeFast(int64_t n, int TRIAL=15){
  if(n<=2) return (n==2);
  static random_device rd;
  static mt19937_64 g(rd());
  while(TRIAL--)
    if(Witness(g()/2%(n-2)+1, n)) 
    	return false;
  return true;
}
