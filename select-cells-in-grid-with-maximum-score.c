int grps[101][2/*0-value,1-mask*/],dp[101][(1<<10)],rs=0,n=0,maxiSum=0;
int pairs[101][2];
int max(int a,int b){
    return ((a>=b)?(a):(b));
}
int dfs(int pos,int tracktaken){
          if(pos>=n){
              return 0;  
          } 
          if(dp[pos][tracktaken]==-1){      
                for(int free=0;free<rs;free++){ // taking current element 
                        if(((grps[pos][1])&(1<<free))!=0) // current element should be there at that spot
                        {
                            if(((1<<free)&(tracktaken))==0){ // choose spot  which is not taken 
                                dp[pos][tracktaken] = max(dp[pos][tracktaken],grps[pos][0]+dfs(pos+1,tracktaken|(1<<free)));
                            }
                        }
                }
                dp[pos][tracktaken] = max(dp[pos][tracktaken],dfs(pos+1,tracktaken)); // skipping current element
          }
          return dp[pos][tracktaken];  
}
typedef int compare_self_t(const void*,int,int);  
typedef void swap_self_t(const void*,int,int);  

void swap_self_int(const void* arr,int left,int right){
    int* a1 = (int*)arr;
    int  t = a1[2*left] ;a1[2*left]= a1[2*right];a1[2*right]=t;
    t = a1[2*left+1],a1[2*left+1]= a1[2*right+1];a1[2*right+1]=t; // forgot to swap indexes
    return;
}

int compare_self_int(const void* arr,int left,int right){
    int* a1 = (int*)arr;
    return a1[2*left] >= a1[2*right]; 
}

void heapify(const void* arr,int root,int sz,compare_self_t compfn,swap_self_t swapfn){
    int left = (root<<1)+1 , right = (root<<1)+2,greatest=root;
    if((left<sz)&&(compfn(arr,greatest,left))){
        greatest = left;
    }
    if((right<sz)&&(compfn(arr,greatest,right))){
        greatest = right;
    }
    if(greatest!=root){
        swapfn(arr,greatest,root);
        heapify(arr,greatest,sz,compfn,swapfn);
    }
}
void heapSort(const void* arr,int low,int high,compare_self_t compfn,swap_self_t swapfn){
    for(int i=low+((high+low)/2);i>=low;i--){
        heapify(arr,i,high+1,compfn,swapfn);// start from all possible roots  going upwards
    }
    for(int i=high;i>=low;i--){
        swapfn(arr,low,i);
        heapify(arr,low,i,compfn,swapfn);
    }
    return;
}

int maxScore(int** grid, int gridSize, int* gridColSize) {
    rs = gridSize;
    int rows = 0,colS = gridColSize[0],z=0;
    memset(grps,0,sizeof(grps));
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<gridSize;i++){
        for(int j=0;j<colS;j++){
            pairs[z][0]=grid[i][j];
            pairs[z][1]=rows;
            z++;
        }
        rows++;
    }
    heapSort(pairs,0,z-1,compare_self_int,swap_self_int); // sort pairs of index and values
    int prev = pairs[0][0] ;
    n = 1;
    for(int i=0;i<z;i++){
            int f = pairs[i][0];
            int r = pairs[i][1];
            if(f==prev){
                grps[n-1][0] = f;
                grps[n-1][1] |= (1<<r);
            }
            else{
                n++;
                grps[n-1][0] = f;
                grps[n-1][1] |= (1<<r);
            }
            prev = f;
    }
    return dfs(0,0);
}
