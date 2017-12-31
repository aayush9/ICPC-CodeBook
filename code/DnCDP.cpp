long long dp[21][100005];
void cost(int x, int y);
void computeDP(int idx,int jleft,int jright,int kleft,int kright){
	if(jleft>jright) return;
	int jmid=(jleft+jright)/2;
	int bestk=jmid;
	for(int k=kleft;k<=min(kright,jmid);++k){
		cost(k,jmid);
		if(dp[idx-1][k-1]+tot<dp[idx][jmid])
			dp[idx][jmid]=dp[idx-1][k-1]+tot,bestk=k;
	}
	computeDP(idx,jleft,jmid-1,kleft,bestk);
	computeDP(idx,jmid+1,jright,bestk,kright);
}
int main(){
	for(int i=0;i<=k;++i)
		for(int j=0;j<=n;dp[i][j++]=1e17);
	dp[0][0]=0;
	for(int i=1;i<=k;++i)
		computeDP(i,1,n,1,n);
	cout<<dp[k][n];
}