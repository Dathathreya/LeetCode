#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

const int mod = (int)1e9+7;
int count[100001],L[3];
int max(int m,int n){ return (m>=n)?(m):(n);}
int min(int m,int n){ return (m<=n)?(m):(n);}
int f(int x){return (x!=0)?(x):(1); }
int Abs(int x){return (x>0)?(x):(-x);}

int addmod(int a,int b){
	if(a<=(INT_MAX-b)){
		return (a+b)%mod;
	}
	if(Abs(a-mod)<a){ a -= mod; }
	if(Abs(b-mod)<b){ b -= mod; }

	int ret = (a+b)%mod;
	if(ret<0) ret += mod;
	return ret;
}

int mulmod(int a,int b){
	if((a==0)||(b==0)){
		return 0;
	}
	if(a<=(INT_MAX/b)){
		return (a*b)%mod;
	}
	if(Abs(a-mod)<a){ a -= mod; }
	if(Abs(b-mod)<b){ b -= mod; }
	int ret = (1ll*a*b)%mod;
	if(ret<0) ret += mod;
	return ret;
}

int checkRecord(int n){
	if(n==1){
		return 3;
	}
	memset(count,0,sizeof(count));
	memset(L,0,sizeof(L));
	int i=0,ans=0; L[0]=1,L[1]=1,L[2]=0;// 1P,1L,0LL
	count[1] = (L[0]+L[1]+L[2])%mod;
	for(i=1;i<=n;i++){
		int new_P,new_L1,new_L2;new_P=0,new_L1=0,new_L2=0;
		new_P = addmod(new_P,L[0]); // endswith P from 1P,
		new_P = addmod(new_P,L[1]); // endswith P from 1L,
		new_P = addmod(new_P,L[2]); // endswith P from 2LL,
		new_L1  = L[0];// endswith L from 1P 
		new_L2  = L[1];// endswith L from 1L
		count[i+1] = addmod(count[i+1],new_P);
		count[i+1] = addmod(count[i+1],new_L1); 
		count[i+1] = addmod(count[i+1],new_L2); 
		L[0] = new_P;
		L[1] = new_L1;
		L[2] = new_L2;
	}

	for(i=0;i<=n-1-i;i++){
		if(i!=n-1-i){
			int pdt =1;
			pdt = mulmod(2,f(count[i]));
			pdt = mulmod(pdt,f(count[n-1-i]));
			ans = addmod(ans,pdt);
		}
		else{
			int pdt =1;
			pdt = mulmod(1,f(count[i]));
			pdt = mulmod(pdt,f(count[n-1-i]));
			ans = addmod(ans,pdt);
		}
	}
	ans = addmod(ans,count[n]);
	//printf("\n");
	return ans;
}

void solve(){
	int n;
	assert(fscanf(stdin,"%d",&n)>0);
	printf("%d\n",checkRecord(n));
}

int main(){
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
