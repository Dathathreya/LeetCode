#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
	assert(freopen("input.txt", "r", stdin) );
	assert(freopen("output.txt", "w", stdout));
#endif //  LocalStreetLampsLitOnFire
}
int mod = ((int)1e9+7);
// matrix multiplication template 
// matrix exponentiation template 
// state transition , incident matrix
#define N ((int)5e4+4)

int inc[26][26],act[26][26],tem[26][26];
char str[N];

int modadd(int a,int b){
    a += b;
    if(a>=mod) a-=mod;
    return a;
}

int modmul(int a,int b){
    a = (1ll*a%mod*b)%mod;
    if(a<0) a+=mod;
    return a;
}

void mat_mul(const void *inc1,const void* act1,const void* tem1,int D){
    int* m1 = (int*)inc1;
    int* m2 = (int*)act1;
    int* temz = (int*)tem1;
    int rs,cs;
    rs = cs = D;
    memset(temz,0,cs*rs*sizeof(int));
    for(int row1=0;row1<rs;row1++){
        for(int col1=0;col1<cs;col1++){
            for(int k1=0;k1<cs;k1++){
                temz[row1*cs+col1] = modadd(temz[row1*cs+col1],modmul(m1[row1*cs+k1],m2[k1*cs+col1]));
            }   
        }
    }
    memcpy(m1,temz,cs*rs*sizeof(int));
    return ;
}

void binmatpow(const void *inc,const void* act,const void* temz,int exponent,int _2d_size){
    while(exponent>0){
        if((exponent%2)==1){
            mat_mul(inc,act,temz,_2d_size);
        }
            mat_mul(act,act,temz,_2d_size);
        exponent /= 2;
    }
    return;
}
int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
    int n=strlen(s),i,j;
    memset(act,0,sizeof(act));
    memset(tem,0,sizeof(tem));
    memset(inc,0,sizeof(inc));
    for(i=0;i<26;i++){
        int pos = nums[i];
        inc[i][i] = 1;
        for(;pos>0;pos--){
            act[i][(26+i+pos)%26] = 1;
        }   
    }
    binmatpow(inc,act,tem,t,26);
    int ans = 0;
    for(i=0;i<n;i++){
        int j = s[i]-'a';
        for(int u=0;u<26;u++){
            ans = modadd(ans,inc[j][u]);
        }    
    }
    return ans;
}
void solve(){
    int n,i,t,j;
    scanf("%s",&str);
    scanf("%d",&t);
    n = strlen(str);
    int nums[26];
    for(i=0;i<26;i++){
        scanf("%d",&nums[i]);
        //printf("%d ",nums[i]);
    }
    printf("%d\n",lengthAfterTransformations(str,t,nums,n));
    return;
}

int main(int argc,char* argv[]){
    int tt=1;
    io_init();
    //assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    }
}
