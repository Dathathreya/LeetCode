#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int mod = ((int)1e9+7);
    int neg[1002][3],posi[1002][3],temp_neg[1002][3],temp_posi[1002][3];
    int modadd(int a,int b){
        a += b;
        if(a>=mod) a -= mod;
        return a;
    }
    int verdict(char alice,char bob){
        if(alice==bob){
            return 0;
        }
        if(((alice=='F')&&(bob=='W'))||((alice=='W')&&(bob=='E'))||((alice=='E')&&(bob=='F'))){
            return 1;
        }
        return -1;
    }
    // FF,FW,FE,(WF,WW,WE),EF,EW,EE - (Alice,Bob Pair)
    void base_case(int num,int pos){
        if(num>0){
            temp_posi[num][pos]++;
        }
        else{
            int x = (num==0)?(0):(-num);
            temp_neg[x][pos]++;
        }
        return;
    }
    void shift_array(int num1,int pos){
        int pos1=2-pos-(pos==1),pos2 = 3-pos1-pos;
        //printf("(%d,%d,%d)",pos,pos1,pos2);
        for(int j=1;j<1002;j++){ // 1....1001
            if(num1>0){
                // forward
                // 10 <- 9 
                // 1001 <- 1000
                // 1 <- 0(pos+neg)
temp_posi[1002-j][pos] = modadd(temp_posi[1002-j][pos],((1002-j-1)==0)?(modadd(neg[0][pos1],posi[0][pos1])):(posi[1002-j-1][pos1]));
temp_posi[1002-j][pos] = modadd(temp_posi[1002-j][pos],((1002-j-1)==0)?(modadd(neg[0][pos2],posi[0][pos2])):(posi[1002-j-1][pos2]));
                // 0 <- -1
                // -999 <- -1000
                 temp_neg[j-1][pos] = modadd(temp_neg[j-1][pos],neg[j][pos1]);
                 temp_neg[j-1][pos] = modadd(temp_neg[j-1][pos],neg[j][pos2]);
            }
            else if(num1<0){
                // reverse
                // -1 <- 0(pos+neg) 
                // -1000 <- -999
temp_neg[1002-j][pos] = modadd(temp_neg[1002-j][pos],((1002-j-1)==0)?(modadd(neg[0][pos1],posi[0][pos1])):(neg[1002-j-1][pos1]));
temp_neg[1002-j][pos] = modadd(temp_neg[1002-j][pos],((1002-j-1)==0)?(modadd(neg[0][pos2],posi[0][pos2])):(neg[1002-j-1][pos2]));
                // 0 <- 1
                // 999 <- 1000
                temp_posi[j-1][pos] = modadd(temp_posi[j-1][pos],posi[j][pos1]);
                temp_posi[j-1][pos] = modadd(temp_posi[j-1][pos],posi[j][pos2]);
            }
            else if(num1==0){
                temp_posi[j-1][pos] = modadd(temp_posi[j-1][pos],posi[j-1][pos1]);
                temp_posi[j-1][pos] = modadd(temp_posi[j-1][pos],posi[j-1][pos2]);
                temp_neg[j-1][pos] = modadd(temp_neg[j-1][pos],neg[j-1][pos1]);
                temp_neg[j-1][pos] = modadd(temp_neg[j-1][pos],neg[j-1][pos2]);
            }
        }
        return;
    }
    
    int countWinningSequences(char* s) {
        //return dfs(s,0,s.size(),0); DFS not needed 
        //printf("%s\n",s);
        memset(posi,0,sizeof(posi));memset(neg,0,sizeof(neg));
        memset(temp_neg,0,sizeof(temp_neg));memset(temp_posi,0,sizeof(temp_posi));
        int ans = 0,i,n=strlen(s),j;
        for(i=0;i<n;i++){ // num
            int f_ = verdict(s[i],'F');
            int w_ = verdict(s[i],'W');
            int e_ = verdict(s[i],'E');
            if(i==0){
                base_case(f_,0);
                base_case(w_,1);
                base_case(e_,2);
            }
             else{                
                shift_array(f_,0);
                shift_array(w_,1);
                shift_array(e_,2);
            }
                memcpy(posi,temp_posi,1002*3*sizeof(int));
                memcpy(neg,temp_neg,1002*3*sizeof(int));    
                memset(temp_posi,0,1002*3*sizeof(int));
                memset(temp_neg,0,1002*3*sizeof(int)); 
        }
        for(int i=1;i<=1001;i++){ // num
            for(int j=0;j<=2;j++){ // for all combinations ending with E,F,W
                ans = modadd(ans,posi[i][j]);
            }   
        }
        return ans;
   	}
void solve(){
	int n;
	char s[1002];
	fgets(s,sizeof(s),stdin);
	printf("%d\n",countWinningSequences(s));
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
