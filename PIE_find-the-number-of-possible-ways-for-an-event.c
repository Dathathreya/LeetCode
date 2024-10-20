#define fact_sz 1001
#define N 1001
int mod = ((int)1e9+7),fact[fact_sz][2],ans_arr[fact_sz];

int min(int x,int y){return ((x<=y)?(x):(y)); }
int max(int x,int y){return ((x>=y)?(x):(y)); }

int modadd(int a,int b){
	a += b;
	if(a>=mod){
		a-=mod;
	}
	if(a<0) a+=mod;
	return a;
}
int modmul(int a,int b){
	a = (1ll*a*(b%mod))%mod;
	if(a>=mod){
		a-=mod;
	}
	if(a<0) a+=mod;
	return a;
}

int binpow(int base, int power) {
    int ret = 1;
    while(power>0){
        if((power%2)==1){
            ret = modmul(ret,base);
        }
        base = modmul(base,base);
        power >>= 1;
    }
    return ret; 
}

void gen_fact() {
    fact[0][0] = fact[0][1] = 1;
    for(int num=1;num<N;num++){
        fact[num][0] = modmul(fact[num-1][0],num); // fact(n) under mod
        fact[num][1] = binpow(fact[num][0],mod-2); // 1/fact(n) under mod 
    } 
}

int nCr(int n, int k, int p){
    return modmul(fact[n][0],modmul(fact[k][1],fact[n-k][1]));
}

int numberOfWays(int people, int stage, int score) {
	gen_fact();	
	// princple of inclusion and exclusion 
	int ans = 0;
	memset(ans_arr,0,sizeof(ans_arr));
	for(int st=1;st<=min(people,stage);st++){
		int temp_cnt=0;
		for(int prev_st=st;prev_st>=1;prev_st--){
			temp_cnt = modadd(temp_cnt,modmul(nCr(st,prev_st,mod),(prev_st==st)?(binpow(st,people)):(-ans_arr[prev_st])));
		}
		ans_arr[st]=temp_cnt;
		ans = modadd(ans,modmul(nCr(stage,st,mod),modmul(temp_cnt,binpow(score,st))));
	}
	return ans;
}
