long long trie[100005][35];
void add(long long x){
	for(int i=32;i--;){
		if(!trie[clk][i] && (x&(1<<i))){
			trie[clk][i]=x;
			break;
		}
		else x=min(x,x^trie[clk][i]);
	}
}
int main(){
	ans=res[1]^res[n];
	for(int i=32;i--;){
		ans=min(ans,ans^trie[vis[1]][i]);
	}
}