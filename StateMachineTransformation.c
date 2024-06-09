#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

const int mod = (int)1e9+7;
int Abs(int x){ return (x>0)?(x):(-x);}

int addmod(int m,int n){
    if(m<=(INT_MAX-n)){
        return (m+n)%mod;
    }
    if(Abs(m-mod)<m){
        m -= mod;
    }
    if(Abs(n-mod)<n){
        n -= mod;
    }
    int ret = (n+m)%mod;
    if(ret<0) ret += mod;
    return ret;
}

int mulmod(int m,int n)
{
	if((m==0)||(n==0)) return 0;
	if(m<=(INT_MAX/n)) return (m*n)%mod;
	if(Abs(m-mod)<m) m -= mod;
	if(Abs(n-mod)<n) n -= mod;
	int ret = (1ll*m*n)%mod;
	if(ret<0) ret += mod;
	return ret;
}

int checkRecord(int n){
    if(n==1) return 3;
    int ans=0,i=0;
    int count[][3]={{1,1,0}
                   ,{1,0,0}};

    for(int i=1;i<n;i++){
        // State Transition 
        // without A and L -> (Add P to (A=0,L=0)) or (Add P to (A=0,L=1)) or (Add P to (A=0,L=2))
        // Adding P will make L to 0 irrespective of its previous value
        int new_00 = 0; 
        new_00 = addmod(new_00,count[0][0]);new_00 = addmod(new_00,count[0][1]);
        new_00 = addmod(new_00,count[0][2]);
        // without A but one L -> ((Add  L to (A=0,L=0)) 
        int new_01 = count[0][0]; 
        // without A but two L -> ((Add  L to (A=0,L=1)) 
        int new_02 = count[0][1];
        // with A=1 and L=0 -> (Add A to (A=0,L=0)) or (Add A to (A=0,L=1)) or  (Add A to (A=0,L=2))
        // or (Add P to (A=1,L=0)) or (Add P to (A=1,L=1)) or (Add P to (A=1,L=2))
        // Adding P will make L to 0 irrespective of its previous value
        int new_10 = 0;
        new_10 = addmod(new_10,count[0][0]);new_10 = addmod(new_10,count[0][1]);
        new_10 = addmod(new_10,count[0][2]);
        new_10 = addmod(new_10,count[1][0]);new_10 = addmod(new_10,count[1][1]);
        new_10 = addmod(new_10,count[1][2]);
        // with A=1 and L=1 -> (Add L to (A=1,L=0)) 
        int new_11 = count[1][0];
        // with A=1 and L=2 -> (Add L to (A=1,L=1)) 
        int new_12 = count[1][1];
        count[0][0] = new_00,count[0][1] = new_01,count[0][2] = new_02;
        count[1][0] = new_10,count[1][1] = new_11,count[1][2] = new_12;
    }
    int new_10 = 0;
        new_10 = addmod(new_10,count[0][0]);new_10 = addmod(new_10,count[0][1]);
        new_10 = addmod(new_10,count[0][2]);
        new_10 = addmod(new_10,count[1][0]);new_10 = addmod(new_10,count[1][1]);
        new_10 = addmod(new_10,count[1][2]);

	return new_10;
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
